//
// Created by cumbala on 3/1/2023.
//

#include <cmath>
#include <string>
#include <algorithm>

#ifndef PSMATHLIB_MATHLIB_H
#define PSMATHLIB_MATHLIB_H

#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <regex>
#include <utility>
#include <iomanip>
#include <sstream>

enum TAssociativity {
    None, Left, Right
};

struct TOperator {
    char iOperator;
    int Precedence;
    TAssociativity Associativity;

    [[nodiscard]] std::string ToString() const {
        return { iOperator };
    }
    
    explicit operator std::string() const { return ToString(); }
    
    std::ostream & operator<<(std::ostream &os) const {
        return os << ToString();
    }

    bool operator==(const char &rhs) const {
        return iOperator == rhs;
    }
    
    bool operator==(const TOperator &rhs) const {
        return iOperator == rhs.iOperator;
    }
};

const std::string scOperators = "^*/+-()";
const std::string FloatForm = "####################.%s";
const std::vector<TOperator> Operators = {
        {'^', 4, TAssociativity::Right},
        {'*', 3, TAssociativity::Left},
        {'/', 3, TAssociativity::Left},
        {'+', 2, TAssociativity::Left},
        {'-', 2, TAssociativity::Left},
        {'(', 1, TAssociativity::None},
        {')', 1, TAssociativity::None},
};

class TExpressionParser {
private:

//    int CheckDepth(const std::string& S) {
//        std::stack<char> st;
//        for (auto& c : S) {
//
//        }
//        return 0;
//    }
//
//    bool IsEncapsulated(const std::string& S) {
//        if (S[0] == '(' && S[S.length() - 1] == ')') {
//            // remove brackets to temp variable
//            std::string temp = S.substr(1, S.length() - 2);
//            // check if temp is encapsulated
//            return CheckDepth(temp) == 0;
//        }
//
//        return false;
//    }

//    static TOperator FindOperator(char Ch) {
//        auto iter = std::find_if(Operators.begin(), Operators.end(), [Ch](const auto& op) {
//            return op.iOperator == Ch;
//        });
//
//        if (iter == Operators.end()) {
//            return nullptr;
//        }
//
//        return *iter;
//    }
    bool isOperator(std::string c) {
        return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
    }

    bool isOperator(char c) {
        return isOperator(std::string(1, c));
    }

    bool leftAssoc(std::string c) {
        return c != "^";
    }

    bool leftAssoc(char c) {
        return leftAssoc(std::string(1, c));
    }

    int priority(char c) {
        switch (c) {
            case '^': return 3;
            case '*':
            case '/': return 2;
            case '+':
            case '-': return 1;
            default: return 0;
        }
    }

    int priority(std::string c) {
        return priority(c[0]);
    }

    int rightPriority(char c) {
        switch (c) {
            case '+': return 1;
            case '-': return 2;
            case '*': return 3;
            case '/': return 4;
            case '^': return 5;
            default: return 0;
        }
    }

    /// Recursive function to replace sqrt() with
    /// it's power representation\n
    /// sqrt(12) -> 12^(1/2)\n
    /// sqrt(12 + 3) -> (12 + 3)^(1/2)\n
    std::string ReplaceSqrt(std::string s) {
        std::string res;
        size_t pos = s.find("sqrt(");
        int Depth = 0;
        if (pos != std::string::npos) {
            pos += 5;
            for (size_t i = pos; i < s.length(); i++) {
                if (s[i] == ')' && Depth == 0) {
                    break;
                }

                if (s[i] == '(') Depth++;
                if (s[i] == ')') Depth--;

                res += s[i];
            }

            s = s.replace(pos - 5, res.length() + 6, "(" + res + ")^(1/2)");

            if (s.find("sqrt(") != std::string::npos) {
                s = ReplaceSqrt(s);
            }

            return s;
        }

        return s;
    }
    
