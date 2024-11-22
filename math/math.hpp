#ifndef MATH_HPP
#define MATH_HPP

#include <cstdio>
#include <string>
#include <assert.h>
#include <map>

struct Func_Data {
    public:
        int count;
        std::string* func_expr;
        std::string* degree_expr;
        std::string* param_expr;
        std::string* operations;
        Func_Data();
        ~Func_Data();
        bool insert_data(const std::string& expr, int info_type, int index); //info_type 0 - f_expr, 1 - d_expr, 2 - p_expr, 3 - operation
};

class Math {
    private:
    public:
        Math();
        ~Math();
        int check_is_branch(char element); //-1 opeing branch, 1 closing branch, 0 zero branches
        int check_is_sign(char element);
        bool check_is_digit(char element);
        bool check_br_in_expr(const std::string& expr); // zero branches is also fine, main point is get 'right' string
        //'right' string: cos(x)+sin(x)+(tg^(2x)(2x)+3)+4
        // func_expr: func_name, ^(degree), (args)
        // func_expr: func_name, ^number, (args)
        int element_type(const char& element);
        bool expression_type_data(const std::string& expression, int* expression_type_data);
        bool expression(const std::string& expression, Func_Data *data);
        //all non math funcs should be private later
        std::string derivative(std::string s);

};


#endif