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
                operations[index] = expression[0];
                break;
            }
        }
    } else if (index == count) { // + 1 new func_data
        if (count == 0) {
            delete [] func_expr;
            delete [] degree_expr;
            delete [] param_expr;
            delete [] operations;
            count += 1;
            std::string* func_expr = new std::string[count];
            std::string* degree_expr = new std::string[count];
            std::string* param_expr = new std::string[count];
            char* new_operations = new char[count];
            func_expr[0] = "none";
            degree_expr[0] = "1";
            param_expr[0] = "none";
            operations[0] = '+';
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
                    operations[index] = expression[0];
                    break;
                }
            }
        } else {
            count += 1;
            std::string* new_func_expr = new std::string[count];
            std::string* new_degree_expr = new std::string[count];
            std::string* new_param_expr = new std::string[count];
            char* new_operations = new char[count];
            for (int iter=0; iter < (count-1); ++iter) {
                new_func_expr[iter] = func_expr[iter];
                new_degree_expr[iter] = degree_expr[iter];
                new_param_expr[iter] = param_expr[iter];
                operations[iter] = operations[iter];
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
            operations[index] = '+';   
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
                    operations[index] = expression[0];
                    break;
                }
            }
        }
    } else {
        printf("There is %d func_data expressions, you can add 1 more, not %d more", count, count-index-1);
        return false;
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
        (count != 0)
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

bool Math::expression(const std::string& expression, Func_Data* data) {
    assert(check_br_in_expr(expression));
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
                    //data->insert_data("+", prev_expr_type); // sign data
                    break;
                }
                case (1): { // sign_expr_handler
                    cur_expr_type = 3;
                    cur_branch_expr_status = false;
                    sign = check_is_sign(expression[iter]);
                    start = iter; // start from sign_expr;
                    if ((sign > 2) && (sign != 6)) {
                        printf("\nYou cant start an exception using %c\n", expression[iter]);
                        return false;
                    } else { // i know about return above this line, but i need 'readable' code
                        std::string sign_data = expression.substr(start, 1);
                        //data->insert_data(sign_data, cur_expr_type);
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
                        printf("\nYou cant start an expression using %c\n", expression[iter]);
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
                    std::string sign_data = expression.substr(start, 1); //may be wrong
                    //data->insert_data(sign_data, cur_expr_type);
                    if (cur_branch_expr_status) {
                        cur_expr_type = prev_expr_type;
                    } else {
                        cur_expr_type = 3;
                        switch (prev_expr_type) {
                            case (0): { // func_name_handler
                                std::string func_name_data = expression.substr(start+1, (end-1)-(start+1)+1); // func_name is between 'sign' and 'sign'
                                //data->insert_data(func_name_data, prev_expr_type);
                                break;
                            }
                            case (1): { // degree_expr_handler
                                // we store data before degree statement, so we have to store degree_expr and arg_expr data, but arg_expr is none by default
                                std::string degree_expr_data = expression.substr(start+1, (end-1)-(start+1)+1); // degree_expr is also between 'sign' and 'sign'
                                //data->insert_data(degree_expr_data, prev_expr_type);
                                break;
                            }
                            case (2): { //arg_expr_handler
                                std::string param_expr_data = expression.substr(start+1, (end-2)-(start+1)+1); // param_expr is between 'branch' and 'branch' + 'sign'
                                //data->insert_data(param_expr_data, prev_expr_type);
                                break;
                            }
                            case (3): {
                                printf("\nSign '%c' before '%c', two signes in a row are not allowed\n", expression[iter-1], expression[iter]);
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
                                    std::string degree_expr_data = expression.substr(start+1, (end-1)-(start+1)+1); // degree_expre is between 'sign' and 'branch'
                                    //data->insert_data(degree_expr_data, prev_expr_type);
                                    break;
                                }
                                case (2): { // arg_expr_handler
                                    printf("\nFound branch expression in breanch expression at '%d' position(counts from 1)\n", iter+1); // recursive call?
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
                                    printf("\nDoesnt seem to be real, if you use '%c' after func_name\n", expression[iter]);
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
                                    printf("\nFound sign '%c' before branch '%c', without func_expr after sign\n", expression[iter-1], expression[iter]);
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
            if (prev_expr_type == 3) {
                cur_expr_type = 0;
            } else {
                cur_expr_type = prev_expr_type;
            }
            switch (cur_element_type) {
                case (0): { // func_name_expr_handler
                    end = iter;
                    std::string func_name_expr = expression.substr(start+1, end-(start+1)+1);
                    //data->insert_data(func_name_expr, cur_expr_type);
                    break;
                }
                case (1): { // sign_expr_handler
                    printf("\nSeems wrong last symbols is '%c'\n", expression[iter]);
                    break;
                }
                case (2): { // digit_expr_handler
                    end = iter;
                    if (cur_branch_expr_status) {
                        printf("\nBranch is still open, but its the end of expression\n");
                        break;
                    }
                    switch (cur_expr_type) {
                        case (0): { // func_expr_handler
                            std::string func_expr_data = expression.substr(start+1, end-(start+1)+1);
                            //data->insert_data(func_expr_data, cur_expr_type);
                            break;
                        }
                        case (1): { // degree_expr_handler
                            std::string degree_expr_data = expression.substr(start+1, end-(start+1)+1);
                            //data->insert_data(degree_expr_data, cur_expr_type);
                            break;
                        }
                        case (2): { // arg_expr_handler
                            std::string param_expr_data = expression.substr(start+1, end-(start+1)+1);
                            //data->insert_data(param_expr_data, cur_expr_type);
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
                        printf("\nYou cant use opening branch '%c' at the end of expr\n", expression[iter]);
                        return false;
                    } else if (branch == 1) {
                        end = iter;
                        switch (cur_expr_type) {
                            case (0): { // func_expr_handler
                                std::string func_expr_data = expression.substr(start+1+1, (end-1)-(start+1+1)+1);
                                //data->insert_data(func_expr_data, cur_expr_type);
                                break;
                            }
                            case (1): { // degree_expr_handler
                                std::string degree_expr_data = expression.substr(start+1+1, (end-1)-(start+1+1)+1);
                                //data->insert_data(degree_expr_data, cur_expr_type);                                
                                break;
                            }
                            case (2): { // param_expr_handler
                                std::string param_expr_data = expression.substr(start+1+1, (end-1)-(start+1)+1);
                                //data->insert_data(param_expr_data, cur_expr_type);
                                break;
                            }
                            case (3): { // separator_expr_handler
                                printf("\nUsing closing branch '%c' in front of separator sign '%c' is not allowed\n", expression[iter], expression[iter-1]);
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

std::string Math::derivative(std::string s) {
    return std::string {s};
}