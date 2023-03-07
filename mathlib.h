//
// Created by lunam on 3/1/2023.
//

#include <cmath>
#include <string>
#include <algorithm>

//const std::string WHITESPACE = " \n\r\t\f\v";
//
//std::string ltrim(const std::string &s) {
//    size_t start = s.find_first_not_of(WHITESPACE);
//    return (start == std::string::npos) ? "" : s.substr(start);
//}
//
//std::string rtrim(const std::string &s) {
//    size_t end = s.find_last_not_of(WHITESPACE);
//    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
//}
//
//std::string trim(const std::string &s) {
//    return rtrim(ltrim(s));
//}

#ifndef PSMATHLIB_MATHLIB_H
#define PSMATHLIB_MATHLIB_H

//class MathExpressionParser {
//public:
//    explicit MathExpressionParser(const std::string& input): m_input(trim(input)), m_index(0) {}
//
//    double parse(const std::string &input) {
//        m_input = trim(input);
//        m_index = 0;
//        return expression();
//    }
//
//    double parse() {
//        return expression();
//    }
//
//private:
//    double expression() {
//        double result = term();
//        while (peek() == '+' || peek() == '-') {
//            char op = consume();
//            double operand = term();
//            if (op == '+') {
//                result += operand;
//            } else {
//                result -= operand;
//            }
//        }
//        return result;
//    }
//
//    double term() {
//        double result = factor();
//        while (peek() == '*' || peek() == '/') {
//            char op = consume();
//            double operand = factor();
//            if (op == '*') {
//                result *= operand;
//            } else {
//                result /= operand;
//            }
//        }
//        return result;
//    }
//
//    double factor() {
//        if (peek() == '(') {
//            consume();  // Consume the '('
//            double result = expression();
//            consume();  // Consume the ')'
//            return result;
//        } else if (peek() == '-') {
//            consume();  // Consume the '-'
//            return -factor();
//        } else if (peek() == 's') {
//            return sqrt_func();
//        } else {
//            return number();
//        }
//    }
//
//    double number() {
//        double result = parse_number();
//        if (peek() == '^') {
//            consume();  // Consume the '^'
//            double exponent = parse_number();
//            result = pow(result, exponent);
//        }
//        return result;
//    }
//
//    double sqrt_func() {
//        consume();  // Consume the 's'
//        consume();  // Consume the 'q'
//        consume();  // Consume the 'r'
//        consume();  // Consume the 't'
//        consume();  // Consume the '('
//        double result = expression();
//        consume();  // Consume the ')'
//        return sqrt(result);
//    }
//
//    char peek() {
//        return m_input[m_index];
//    }
//
//    char consume() {
//        return m_input[m_index++];
//    }
//
//    double parse_number() {
//        double result = 0;
//        while (isdigit(peek())) {
//            result = result * 10 + (consume() - '0');
//        }
//        return result;
//    }
//
//    std::string m_input;
//    int m_index;
//};

#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <regex>
#include <utility>
#include <iomanip>
#include <sstream>

