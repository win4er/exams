#include "math.hpp"

Func_Data::Func_Data() {
    size = 0;
    func_expr_size = 0;
    degree_expr_size = 0;
    param_expr_size = 0;
    operations_size = 0;
    func_expr = nullptr;
    degree_expr = nullptr;
    param_expr = nullptr;
    operations = nullptr;
}

Func_Data::Func_Data(const std::string& f_expr, const std::string& d_expr, const std::string& p_expr) {
    size = 1;
    func_expr_size = 1;
    degree_expr_size = 1;
    param_expr_size = 1;
    operations_size = 1;
    func_expr = new std::string[func_expr_size];
    degree_expr = new std::string[degree_expr_size];
    param_expr = new std::string[param_expr_size];
    operations = new char[operations_size];
    operations[size-1] = '0'; //fist operation means nothing
}

Func_Data::~Func_Data() {
    size = 0;
    func_expr_size = 0;
    degree_expr_size = 0;
    param_expr_size = 0;
    operations_size = 0;
    delete [] func_expr;
    delete [] degree_expr;
    delete [] param_expr;
    delete [] operations;
}

bool Func_Data::insert_data(const std::string& expression, int index) {
    assert((0 <= index) && (index <= 3));
    bool flag = false;
    switch (index) { //ok, now i dont have to fix ALL of this shit, but later, it will be better
        case (0): {
            if (func_expr == nullptr) {
                assert((size==0)||(size==1));
                delete [] func_expr;
                size = 1;
                func_expr = new std::string[size];
                func_expr[0] = expression;
                func_expr_size = 1;
                break;
            } else {
                func_expr_size += 1;
                if (func_expr_size > size) {
                    assert((func_expr_size-size)==1);
                    std::string* new_func_expr = new std::string[size+1];
                    std::string* new_degree_expr = new std::string[size+1];
                    std::string* new_param_expr = new std::string[size+1];
                    char* new_operations = new char[size+1];
                    for (int iter = 0; iter < size; ++iter) {
                        new_func_expr[iter] = func_expr[iter];
                        new_degree_expr[iter] = degree_expr[iter];
                        new_param_expr[iter] = param_expr[iter];
                        new_operations[iter] = operations[iter]; 
                    }
                    delete [] func_expr;
                    delete [] degree_expr;
                    delete [] param_expr;
                    delete [] operations;
                    
                    size += 1;
                    
                    func_expr = new_func_expr;
                    degree_expr = new_degree_expr;
                    param_expr = new_param_expr;
                    operations = new_operations;

                    func_expr[size-1] = expression;
                    degree_expr[size-1] = "1";
                    param_expr[size-1] = "none";
                    operations[size-1] = ' ';
                    break;
                } else if (func_expr_size == size) {
                    std::string* new_func_expr = new std::string[func_expr_size];
                    for (int iter = 0; iter < func_expr_size-1; ++iter) {
                        new_func_expr[iter] = func_expr[iter];
                    }
                    delete [] func_expr;
                    func_expr = new_func_expr;
                    func_expr[size-1] = expression;
                    func_expr_size += 1;
                    break;
                }
            }
        }
        case (1): {
            if (degree_expr == nullptr) {
                assert((size==0)||(size==1));
                delete [] degree_expr;
                size = 1;
                degree_expr = new std::string[size];
                degree_expr[0] = expression;
                degree_expr_size = 1;
                break;
            } else {
                degree_expr_size += 1;
                if (degree_expr_size > size) {
                    assert((degree_expr_size-size)==1);
                    std::string* new_func_expr = new std::string[size+1];
                    std::string* new_degree_expr = new std::string[size+1];
                    std::string* new_param_expr = new std::string[size+1];
                    char* new_operations = new char[size+1];
                    for (int iter = 0; iter < size; ++iter) {
                        new_func_expr[iter] = func_expr[iter];
                        new_degree_expr[iter] = degree_expr[iter];
                        new_param_expr[iter] = param_expr[iter];
                        new_operations[iter] = operations[iter]; 
                    }
                    delete [] func_expr;
                    delete [] degree_expr;
                    delete [] param_expr;
                    delete [] operations;
                    
                    size += 1;
                    
                    func_expr = new_func_expr;
                    degree_expr = new_degree_expr;
                    param_expr = new_param_expr;
                    operations = new_operations;

                    func_expr[size-1] = "none";
                    degree_expr[size-1] = expression;
                    param_expr[size-1] = "none";
                    operations[size-1] = ' ';
                    break;
                } else if (degree_expr_size == size) {
                    std::string* new_degree_expr = new std::string[degree_expr_size];
                    for (int iter = 0; iter < degree_expr_size-1; ++iter) {
                        new_degree_expr[iter] = degree_expr[iter];
                    }
                    delete [] degree_expr;
                    degree_expr = new_degree_expr;
                    degree_expr[size-1] = expression;
                    degree_expr_size += 1;
                    break;
                }
            }
        }
        case (2): {
            if (param_expr == nullptr) {
                assert((size==0)||(size==1));
                delete [] param_expr;
                size = 1;
                param_expr = new std::string[size];
                param_expr[0] = expression;
                param_expr_size = 1;
                break;
            } else {
                param_expr_size += 1;
                if (param_expr_size > size) {
                    assert((param_expr_size-size)==1);
                    std::string* new_func_expr = new std::string[size+1];
                    std::string* new_degree_expr = new std::string[size+1];
                    std::string* new_param_expr = new std::string[size+1];
                    char* new_operations = new char[size+1];
                    for (int iter = 0; iter < size; ++iter) {
                        new_func_expr[iter] = func_expr[iter];
                        new_degree_expr[iter] = degree_expr[iter];
                        new_param_expr[iter] = param_expr[iter];
                        new_operations[iter] = operations[iter]; 
                    }
                    delete [] func_expr;
                    delete [] degree_expr;
                    delete [] param_expr;
                    delete [] operations;
                    
                    size += 1;
                    
                    func_expr = new_func_expr;
                    degree_expr = new_degree_expr;
                    param_expr = new_param_expr;
                    operations = new_operations;

                    func_expr[size-1] = "none";
                    degree_expr[size-1] = "1";
                    param_expr[size-1] = expression;
                    operations[size-1] = ' ';
                    break;
                } else if (param_expr_size == size) {
                    std::string* new_param_expr = new std::string[param_expr_size];
                    for (int iter = 0; iter < param_expr_size-1; ++iter) {
                        new_param_expr[iter] = param_expr[iter];
                    }
                    delete [] param_expr;
                    param_expr = new_param_expr;
                    param_expr[size-1] = expression;
                    param_expr_size += 1;
                    break;
                }
            }
        }
        case (3): {
            bool flag = true;
            const char* signs = "+-*/^ ";
            int length = 6;
            assert(expression.size()==1);
            const char& operation = expression[0];
            for (int iter = 0; iter < length; ++iter) {
                if (operation == signs[iter]) {
                    flag = false;
                    break;
                }
            } 
            if (flag) {
                printf("Wrong operation: '%c'\n", operation);
                break;
            }

            if (operations == nullptr) {
                assert((size == 0)||(size == 1));
                delete [] operations;
                size = 1;
                char* new_operations = new char[size];
                operations = new_operations;
                operations[0] = operation;
                operations_size = 1;
                break;
            } else {
                operations_size += 1;
                if (operations_size > size) {
                    assert((operations_size-size)==1);
                    std::string* new_func_expr = new std::string[size+1];
                    std::string* new_degree_expr = new std::string[size+1];
                    std::string* new_param_expr = new std::string[size+1];
                    char* new_operations = new char[size+1];
                    for (int iter = 0; iter < size; ++iter) {
                        new_func_expr[iter] = func_expr[iter];
                        new_degree_expr[iter] = degree_expr[iter];
                        new_param_expr[iter] = param_expr[iter];
                        new_operations[iter] = operations[iter]; 
                    }
                    delete [] func_expr;
                    delete [] degree_expr;
                    delete [] param_expr;
                    delete [] operations;
                                    
                    size += 1;
                                    
                    func_expr = new_func_expr;
                    degree_expr = new_degree_expr;
                    param_expr = new_param_expr;
                    operations = new_operations;

                    func_expr[size-1] = "none";
                    degree_expr[size-1] = "1";
                    param_expr[size-1] = "none";
                    operations[size-1] = operation;
                    break;
                } else if (operations_size == size) {
                    char* new_operations = new char[operations_size];
                    for (int iter = 0; iter < operations_size-1; ++iter) {
                        new_operations[iter] = operations[iter];
                    }
                    delete [] operations;
                    operations = new_operations;
                    operations[size-1] = operation;
                    operations_size += 1;
                    break;
                }
            }
        }
    }
    return true; //doesnt matter, cause we have assert in the beginning
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
    //TODO: write it, considering this: }{ is wrong, 
    //actually u can count += branch, and if count > 0 at ')', that means its broken expr
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
    //code: 0 - func , 1 - degree, 2 - arg, 3 - sign_separator
    int prev_expr_type = -1;
    int cur_expr_type = -1;
    bool cur_branch_expr_status = false;
    bool prev_branch_expr_status = false;

    int branch = 0; // opened, none, closed
    int digit = 0; // 0 - not digit, 1..10 - ok
    int sign = 0; // true false

    int start = 0;
    int end = 0;

    int cur_element_type = -1;
    int prev_element_type = -1;
    for (int iter = 0; iter < expression.size(); ++iter) {
        cur_element_type = element_type(expression[iter]);

        if (iter == 0) {
            switch (cur_element_type) {
                case (0): { // func_expr_handler
                    cur_expr_type = 0;
                    prev_expr_type = 3; // idea? 3.....3......3, separator of func_expr
                    cur_branch_expr_status = false;
                    start = iter-1; // start from sign_expr; then we add 1 to start and everything will be ok
                    data->insert_data("+", prev_expr_type); // sign data
                    break;
                }
                case (1): { // sign_expr_handler
                    cur_expr_type = 3;
                    cur_branch_expr_status = false;
                    sign = check_is_sign(expression[iter]);
                    start = iter; // start from sign_expr;
                    if ((sign > 2) && (sign != 6)) {
                        printf("You cant start an exception using %s\n", expression[iter]);
                        return false;
                    } else { // i know about return above this line, but i need 'readable' code
                        std::string sign_data = expression.substr(expression[start], 1);
                        data->insert_data(sign_data, cur_expr_type);
                    }
                    break;
                }
                case (2): { // digit_expr_handler
                    cur_expr_type = 0;
                    cur_branch_expr_status = false;
                    start = iter;
                    break;
                }
                case (3): { // branch_expr_handler
                    branch = check_is_branch(expression[iter]);
                    if (branch == -1) {
                        cur_expr_type = 0;
                        start = iter;
                        cur_branch_expr_status = true;
                    } else {
                        printf("You cant start an expression using %s\n", expression[iter]);
                        return false;
                    }
                    break;
                }
            }
        } else if ((iter != 0) && (iter != (expression.size()-1))) {
            switch (cur_element_type) {
                case (0): { // func_expr_handler
                    cur_branch_expr_status = prev_branch_expr_status;
                    end = iter;
                    if (prev_expr_type == 3) {
                        cur_expr_type = 0;
                    } else {
                        assert(prev_element_type == 0);
                        cur_expr_type = prev_expr_type;
                    }
                    break;
                }
                case (1): { // sign_expr_handler
                    cur_branch_expr_status = prev_branch_expr_status;
                    if (prev_branch_expr_status) {
                        if (prev_element_type == 3) {
                            branch = check_is_branch(expression[iter]);
                            if (branch == 1) {
                                cur_branch_expr_status = false;
                            } else {
                                cur_branch_expr_status = prev_branch_expr_status; 
                                // i know that cur_br... already has this value,
                                // but this way of code is more 'readable'
                            }
                        }
                    }
                    start = iter; //may be wrong
                    end = iter;
                    std::string sign_data = expression.substr(expression[start], 1); //may be wrong
                    data->insert_data(sign_data, cur_expr_type);
                    if (cur_branch_expr_status) {
                        cur_expr_type = prev_expr_type;
                    } else {
                        cur_expr_type = 3;
                        switch (prev_expr_type) {
                            case (0): { // func_name_handler
                                std::string func_name_data = expression.substr(expression[start+1], (end-1)-(start+1)+1); // func_name is between 'sign' and 'sign'
                                data->insert_data(func_name_data, prev_expr_type);
                                break;
                            }
                            case (1): { // degree_expr_handler
                                // we store data before degree statement, so we have to store degree_expr and arg_expr data, but arg_expr is none by default
                                std::string degree_expr_data = expression.substr(expression[start+1], (end-1)-(start+1)+1); // degree_expr is also between 'sign' and 'sign'
                                data->insert_data(degree_expr_data, prev_expr_type);
                                break;
                            }
                            case (2): { //arg_expr_handler
                                std::string param_expr_data = expression.substr(expression[start+1], (end-2)-(start+1)+1); // param_expr is between 'branch' and 'branch' + 'sign'
                                data->insert_data(param_expr_data, prev_expr_type);
                                break;
                            }
                            case (3): {
                                printf("Sign '%s' before '%s', two signes in a row are not allowed\n", expression[iter-1], expression[iter]);
                                return false;
                                break;
                            }
                        }
                    }
                    start = iter;
                    break;
                }
                case (2): { // digit_expr_handler
                    cur_expr_type = prev_expr_type;
                    cur_branch_expr_status = prev_branch_expr_status;
                    end = iter;
                    break;
                }
                case (3): { // branch_expr_handler
                    branch = check_is_branch(expression[iter]);
                    cur_branch_expr_status = true;
                    switch (branch) {
                        case (-1): { // opening branch
                            start = iter;
                            switch (prev_expr_type) {
                                case (0): { // func_expr_handler
                                    cur_expr_type = 2;
                                    break;
                                }
                                case (1): { // degree_expr_handler
                                    cur_expr_type = 2;
                                    std::string degree_expr_data = expression.substr(expression[start+1], (end-1)-(start+1)+1); // degree_expre is between 'sign' and 'branch'
                                    data->insert_data(degree_expr_data, prev_expr_type);
                                    break;
                                }
                                case (2): { // arg_expr_handler
                                    printf("Found branch expression in breanch expression at '%d' position(counts from 1)\n", iter+1); // recursive call?
                                    return false;
                                    break;
                                }
                                case (3): { // sign_separator_handler
                                    cur_expr_type = 0;
                                    break;
                                }
                                
                            }
                            break;
                        }
                        case (1): { // closing branch
                            end = iter;
                            switch (prev_expr_type) { // func_expr_handler
                                case (0): {
                                    printf("Doesnt seem to be real, if you use '%s' after func_name\n", expression[iter]);
                                    return false;
                                    break;
                                }
                                case (1): { // degree_expr_handler
                                    break;
                                }
                                case (2): { // arg_expr_handler
                                    break;
                                }
                                case (3): { // sign_separator_handler
                                    printf("Found sign '%s' before branch '%s', without func_expr after sign\n", expression[iter-1], expression[iter]);
                                    return false;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        } else if (iter == (expression.size()-1)) {
            switch (cur_element_type) {
                if (prev_expr_type == 3) {
                    cur_expr_type = 0;
                } else {
                    cur_expr_type = prev_expr_type;
                }
                case (0): { // func_name_expr_handler
                    end = iter;
                    std::string func_name_expr = expression.substr(expression[start+1], end-(start+1)+1);
                    data->insert_data(func_name_expr, cur_expr_type);
                    break;
                }
                case (1): { // sign_expr_handler
                    printf("Seems wrong last symbols is '%s'\n", expression[iter]);
                    break;
                }
                case (2): { // digit_expr_handler
                    end = iter;
                    if (cur_branch_expr_status) {
                        printf("Branch is still open, but its the end of expression\n");
                        break;
                    }
                    switch (cur_expr_type) {
                        case (0): { // func_expr_handler
                            std::string func_expr_data = expression.substr(expression[start+1], end-(start+1)+1);
                            data->insert_data(func_expr_data, cur_expr_type);
                            break;
                        }
                        case (1): { // degree_expr_handler
                            std::string degree_expr_data = expression.substr(expression[start+1], end-(start+1)+1);
                            data->insert_data(degree_expr_data, cur_expr_type);
                            break;
                        }
                        case (2): { // arg_expr_handler
                            std::string param_expr_data = expression.substr(expression[start+1], end-(start+1)+1);
                            data->insert_data(param_expr_data, cur_expr_type);
                            break;
                        }
                        case (3): { // sign_separator_expr_handler
                            break;
                        }
                    }
                    break;
                }
                case (3): { // branch_expr_handler
                    branch = check_is_branch(expression[iter]);
                    if (branch == -1) {
                        printf("You cant use opening branch '%s' at the end of expr\n", expression[iter]);
                        return false;
                    } else if (branch == 1) {
                        end = iter;
                        switch (cur_expr_type) {
                            case (0): { // func_expr_handler
                                std::string func_expr_data = expression.substr(expression[start+1+1], (end-1)-(start+1+1)+1);
                                data->insert_data(func_expr_data, cur_expr_type);
                                break;
                            }
                            case (1): { // degree_expr_handler
                                std::string degree_expr_data = expression.substr(expression[start+1+1], (end-1)-(start+1+1)+1);
                                data->insert_data(degree_expr_data, cur_expr_type);                                
                                break;
                            }
                            case (2): { // param_expr_handler
                                std::string param_expr_data = expression.substr(expression[start+1+1], (end-1)-(start+1)+1);
                                data->insert_data(param_expr_data, cur_expr_type);
                                break;
                            }
                            case (3): { // separator_expr_handler
                                printf("Using closing branch '%s' in front of separator sign '%s' is not allowed\n", expression[iter], expression[iter-1]);
                                return false;
                                break;
                            } //fuck i forgot about branches in expressions, thats why data can be stored bad, but i want to go sleep
                        }
                    }
                    break;
                }
            }
        }
        prev_element_type = cur_element_type;
        prev_expr_type = cur_expr_type;
        prev_branch_expr_status = cur_branch_expr_status;
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