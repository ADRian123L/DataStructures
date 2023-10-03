#include "NotationConverter.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>

// Check if a given character is a letter.
bool isLetter(char letter) {
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}

// Check if a given character is an operator.
bool isOperator(char oper) {
    return oper == '+' || oper == '-' || oper == '*' || oper == '/';
}

// Get the precedence level of an operator outside the stack.
int precedence_out(char oper) {
    switch (oper) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 3;
    case '(':
        return 5;
    default:
        return -1;
    }
}

// Get the precedence level of an operator inside the stack.
int precedence_in(char oper) {
    switch (oper) {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 4;
    case '(':
        return 0;
    default:
        return -1;
    }
}

// Convert Postfix notation to Infix notation.
std::string NotationConverter::postfixToInfix(std::string inStr) {
    Deque<std::string> stack;
    for (char &ch : inStr) {
        if (isLetter(ch)) {
            std::string temp(1, ch);
            stack.insertBack(temp);
        }
        else if (isOperator(ch)) {
            std::string op2 = stack.back();
            stack.eraseBack();
            std::string op1 = stack.back();
            stack.eraseBack();
            std::string combined = "(" + op1 + ch + op2 + ")";
            stack.insertBack(combined);
        }
    }
    return stack.back();
}

// Convert Infix notation to Postfix notation.
std::string NotationConverter::infixToPostfix(std::string inStr) {
    // Declare the deque for the operations and the resulting postfix string:
    Deque<char> operators;
    std::string postfix;
    // Conversion:
    for (char &ch : inStr) {
        if (isLetter(ch)) {
            postfix += ch;
        }
        else if (isOperator(ch)) {
            while (!operators.isEmpty() &&
                   precedence_out(operators.back()) >= precedence_in(ch)) {
                postfix += operators.back();
                operators.eraseBack();
            }
            operators.insertBack(ch);
        }
        else if (ch == '(') {
            operators.insertBack(ch);
        }
        else if (ch == ')') {
            while (operators.back() != '(') {
                postfix += operators.back();
                operators.eraseBack();
            }
            operators.eraseBack(); // Remove the '('
        }
    }
    while (!operators.isEmpty()) {
        postfix += operators.back();
        operators.eraseBack();
    }
    return postfix;
}

// Convert Postfix notation to Prefix notation.
std::string NotationConverter::postfixToPrefix(std::string inStr) {
    Deque<std::string> stack;
    for (char &ch : inStr) {
        if (isLetter(ch)) {
            std::string temp(1, ch);
            stack.insertBack(temp);
        }
        else if (isOperator(ch)) {
            std::string op2 = stack.back();
            stack.eraseBack();
            std::string op1 = stack.back();
            stack.eraseBack();
            std::string combined = ch + op1 + op2;
            stack.insertBack(combined);
        }
    }
    return stack.back();
}

// Convert Infix notation to Prefix notation.
std::string NotationConverter::infixToPrefix(std::string inStr) {
    std::reverse(
        inStr.begin(),
        inStr.end()); // reverse the string to simulate prefix operations

    for (char &ch : inStr) {
        if (ch == '(')
            ch = ')';
        else if (ch == ')')
            ch = '(';
    }

    std::string postfix = infixToPostfix(inStr);

    std::reverse(postfix.begin(), postfix.end());

    return postfixToPrefix(postfix);
}

// Convert Prefix notation to Infix notation.
std::string NotationConverter::prefixToInfix(std::string inStr) {
    // Similar to postfixToInfix, but you process operators before operands.
    Deque<std::string> stack;
    for (auto it = inStr.rbegin(); it != inStr.rend(); ++it) {
        char ch = *it;
        if (isLetter(ch)) {
            std::string temp(1, ch);
            stack.insertBack(temp);
        }
        else if (isOperator(ch)) {
            std::string op1 = stack.back();
            stack.eraseBack();
            std::string op2 = stack.back();
            stack.eraseBack();
            std::string combined = "(" + op1 + ch + op2 + ")";
            stack.insertBack(combined);
        }
    }
    return stack.back();
}

// Convert Prefix notation to Postfix notation.
std::string NotationConverter::prefixToPostfix(std::string inStr) {
    // Similar to postfixToPrefix, but you process operators before operands.
    Deque<std::string> stack;
    for (auto it = inStr.rbegin(); it != inStr.rend(); ++it) {
        char ch = *it;
        if (isLetter(ch)) {
            std::string temp(1, ch);
            stack.insertBack(temp);
        }
        else if (isOperator(ch)) {
            std::string op1 = stack.back();
            stack.eraseBack();
            std::string op2 = stack.back();
            stack.eraseBack();
            std::string combined = op1 + op2 + ch;
            stack.insertBack(combined);
        }
    }
    return stack.back();
}
