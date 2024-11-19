#include "math.hpp"
#include <iostream>

int main() {
    Math handler;
    const char* expression = "";
    expression = "cos^(3*x)(x+1)";
    Func_Data obj;
    printf("%s\n", expression);
    handler.func_expr(expression, &obj);
    int arg1 = obj.size; 
    int arg2 = obj.func_expr_size;
    int arg3 = obj.degree_expr_size;
    int arg4 = obj.param_expr_size;
    int arg5 = obj.operations_size;
    printf("size:%d, func_expr_size:%d, degree_expr_size:%d, param_expr_size:%d, operations_size:%d\n", arg1, arg2, arg3, arg4, arg5);
    for (int iter = 0; iter < obj.size; ++iter) {
        printf("%c, ", obj.operations[iter]);
        printf("%s, ", obj.func_expr[iter].c_str());
        printf("%s, ", obj.degree_expr[iter].c_str());
        printf("%s\n", obj.param_expr[iter].c_str());
    }

    return 0;
}