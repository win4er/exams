#include "math.hpp"

Func_Data::Func_Data() {
    count = 0;
    func_expr = nullptr;
    degree_expr = nullptr;
    param_expr = nullptr;
    operations = nullptr;
}

Func_Data::~Func_Data() {
    count = 0;
    delete [] func_expr;
    delete [] degree_expr;
    delete [] param_expr;
    delete [] operations;
}

bool Func_Data::insert_data(const std::string& expression, int info_type, int index) {
    assert((info_type >= 0) && (info_type <= 3));
    if (index < count) {
        switch (info_type) { // rewriting existed func_data
            case (0): {
                func_expr[index] = expression;
                break;
            }
            case (1): {
                degree_expr[index] = expression;
                break;
            }
            case (2): {
                param_expr[index] = expression;
                break;
            }
            case (3): {
                assert(expression.size() == 1);
                operations[index] = expression;
                break;
            }
        }
    } else if (index == count) { // + 1 new func_data
        count += 1;
        std::string* new_func_expr = new std::string[count];
        std::string* new_degree_expr = new std::string[count];
        std::string* new_param_expr = new std::string[count];
        std::string* new_operations = new std::string[count];
        for (int iter=0; iter < (count-1); ++iter) {
            new_func_expr[iter] = func_expr[iter];
            new_degree_expr[iter] = degree_expr[iter];
            new_param_expr[iter] = param_expr[iter];
            new_operations[iter] = operations[iter];
        }
        delete [] func_expr;
        delete [] degree_expr;
        delete [] param_expr;
        delete [] operations;

        func_expr = new_func_expr;
        degree_expr = new_degree_expr;
        param_expr = new_param_expr;
        operations = new_operations;

        func_expr[index] = "none";
        degree_expr[index] = "1";
        param_expr[index] = "none";
        operations[index] = "+";   
        switch (info_type) {
            case (0): {
                func_expr[index] = expression;
                break;
            }
            case (1): {
                degree_expr[index] = expression;
                break;
            }
            case (2): {
                param_expr[index] = expression;
                break;
            }
            case (3): {
                assert(expression.size() == 1);
                operations[index] = expression;
                break;
            }
        }
    } else {
        printf("There is %d func_data expressions, you can add 1 more, not %d more\n", count, count-index-1);
        return false;
    }
    return true;
}

bool Func_Data::show() {
    if (count > 0) {
        for (int i=0; i<count; ++i) {
            printf("Func #%d\n", i+1);
            printf("[operation]: {%s}\n", operations[i].c_str());
            printf("[func_name]: {%s}\n", func_expr[i].c_str());
            printf("[degree]: {%s}\n", degree_expr[i].c_str());
            printf("[param]: {%s}\n", param_expr[i].c_str());
        }
        return true;
    }
    printf("Data is empty!\n");
    return false;
}

Math::Math() {}

Math::~Math() {}

int Math::check_is_branch(const char& element) {
    const char* opening_br = "({[<";
    const char* closing_br = ")}]>";
    int length = 5;
    for (int iter = 0; iter < length; ++iter) {
        if ((element == opening_br[iter]) || (element == closing_br[iter])) {
            if (element == opening_br[iter]) {
                /*if ((element == opening_br[iter]) && (element == closing_br[iter])) {
                    return 0; // for |...| branches
                } lets forget about |...| branches for now, i will come back to it later*/
                return -1;
            } else {
                return +1;
            }
        }
    }
    return 0;
}

int Math::check_is_sign(const char& element) {
    const char* signs = "+-*/^ ";
    int length = 6;
    for (int iter = 0; iter < length; ++iter) {
        if (element == signs[iter]) {
            return iter + 1; //number of sign, 0 is reserved for nonsign symbols
        }
    }
    return 0;
}

bool Math::check_is_digit(const char& element) {
    const char* digits = "0123456789";
    int length = 10;
    for (int iter = 0; iter < length; ++iter) {
        if (element == digits[iter]) {
            return true;
        }
    }
    return false;
}

