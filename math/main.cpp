#include "math.hpp"
#include <iostream>

int main() {
    Math handler;
    std::string expression = "";
    expression = "(sin^2+3)+cos^(3+3)(3+x)+sin(x)+x^(3+4+x^2)+sin^(x^2+3)+x*90+x^(600-x)"; //"(sin^2+3)+cos^(3+3)(3+x)+sin(x)+x^(3+4+x^2)+sin^(x^2+3)+x*90+x^(600-x)"
    printf("%s\n", expression.c_str());

    Func_Data obj;
    int* data_expr = new int[expression.size()];
    handler.expression_type_data(expression, data_expr);
    for (int i=0; i<expression.size(); ++i) {
        std::cout << data_expr[i];
    }
    std::cout << std::endl;
    handler.expression(expression, &obj);
    for (int i=0; i<obj.count;++i) {
        printf("%s\t", obj.func_expr[i].c_str());
        printf("%s\t", obj.degree_expr[i].c_str());
        printf("%s\t", obj.param_expr[i].c_str());
        printf("%s\t\n", obj.operations[i].c_str());
    }
    printf("\n");
    return 0;
}