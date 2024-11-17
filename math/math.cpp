#include "math.hpp"

Func_Data::Func_Data() {
    size = 0;
    func_expr = nullptr;
    degree_expr = nullptr;
    param_expr = nullptr;
    operations = nullptr;
}

Func_Data::Func_Data(const std::string& f_expr, const std::string& d_expr, const std::string& p_expr) {
    size = 1;
    func_expr = new std::string[size];
    degree_expr = new std::string[size];
    param_expr = new std::string[size];
    operations = new std::string[size];
}

Func_Data::~Func_Data() {
    size = 0;
    delete [] func_expr;
    delete [] degree_expr;
    delete [] param_expr;
    delete [] operations;
}

bool Func_Data::insert_data(const std::string& expression, int index) {
    assert((0 <= index) && (index <= 2));
    bool flag = false;
    switch (index) {
        case (0): {
            if (func_expr == nullptr) {
                size = 1;
                delete [] func_expr;
                func_expr = new std::string[size];
                func_expr[size-1] = expression;
                break;
            } else {
                std::string* new_func_expr = new std::string[size+1];
                for (int iter = 0; iter < size; ++iter) {
                    new_func_expr[iter] = func_expr[iter];
                }
                delete [] func_expr;
                size += 1;
                func_expr = new_func_expr;
                func_expr[size-1] = expression;
                break;
            }
        }
        case (1): {
            if (degree_expr == nullptr) {
                size = 1;
                delete [] degree_expr;
                degree_expr = new std::string[size];
                degree_expr[size-1] = expression;
                break;
            } else {
                std::string* new_degree_expr = new std::string[size+1];
                for (int iter = 0; iter < size; ++iter) {
                    new_degree_expr[iter] = degree_expr[iter];
                }
                delete [] degree_expr;
                size += 1;
                degree_expr = new_degree_expr;
                degree_expr[size-1] = expression;
                break;
            }
        }
        case (2): {
            if (param_expr == nullptr) {
                size = 1;
                delete [] param_expr;
                param_expr = new std::string[size];
                param_expr[size-1] = expression;
                break;
            } else {
                std::string* new_param_expr = new std::string[size+1];
                for (int iter = 0; iter < size; ++iter) {
                    new_param_expr[iter] = param_expr[iter];
                }
                delete [] param_expr;
                size += 1;
                param_expr = new_param_expr;
                param_expr[size-1] = expression;
                break;
            }
        }
    }
    return true; //doesnt matter, cause we have assert in the beginning
}

bool Func_Data::insert_operation_data(const char& operation) {
    bool flag = true;
    const char* signs = "+-*/^ ";
    int length = 6;
    for (int iter = 0; iter < length; ++iter) {
        if (operation == signs[iter]) {
            bool flag = false;
            break;
        }
    } 
    if (flag) {
        printf("Wrong operation\n");
        return false;
    }

    if (operations == nullptr) {
        size = 1;
        operations[size-1] = operation;
    } else {
        std::string* new_operations = new std::string[size-1];
        for (int iter = 0; iter < size; ++iter) {
            new_operations[iter] = operations[iter];
        }
        delete [] operations;
        size += 1;
        operations = new_operations;
        operations[size-1] = operation;
    }
    return true;
}

Math::Math() {}

Math::~Math() {}