bool Math::check_br_in_expr(const std::string& s) {
    int count = 0; 
    //TODO: write it, considering this: }{ is wrong, 
    //actually u can count += branch, and if count > 0 at ')', that means its broken expr
    int opening_br_indexes[4] = {-1, -1, -1, -1};
    int closing_br_indexes[4] = {-1, -1, -1, -1};
    std::map<std::string, int> branch_map = {
        {"()", 0},
        {"{}", 0},
        {"[]", 0},
        {"<>", 0},
    };

    int check = 0;
    int start = -1;
    int end = -1;

    std::string type = "";
    for (int iter = 0; iter < s.size(); ++iter) {
        check = check_is_branch((s.c_str())[iter]);
        if (check) {
            count += 1;
            switch (s.c_str()[iter]) { //TODO: write it without switch
                case ('('): {
                    type = "()";
                    branch_map["()"] += check;
                    opening_br_indexes[0] = iter;
                    start = iter;
                    end = closing_br_indexes[0];
                    break;
                }
                case (')'): {
                    type = "[]";
                    branch_map["()"] += check;
                    closing_br_indexes[0] = iter;
                    start = opening_br_indexes[0];
                    end = iter;
                    break;
                }
                case ('{'): {
                    type = "{}";
                    branch_map["{}"] += check;
                    opening_br_indexes[1] = iter;
                    start = iter;
                    end = closing_br_indexes[1];
                    break;
                }
                case ('}'): {
                    type = "{}";
                    branch_map["{}"] += check;
                    closing_br_indexes[1] = iter;
                    start = opening_br_indexes[1];
                    end = iter;
                    break;
                }
                case ('['): {
                    type = "[]";
                    branch_map["[]"] += check;
                    opening_br_indexes[2] = iter;
                    start = iter;
                    end = closing_br_indexes[2];
                    break;
                }
                case (']'): {
                    type = "[]";
                    branch_map["[]"] += check;
                    closing_br_indexes[2] = iter;
                    start = opening_br_indexes[2];
                    end = iter;
                    break;
                }
                case ('<'): {
                    type = "<>";
                    branch_map["<>"] += check;
                    opening_br_indexes[3] = iter;
                    start = iter;
                    end = closing_br_indexes[3];
                    break;
                }
                case ('>'): {
                    type = "<>";
                    branch_map["<>"] += check;
                    closing_br_indexes[3] = iter;
                    start = opening_br_indexes[3];
                    end = iter;
                    break;
                }
            }
            bool condition = ((end-start)<0)&&((end != -1)&&(start != -1)) && (branch_map[type]==0);
            if (condition) {
                //printf("'%c, %c'; '%d, %d'\n", s[start], s[end], start, end);
                return false;
            }
        }
    }
    bool condition = {
        (branch_map["()"] == 0) && 
        (branch_map["{}"] == 0) &&
        (branch_map["[]"] == 0) &&
        (branch_map["<>"] == 0) &&
        (count % 2 == 0)
    };
    return condition;
}

int Math::element_type(const char& element) {
    int branch = check_is_branch(element);
    int digit = check_is_digit(element);
    int sign = check_is_sign(element);

    if (branch) {
        return 3;
    } else if (digit) {
        return 2;
    } else if (sign) {
        return 1;
    }
    return 0; //x or func_name
}

bool Math::check_is_const_expr(const std::string& expression) {
    int cur_element_type = -1;
    int prev_element_type = -1;
    for (int iter=0; iter<expression.size(); ++iter) {
        cur_element_type = check_is_digit(expression[iter]);
        if (iter==0) {
            if (cur_element_type != 0) {
                prev_element_type = cur_element_type;
                continue;
            } else {
                return false;
            }
        }
        if ((cur_element_type == 0)||(prev_element_type == 0)) {
            return false;
        }
        prev_element_type = cur_element_type;
    }
    return true;
}

