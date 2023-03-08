# RPNMathLib
Simple, RPN-based C++ math expression evaluation library.

## Building
Use CLion or CMake to build the project. The project is configured to build a static library and a test executable. The library is written in C++20.

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

## TODO
- [ ] Optimisation of operators checking / RPN generation
- [ ] Transform it into dynamic library
- [ ] Big cleanup