    int _pos = 0;
    std::string nextToken(std::string &expr) {
        while (_pos < expr.length() && expr[_pos] == ' ')
            _pos++;

        if (_pos == expr.length())
            return "";

        std::string b;

        while (
                _pos < expr.length()
            &&  expr[_pos] == ' '
            &&  expr[_pos] != '('
            &&  expr[_pos] != ')'
            ||  isdigit(expr[_pos])
            ||  (expr[_pos] == '.')
            ||  (
                    !isdigit(expr[_pos - 1])
                &&  expr[_pos - 1] != ')'
                &&  expr[_pos] == '-'
                &&  isdigit(expr[_pos + 1])
            )
        )
            b += expr[_pos++];

        if (!b.empty())
            return b;

        return { expr[_pos++] };
    }

    std::string CreateRPN(std::string input) {
        std::vector<std::string> S, O;
        std::string tok;

        input.erase(remove(input.begin(), input.end(), ' '), input.end());
        input = ReplaceSqrt(input);
        input = std::regex_replace(input, std::regex("--"), "+");

         while (!(tok = nextToken(input)).empty()) {
            if (tok == "(")
                S.push_back(tok);
            else if (tok == ")") {
                while (!S.empty() && S[S.size() - 1] != "(") {
                    O.push_back(S[S.size() - 1]);
                    S.pop_back();
                }
                if (S.empty())
                    throw std::invalid_argument("Mismatched parentheses");
                S.pop_back();
            } else if (isOperator(tok)) {
                while (!S.empty() && isOperator(S[S.size() - 1])
                       && ((leftAssoc(tok) && priority(tok) <= priority(S[S.size() - 1]))
                           || (!leftAssoc(tok) && priority(tok) < priority(S[S.size() - 1])))) {
                    O.push_back(S[S.size() - 1]);
                    S.pop_back();
                }
                S.push_back(tok);
            } else
                O.push_back(tok);
        }

        while(!S.empty()) {
            if (!isOperator(S[S.size() - 1]))
                throw std::invalid_argument("Mismatched parentheses");
            O.push_back(S[S.size() - 1]);
            S.pop_back();
        }

        if (O.empty())
            throw std::invalid_argument("Invalid expression");

        std::string output;

        for (int j = 0; j < O.size(); j++) {
            if (j != 0) output += " ";
            output += O[j];
        }

        return output;
    }

    [[nodiscard]] auto GetDecFormat() const {
        return std::string(MaxDecimals, '#');
    }
    
    static double ProcessRPN(std::string rpn) {
        std::stack<double> stack;
        std::vector<std::string> rpnList;
        std::istringstream iss(rpn);
        std::string token;
        const std::string cOperators = "^+-*/";

        while (std::getline(iss, token, ' ')) {
            if (!token.empty())
                rpnList.push_back(token);
        }

        stack.push(std::stod(rpnList[0]));
        for (int i = 1; i < rpnList.size(); i++) {
            if (rpnList[i].empty()) {
                continue;
            }
            if (cOperators.find(rpnList[i]) != std::string::npos) {
                double op1 = stack.top();
                stack.pop();

                if (stack.empty() && rpnList[rpnList.size() - 1] == "-") return -op1;
                
                double op2 = stack.top();
                stack.pop();
                switch (rpnList[i][0]) {
                    case '+':
                        stack.push(op2 + op1);
                        break;
                    case '-':
                        stack.push(op2 - op1);
                        break;
                    case '*':
                        stack.push(op2 * op1);
                        break;
                    case '/':
                        stack.push(op2 / op1);
                        break;
                    case '^':
                        stack.push(pow(op2, op1));
                        break;
                }
            } else {
                stack.push(std::stod(rpnList[i]));
            }
        }

        return stack.top();
    }
public:
    // FFormat is ignored, since cpp does not seem to have "TFormatSettings"
    char DecimalSeparator{};
    
    int MaxDecimals = 8;
    
    double ParseExpressionToFloat(std::string Expression) {
        // Reversed polish notation
        std::string RevPolNotation = CreateRPN(std::move(Expression));
        return ProcessRPN(RevPolNotation);
    }
    
    std::string ParseExpressionToString(std::string Expression) {
        std::string revPolNotation = CreateRPN(std::move(Expression));
        double result = ProcessRPN(revPolNotation);
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(MaxDecimals) << result;
        return stream.str();
    }
};


#endif //PSMATHLIB_MATHLIB_H