bool Math::expression_type_data(const std::string& expression, int* expression_type_data) {
    assert(check_br_in_expr(expression));
    int cur_element_type = 0;
    int prev_element_type = 0;
    int cur_expr_type = 0;
    int branch_count = 0;
    const int expr_length = expression.size();
    for (int iter=0; iter<expr_length; ++iter) {
        cur_element_type = element_type(expression[iter]);
        if ((iter == 0)||(iter == (expr_length-1))) {
            if ((iter == 0) && (iter == (expr_length-1))) {
                cur_expr_type = 0;
            } else if (iter == 0) {
                switch (cur_element_type) {
                    case (0): {
                        cur_expr_type = 0;
                        break;    
                    }
                    case (1): {
                        cur_expr_type = 3;
                        break;    
                    }
                    case (2): {
                        cur_expr_type = 0;
                        break;    
                    }
                    case (3): {
                        cur_expr_type = 0;
                        branch_count += check_is_branch(expression[iter]);
                        break;
                    }
                }
            } else if (iter == (expr_length-1)) {
                if (branch_count) {
                    cur_expr_type = expression_type_data[iter-1];
                    branch_count += check_is_branch(expression[iter]);
                    if (branch_count) {
                        printf("Wrong expression\n");
                        return false; 
                    }
                } else {
                    switch (cur_element_type) {
                        case (0): {
                            if (prev_element_type == 1) {
                                int sign = check_is_sign(expression[iter-1]);
                                if (sign == 5) {
                                    cur_expr_type = 1;
                                } else {
                                    cur_expr_type = 0;
                                }
                            } else {
                                cur_expr_type = expression_type_data[iter-1];
                            }
                            break;
                        }
                        case (1): {
                            printf("You cant use '%c' sign at the end of expression\n", expression[iter]);
                            return false;
                            break;    
                        }
                        case (2): {
                            if (prev_element_type == 1) {
                                int sign = check_is_sign(expression[iter-1]);
                                if (sign == 5) {
                                    cur_expr_type = 1;
                                } else {
                                    cur_expr_type = 0;
                                }
                            } else {
                                cur_expr_type = expression_type_data[iter-1];
                            }
                            break;    
                        }
                        case (3): {
                            printf("Wrong expression, last element is '%c'\n", expression[iter]);
                            return false;
                            break;    
                        }
                    }   
                }
            }
        } else if ((iter != 0) && (iter != (expr_length-1))) {
            if (branch_count) {
                cur_expr_type = expression_type_data[iter-1];
                branch_count += check_is_branch(expression[iter]);
            } else {
                switch (cur_element_type) {
                    case (0): {
                        if (prev_element_type == 1) {
                            int sign = check_is_sign(expression[iter-1]);
                            if (sign == 5) {
                                cur_expr_type = 1;
                            } else {
                                cur_expr_type = 0;
                            }
                        } else {
                            cur_expr_type = expression_type_data[iter-1];
                        }
                        break;
                    }
                    case (1): {
                        cur_expr_type = 3;
                        break;    
                    }
                    case (2): {
                        if (prev_element_type == 1) {
                            int sign = check_is_sign(expression[iter-1]);
                            if (sign == 5) {
                                cur_expr_type = 1;
                            } else {
                                cur_expr_type = 0;
                            }
                        } else {
                            cur_expr_type = expression_type_data[iter-1];
                        }
                        break;    
                    }
                    case (3): {
                        int branch = check_is_branch(expression[iter]);
                        if (branch == 1) {
                            printf("Part of expression started with closing branch '%c'\n", expression[iter]);
                            return false;
                        } else {
                            int prev_expr_type = expression_type_data[iter-1];
                            if (prev_expr_type == 3) {
                                int sign = check_is_sign(expression[iter-1]);
                                if (sign == 5) {
                                    cur_expr_type = 1;
                                } else {
                                    cur_expr_type = 0;
                                }
                            } else if ((prev_expr_type == 0)||(prev_expr_type == 1)) {
                                cur_expr_type = 2;
                            }
                        }
                        branch_count += check_is_branch(expression[iter]);
                        break;    
                    }
                }   
            }
        }
        expression_type_data[iter] = cur_expr_type;
        prev_element_type = cur_element_type;
    }
    return true;
}

