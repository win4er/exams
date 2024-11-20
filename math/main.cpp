#include "math.hpp"
#include <iostream>

int main() {
    Math handler;
    const char* expression = "";
    expression = "+)x^2(*(3)+1";
    printf("%s\n", expression);
    std::cout << handler.check_br_in_expr(expression) << std::endl;
    return 0;
}