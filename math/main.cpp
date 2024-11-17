#include "math.hpp"
#include <iostream>

int main() {
    Math handler;
    const char* expression = "";
    expression = "cos^(3*x)(x+1)+x+2";
    printf("%s: %d\n", expression, handler.count_segments(expression));
    Func_Data obj;
    handler.func_expr(expression, &obj);
    for (int iter = 0; iter < obj.size; ++iter) {
        printf("%s, ", obj.func_expr[iter].c_str());
        printf("%s, ", obj.degree_expr[iter].c_str());
        printf("%s\n", obj.param_expr[iter].c_str());
    }

    return 0;
}