bool Math::show_expression_type_data(const std::string& expression) {
    int* expr_data = new int[expression.size()];
    expression_type_data(expression, expr_data);
    for (int iter=0; iter<expression.size(); ++iter) {
        printf("%d", expr_data[iter]);
    }
    printf("\n");
    delete [] expr_data;
    return true;
}

bool Math::expression(const std::string& expression, Func_Data* data) {
    //TODO: fix inserting sign_data if it doesnt stated
    assert(check_br_in_expr(expression));
    int* expr_code_type = new int[expression.size()];
    expression_type_data(expression, expr_code_type);
    
    const int size = expression.size();
    int func_count = 0;
    int prev_func_count = 0;

    int start=0, end=0;
    for (int iter=0; iter<size; ++iter) {
        if ((iter == 0) || (iter == (size-1))) {
            if ((iter == 0) && (iter == (size-1))) {
                start = iter;
                end = iter;
                func_count = 1;
                int info_type = expr_code_type[iter];
                std::string info = expression.substr(start, end-start+1);
                data->insert_data(info, info_type, func_count-1);
                std::string sign_info;
                sign_info = "+";
                data->insert_data(sign_info, 3, func_count-1);  
                //printf("[%d][%d]%s\n", func_count-1, info_type, info.c_str());
            } else if (iter == 0) {
                start = iter;
                end = iter;
                func_count = 1;
                int info_type = expr_code_type[iter];
                std::string sign_info;
                if (info_type == 0) {
                    sign_info = "+";
                    data->insert_data(sign_info, info_type, func_count-1);
                } else if (info_type == 3) {
                    int sign_type = check_is_digit(expression[iter]);
                    if (sign_type < 3) {
                        sign_info = expression[iter];
                        data->insert_data(sign_info, info_type, func_count-1);
                    } else {
                        printf("Expressin cant be started by '%s'", expression[iter]);
                        return false;
                    }
                }
                                  
            } else if (iter == (size-1)) {
                end = iter;
                int branch_1 = check_is_branch(expression[start]);
                int branch_2 = check_is_branch(expression[end]);
                int info_type = expr_code_type[start];
                std::string info;
                if (expr_code_type[iter]!=expr_code_type[iter-1]) {
                    if (expr_code_type[iter-1] == 3) { 
                        start = iter;
                        info_type = expr_code_type[start];
                        if (expr_code_type[iter] == 0) {
                            func_count += 1;
                            std::string sign_info;
                            sign_info = expression.substr(iter-1, 1);
                            data->insert_data(sign_info, 3, func_count-1);
                        }
                    }
                }
                if ((branch_1 == -1) && (branch_2 == 1)) {
                    info = expression.substr(start+1, end-1-(start+1)+1);
                } else {
                    info = expression.substr(start, end-start+1);
                }
                data->insert_data(info, info_type, func_count-1);
                //printf("[%d][%d]%s\n", func_count-1, info_type, info.c_str());
            }
        } else {
            if (expr_code_type[iter] != expr_code_type[iter-1]) {
                std::string info = "";
                if (expr_code_type[iter-1] == 3) {
                    start = iter;
                    end = iter;
                    if (expr_code_type[iter] == 0) {
                        func_count += 1;
                        std::string sign_info;
                        sign_info = expression.substr(iter-1, 1);
                        data->insert_data(sign_info, 3, func_count-1);                       
                    }
                } else if (expr_code_type[iter] == 3) {
                    end = iter-1;
                    int branch_1 = check_is_branch(expression[start]);
                    int branch_2 = check_is_branch(expression[end]);
                    int info_type = expr_code_type[start];
                    std::string info;
                    if ((branch_1 == -1) && (branch_2 == 1)) {
                        info = expression.substr(start+1, end-1-(start+1)+1);
                    } else {
                        info = expression.substr(start, end-start+1);
                    }
                    data->insert_data(info, info_type, func_count-1);
                    //printf("[%d][%d]%s\n", func_count-1, info_type, info.c_str());
                } else {
                    assert(start>=0);
                    int branch_1 = check_is_branch(expression[start]);
                    int branch_2 = check_is_branch(expression[end]);
                    int info_type = expr_code_type[start];
                    std::string info;
                    if ((branch_1 == -1) && (branch_2 == 1)) {
                        info = expression.substr(start+1, end-1-(start+1)+1);
                    } else {
                        info = expression.substr(start, end-start+1);
                    }
                    data->insert_data(info, info_type, func_count-1);
                    //printf("[%d][%d]%s\n", func_count-1, info_type, info.c_str());
                    start = iter;
                    end = iter;
                }
            } else {
                end = iter;
            }
        }
        //printf("%d", func_count);
        prev_func_count = func_count;
    }
    printf("\n");
    delete [] expr_code_type;
    return true;
}

