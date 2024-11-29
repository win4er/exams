#include "math.hpp"
#include <iostream>

int main() {
    Math handler;
    std::string expression = "cos(x)+1+cos^2(3+x+(9+x))*sin(x+1)-4";
    std::cout << expression << std::endl;
    int* ar = new int[expression.size()];
    handler.expression_type_data(expression, ar);
    for (int i=0; i<expression.size(); ++i) {
        std::cout << ar[i];
    }
    std::cout << std::endl;
    Func_Data obj;
    handler.expression(expression, &obj);
    obj.show();
    Func_Data f_data;
    std::string expr = "cos(x)";
    handler.expression(expr, &f_data);
    Func_Data out_data;
    handler.stupid_derivative(&f_data, &out_data);
    return 0;
}