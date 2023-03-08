# RPNMathLib
Simple, RPN-based C++ math expression evaluation library.

## Building
Use CLion or CMake to build the project. 
The project is configured to build a static library and a test executable. 
The library is written in C++20.

## Usage
The library is header-only, so you can just include the header file in your project.
```cpp
#include "mathlib.h"

int main() {
    TExpressionParser parser{};
    std::cout << "Result: " << parser.ParseExpressionToFloat("(-5 + sqrt(5^2 - 4 * 1 * 4)) / (2 * 1)") << std::endl;
    return 0;
}
```
Output:
```
Result: -1
```

## Testing
Google Test (GTest) is used for testing. 
Test suite contains 100+ tests of randomly generated mathematical expressions with predefined values.
CMake project is already configured to get GTest library.

## TODO
- [ ] Add support for more operators (Factorial, Exponent, N-th root, etc.)
- [ ] Optimisation of operators checking / RPN generation
- [ ] Transform it into dynamic library
- [ ] Big cleanup