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
    return 0;
}