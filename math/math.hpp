#ifndef MATH_HPP
#define MATH_HPP

#include <cstdio>
#include <string>
#include <assert.h>
#include <map>

struct Func_Data {
    public:
        int size;
        std::string* func_expr;
        std::string* degree_expr;
        std::string* param_expr;
        std::string* operations; //operations between 2 or more funcs(only '*' and '/')
        Func_Data();
        Func_Data(const std::string& f_expr, const std::string& d_expr, const  std::string& p_expr);
        ~Func_Data();
        bool insert_data(const std::string& expr, int pos); //pos 0 - f_expr, 1 - d_expr, 2 - p_expr
        bool insert_operation_data(const char& element);
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
        int count_segments(std::string expr); //count of elements in expression
        int element_type(const char& element);
        bool func_expr(const std::string& expression, Func_Data *data);
        //all non math funcs should be private later
        bool expression(std::string expr, std::map<std::string, std::string[]> *func_arg_map);
        std::string derivative(std::string s);

};


#endif