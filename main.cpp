#include <iostream>
#include "mathlib.h"

int main() {
    // Prompt the user for input
//    std::string input;
//    std::cout << "Enter a math expression: ";
//    getline(std::cin, input);

    // Parse the expression and print the result
//    std::string exp1 = "(-5+sqrt(5^2-4*1*4))/(2*1)";
    std::string  exp1 = "27 ^ (1 / 3)";
    std::string exp2 = "250 + (500 * 2 - 250) - 250 * 4";
    TExpressionParser parser{};
    double result = parser.ParseExpressionToFloat(exp1);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
