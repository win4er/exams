#include "math.hpp"
#include <iostream>

int main() {
    Math handler;
    const char* expression = "";
    expression = "x^2 + 1";
    printf("%s\n", expression);

    Func_Data obj;
    handler.expression(expression, &obj);
    printf("Handler is done\n");
    printf("size: %d", obj.count);
    for (int iter = 0; iter < obj.count; ++iter) {
        printf("%c, ", obj.operations[iter]);
        printf("%s, ", obj.func_expr[iter].c_str());
        printf("%s, ", obj.degree_expr[iter].c_str());
        printf("%s", obj.param_expr[iter].c_str());
    }
    printf("\n");
    return 0;
}