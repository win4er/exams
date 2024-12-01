#include "math.hpp"
#include <iostream>

int main() {
    Math handler;
    Func_Data out_data;
    std::string expr = "(x+1)^3";
    handler.expression(expr, &out_data);
    out_data.show();
    std::string result = handler.stupid_derivative(expr);
    std::cout << result << std::endl;
    return 0;
}