int Math::check_is_branch(char element) {
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

int Math::check_is_sign(char element) {
    const char* signs = "+-*/^ ";
    int length = 6;
    for (int iter = 0; iter < length; ++iter) {
        if (element == signs[iter]) {
            return iter + 1; //number of sign, 0 is reserved for nonsign symbols
        }
    }
    return 0;
}

bool Math::check_is_digit(char element) {
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
    std::map<std::string, int> branch_map = {
        {"()", 0},
        {"{}", 0},
        {"[]", 0},
        {"<>", 0},
    };
    int check = 0;
    for (int iter = 0; iter < s.size(); ++iter) {
        check = check_is_branch((s.c_str())[iter]);
        if (check) {
            switch (s.c_str()[iter]) { //TODO: write it without switch
                case ('('):
                case (')'): {
                    count += 1;
                    branch_map["()"] += check;
                    break;
                }
                case ('{'):
                case ('}'): {
                    count += 1;
                    branch_map["{}"] += check;
                    break;
                }
                case ('['):
                case (']'): {
                    count += 1;
                    branch_map["[]"] += check;
                    break;
                }
                case ('<'):
                case ('>'): {
                    count += 1;
                    branch_map["<>"] += check;
                    break;
                }
            }
        }
    }
    bool condition = {
        (branch_map["()"] == 0) && 
        (branch_map["{}"] == 0) &&
        (branch_map["[]"] == 0) &&
        (branch_map["<>"] == 0) &&
        (count != 0)
    };
    return condition;
}

int Math::count_segments(std::string expr) {
    assert(check_br_in_expr(expr));
    int count = 0;
    int flag_closed_branch = 0;
    int sign = -1, branch = -1;
    for (int iter = 0; iter < expr.size(); ++iter) {
        sign = check_is_sign(expr[iter]);
        branch = check_is_branch(expr[iter]);
        if (sign && !flag_closed_branch) {//only if all branches are closed: cos(x) + (sin(x)+cos(x)): 2 segments
            if (iter != 0) {
                count += 1;
            }
        } else if (branch) {
            flag_closed_branch += branch;
        }
    }
    count += 1; //because signs always more than segments: a + b: 2 segmenst
    return count;
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

bool Math::func_expr(const std::string& expression, Func_Data* data) {
    //code: 0 - func , 1 - degree, 2 - arg
    int prev_expr_type = -1;
    int cur_expr_type = -1;

    int branch = 0; // opened, none, closed
    int digit = 0; // 0 - not digit, 1..10 - ok
    int sign = 0; // true false

    int start = 0;
    int end = 0;

    int cur_element_type = -1;
    int prev_element_type = -1;
    for (int iter = 0; iter < expression.size(); ++iter) {
        cur_element_type = element_type(expression[iter]);
        if (cur_element_type == 0) { //func handler
            if (cur_expr_type == -1) { // first iter
                cur_expr_type = 0;
            } else if (prev_expr_type == 0) {
                cur_expr_type = 0;
            } else {
                cur_expr_type = prev_expr_type;
            }
        }
        
        if (cur_element_type == 1) { //signs handler
            sign = check_is_sign(expression[iter]);

            if (sign == 5) { // sign: '^'
                if (cur_expr_type == -1) {
                    printf("You cant use '%s' in front of non-expression\n", expression[iter]);
                    return false;
                } else if (prev_expr_type == 0) { // expr before '^' is func: func_name...'^'
                    end = iter-1;
                    std::string info = expression.substr(start, end-start+1);
                    data->insert_data(info, prev_expr_type);
                    cur_expr_type = 1; //degree part
                }
            } else {
                if (prev_element_type == 3) {
                    int prev_element_branch_type = check_is_branch(expression[iter-1]);
                    if (prev_element_branch_type == 1) {
                        cur_expr_type = 0;
                        cur_element_type = 0;
                        //printf("%s", expression[iter]);
                        //data->insert_operation_data(expression[iter]);
                    }
                }
            }
        }
        if (cur_element_type == 2) { //digits handler
            if (cur_expr_type == -1) {
                cur_expr_type = 0;
            } else {
                if (prev_element_type == 3) {
                    cur_expr_type = prev_expr_type;    
                }
            }
        }

        if (cur_element_type == 3) { //branches handler
            branch = check_is_branch(expression[iter]);
            if (branch == -1) {
                start = iter;
                end = iter;
                if (cur_expr_type == -1) {
                    cur_expr_type = 0;
                } else if (prev_expr_type == 0) {
                    data->insert_data("1", 1); //degree value is 1 by default
                    cur_expr_type = 2; //param_type
                } else if (cur_expr_type == 1) { //degree
                    if (prev_element_type == 3) {
                        int prev_element_branch_type = check_is_branch(expression[iter-1]);
                        if (prev_element_branch_type == 1) {
                            cur_expr_type = 2;
                        }
                    } 
                }
            } else if (branch == 1) {
                if (cur_expr_type == -1) {
                    printf("Expression cant being started by %s\n", expression[iter]);
                    return false;
                } else if ((cur_expr_type == 1) && (iter == (expression.size()-1))) {
                    data->insert_data("x", 2); //param value is x by default
                }
                end = iter;
                std::string info = expression.substr(start+1, (end-1) -(start+1)+1);
                data->insert_data(info, cur_expr_type);
                
            }
        }


        prev_element_type = cur_element_type;
        prev_expr_type = cur_expr_type;
        printf("%d", cur_expr_type);
    }
    printf("\n");
    //printf("%s\n", expression.c_str()[0]);
    return true;
}

bool Math::expression(std::string expr, std::map<std::string, std::string[]> *func_arg_map) {
    assert(check_br_in_expr(expr));
    for (int iter = 0; iter < count_segments(expr); ++iter) {
        int start_segment = 0; 
        int finish_segment = 0;
        
        int sign = 0;
        int sub_expr_start = 0;
        int sub_expr_end = 0;

        assert((start_segment>0) && (finish_segment<expr.size()));
        for (int el_iter = start_segment; el_iter < finish_segment; ++el_iter) {
            sign = check_is_sign(expr[el_iter]);
            sub_expr_end += 1;
            if (sign) {
                //cal func_expr()
                if ((el_iter + 1) < expr.size()) {
                    sub_expr_start = el_iter + 1;
                    sub_expr_end = sub_expr_start;
                }
            }
        }
    }
    return true;
}

std::string Math::derivative(std::string s) {
    return std::string {s};
}