#define FLOAT_TO_STRING(VAL, P) std::to_string(VAL).substr(0, std::to_string(VAL).find('.') + P + 1)

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
    std::string RemoveSqrt(std::string S, int os = 1) {
        std::transform(S.begin(), S.end(), S.begin(), ::toupper);

        // Find all SQRT() substrings using regex /SQRT\((.*?)\)/gm
        // does not work if recursive sqrt(sqrt()) is used
        std::regex self_regex("SQRT\\((.*?)\\)", std::regex_constants::ECMAScript | std::regex_constants::icase);
        std::smatch matches;

        while (std::regex_search(S, matches, self_regex)) {
            std::string match = matches[0].str();  // Get entire match
            std::string num_str = matches[1].str();  // Get number inside brackets
            double result = std::sqrt(ParseExpressionToFloat(num_str));  // Calculate square root
            std::string result_str = std::to_string(result);  // Convert result to string
            S.replace(matches.position(), match.length(), result_str);  // Replace match with result
        }

        // find first SQRT( substring
        //int start = S.find("SQRT(", os - 1);
        

        return S;

    }
    
    std::string RemoveSqr(std::string S, int os = 1) {
        std::size_t I, J, ob, cb;
        int Depth;
        std::string num, sSqr;
        std::transform(S.begin(), S.end(), S.begin(), ::toupper);
        I = S.find("SQR", os - 1);
        if (I + 1 > S.length() || I == std::string::npos) {
            return S;
        }
        Depth = 1;
        ob = S.find('(', I);
        J = ob;
        do {
            J++;
            if (S[J] == '(') {
                Depth++;
            } else if (S[J] == ')') {
                Depth--;
            }
        } while (Depth != 0);
        cb = J;
        num = S.substr(ob + 1, cb - ob - 1);
        for (auto& C : num) {
            if (scOperators.find(C) != std::string::npos) {
                num = ParseExpressionToString(num); // function ParseExpressionToString needs to be implemented
                break;
            }
        }
        sSqr = "SQR(" + num + ")";
        S = std::regex_replace(S, std::regex(sSqr), std::to_string(std::pow(std::stoi(num), 2)));
        return RemoveSqr(S, I + 1);
    }

    int CheckDepth(const std::string& S) {
        int Depth = 0;
        for (auto& C : S) {
            if (C == '(') {
                Depth++;
            } else if (C == ')') {
                Depth--;
            }
        }
        return Depth;
    }

    bool IsEncapsulated(const std::string& S) {
        if (S[0] == '(' && S[S.length() - 1] == ')') {
            // remove brackets to temp variable
            std::string temp = S.substr(1, S.length() - 2);
            // check if temp is encapsulated
            return CheckDepth(temp) == 0;
        }

        return false;
    }

    static TOperator FindOperator(char Ch) {
        auto iter = std::find_if(Operators.begin(), Operators.end(), [Ch](const auto& op) {
            return op.iOperator == Ch;
        });

        if (iter == Operators.end()) {
            throw std::invalid_argument("Invalid operator!");
        }

        return *iter;
    }

    // A Function to convert infix expression to postfix expression
    std::string CreateRPN(std::string s) {

        std::stack<char> st; //For stack operations, we are using C++ built in stack
        std::string ans = "";

        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        s = RemoveSqrt(s); // SQRT()
        s = RemoveSqr(s);
        s = std::regex_replace(s, std::regex("--"), "+");

        if (IsEncapsulated(s)) {
            s = s.substr(1, s.length() - 2);
        }

        for (auto& ch : s) {

            // If the current character is an operand, add it to our answer string.
            if (isdigit(ch) || (ch == '.') || !isdigit(*(&ch - 1)) && ch == '-' && isdigit(*(&ch + 1)))
                ans += ch;   // Append the current character of string in our answer

                // If the current character of string is an '(', push it to the stack.
            else if (ch == '(')
                st.push('(');

                // If the current character of string is an ')', append the top character of stack in our answer string
                // and pop that top character from the stack until an '(' is encountered.
            else if (ch == ')') {
                ans += ' ';
                while (st.top() != '(')
                {
                    if (ans[ans.length() - 1] == ' ')
                        ans += st.top();
                    else {
                        ans += ' ';
                        ans += {st.top(), ' '};
                    }
                        // Append the top character of stack in our answer
                    st.pop();
                }
                st.pop();
            }

                //If an operator is scanned
            else {
                ans += ' ';
                while (!st.empty() && FindOperator(ch).Precedence <= FindOperator(st.top()).Precedence) {
                    ans += {st.top(), ' '};
                    st.pop();
                }
                st.push(ch);             // Push the current character of string in stack
            }
        }

        // Pop all the remaining elements from the stack
        while (!st.empty()) {
            ans += ' ';
            ans += {st.top(), ' '};
            st.pop();
        }

        return ans;
    }
    /*
    std::string CreateRPN(std::string Exp) {
        int Depth = 0;
        std::string Result;
        std::vector<TOperator> opList;
        std::stack<std::string> numStack;
        std::string num;

        Exp.erase(std::remove(Exp.begin(), Exp.end(), ' '), Exp.end());
        Exp = RemoveSqrt(Exp); // SQRT()
        Exp = RemoveSqr(Exp);
        Exp = std::regex_replace(Exp, std::regex("--"), "+");

        if (IsEncapsulated(Exp)) {
            Exp = Exp.substr(1, Exp.length() - 2);
        }

        for (char &C : Exp) {
            if (isdigit(C) || (C == '.') || !isdigit(*(&C - 1)) && C == '-' && isdigit(*(&C + 1))) {
                num += C;
            } else if (scOperators.find(C) != std::string::npos) {
                if (!num.empty()) {
                    Result += num + " ";
                    num.clear();
                }

                TOperator currOperator = FindOperator(C);
                if (currOperator.iOperator == ')') {
                    Depth--;
                    Result += {opList[0].iOperator, ' '};

                    opList.erase(opList.begin());
//                    opList.erase(opList.begin());



                    opList.erase(std::remove_if(opList.begin(), opList.end(), [](const TOperator &op) {
                        return op.iOperator == '(' || op.iOperator == ')';
                    }), opList.end());

                    Result += {opList[0].iOperator, ' '};

                    if (!opList.empty())
                        opList.erase(opList.begin());
//
//                    auto res = std::find(opList.begin(), opList.end(), '(');
//                    if (res != opList.end())
//                    opList.erase(opList.begin());
//                    opList.erase(opList.begin() + opList.size() - 1);
                } else if (currOperator.iOperator == '(') {
                    Depth++;
                    opList.insert(opList.begin(), currOperator);
                } else if (currOperator.iOperator == '^') {
                    opList.insert(opList.begin(), currOperator);
                } else if (!opList.empty()) {
                    if (opList[0].Precedence >= currOperator.Precedence) {
                        Result += {opList[0].iOperator, ' '};
                        opList.erase(opList.begin());
                        opList.insert(opList.begin(), currOperator);
                    } else {
                        opList.insert(opList.begin(), currOperator);
                    }
                } else {
                    opList.push_back(currOperator);
                }
            }
        }

        if (!num.empty()) {
            Result += num + " ";
        }

        for (auto op : opList) {
            Result += {op.iOperator, ' '};
        }

        return Result;
    }
    */
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
    char DecimalSeparator;
    
    int MaxDecimals;
    
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
