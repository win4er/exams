#include "math.hpp"
#include <iostream>

int main() {
    // Math handler;
    // Func_Data out_data;
    // std::string expr = "((x+3+2))^2";
    // handler.expression(expr, &out_data);
    // std::cout << expr << std::endl;
    // handler.show_expression_type_data(expr);
    // out_data.show();
    // std::cout << handler.stupid_derivative(expr) << std::endl;
    std::string expr = "((x+3+2))";
    Math handler;
    std::cout << handler.make_it_branched(expr) << std::endl;
    std::cout << handler.make_it_unbranched(expr) << std::endl;
    return 0;
}