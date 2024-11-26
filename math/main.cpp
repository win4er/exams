#include "math.hpp"
#include <iostream>

int main() {
    Math handler;
    //std::cout << "result: " << handler.check_is_const_expr("345") << std::endl;
    std::string expression = "cos^2(3+x)*sin(x+1)-4";
    std::cout << expression << std::endl;
    Func_Data obj;
    handler.expression(expression, &obj);
    int* ar = new int[expression.size()];
    handler.expression_type_data(expression, ar);
    for (int i=0; i<expression.size(); ++i) {
        std::cout << ar[i];
    }
    std::cout << std::endl;
    for (int i=0; i<obj.count; ++i) {
        printf("%s\t", obj.func_expr[i].c_str());
        printf("%s\t", obj.degree_expr[i].c_str());
        printf("%s\t", obj.param_expr[i].c_str());
        printf("%s\n", obj.operations[i].c_str());
    }
    return 0;
}