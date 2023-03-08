#include <iostream>
#include "mathlib.h"

int main() {
    std::string exp1 = "(-5+sqrt(5^2-4*1*4))/(2*1)";
    TExpressionParser parser{};
    double result = parser.ParseExpressionToFloat(exp1);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