std::string Math::make_it_branched(const std::string& expr) {
    return "(" + expr + ")";
}

std::string Math::make_it_unbranched(const std::string& expr) {
    if ((check_is_branch(expr[0])==-1) && (check_is_branch(expr[expr.size()-1])==1)) {
        int start = 1;
        int end = expr.size()-1-1;
        return expr.substr(start,end-start+1);
    } else {return expr;}
}

bool Math::sub_derivative(Func_Data *input, Func_Data *output, int type) {
    
    return true;
}

bool Math::derivative(Func_Data *input) {
    for (int iter=0; iter < input->count; ++iter) {
        
    }
    return true;
}

std::string Math::stupid_derivative(std::string& input) {
    std::string good_input = input;
    Func_Data expr_data;
    expression(good_input, &expr_data);
    expr_data.show();
    
    std::string output_expr = "";
    if (expr_data.count == 1) {
        std::string input_sign = expr_data.operations[0];
        std::string input_func_name = expr_data.func_expr[0];
        std::string input_degree = expr_data.degree_expr[0];
        std::string input_param = expr_data.param_expr[0];
        
        std::string output_sign = "";
        std::string output_func_name = "";
        std::string output_degree = "";
        std::string output_param = input_param;
        
        make_it_unbranched(input_func_name);

        make_it_unbranched(input_degree);

        Func_Data func_name_data;
        expression(input_func_name, &func_name_data);

        Func_Data degree_data;
        expression(input_degree, &degree_data);

        if (func_name_data.count == 1) {        
            if (degree_data.count == 1) {
                if (input_func_name == "cos") {
                    output_sign = "-";
                    output_func_name = "sin";
                } else if (input_func_name == "sin") {
                    output_sign = input_sign;
                    output_func_name = "sin";
                } else {
                    output_func_name = input_func_name;
                }
                
                if (check_is_const_expr(input_degree)) {
                    output_degree = std::to_string(std::stoi(input_degree)-1);
                } else {
                    output_degree = "(" + input_degree + "-1)";
                }
            } else {
                printf("Proccessing hard degree: {%s}\n", input_degree.c_str());
                output_degree += "(";
                for (int iter=0; iter<degree_data.count; ++iter) {
                    output_degree += degree_data.operations[iter];
                    output_degree += stupid_derivative(degree_data.func_expr[iter]);   
                }
                output_degree += "-1)";
            }
        } else {
            printf("Proccessing hard func_name: {%s}\n", input_func_name.c_str());
            output_func_name = "(";
            for (int iter=0; iter<func_name_data.count; ++iter) {
                output_func_name += func_name_data.operations[iter];
                output_func_name += "(";
                output_func_name += stupid_derivative(func_name_data.func_expr[iter]);
                output_func_name += ")";
            }
            output_func_name += ")";
        }
        output_expr = "(" + output_sign + ")" + input_degree + ")*" + output_func_name + "^" + output_degree;
    } else {
        //printf("Processing multiple func expr {%s}\n", good_input.c_str());
        for (int iter=0; iter<expr_data.count; ++iter) {
            output_expr += expr_data.operations[iter];
            output_expr += stupid_derivative(expr_data.func_expr[iter]);
        }
    }
    return output_expr;
}