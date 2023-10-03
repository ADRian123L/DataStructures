#include "NotationConverter.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>

bool isLetter(char letter) {
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}

bool isOperator(char oper) {
    return oper == '+' || oper == '-' || oper == '*' || oper == '/';
}

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

std::string NotationConverter::postfixToInfix(std::string inStr) {
    Deque<std::string> stack;
    for (char &ch : inStr) {
        if (isLetter(ch)) {
            stack.insertBack(std::string(1, ch));
        }
        else if (isOperator(ch)) {
            std::string op2 = stack.back();
            stack.eraseBack();
            std::string op1 = stack.back();
            stack.eraseBack();
            stack.insertBack("(" + op1 + " " + ch + " " + op2 + ")");
        }
    }
    return stack.back();
}

std::string NotationConverter::infixToPostfix(std::string inStr) {
    Deque<char> operators;
    std::string postfix;

    for (char &ch : inStr) {
        if (isLetter(ch)) {
            postfix += ch;
        }
        else if (isOperator(ch)) {
            while (!operators.isEmpty() &&
                   precedence_out(ch) <= precedence_in(operators.back())) {
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
            operators.eraseBack();
        }
    }

    while (!operators.isEmpty()) {
        postfix += operators.back();
        operators.eraseBack();
    }

    return postfix;
}

std::string NotationConverter::postfixToPrefix(std::string inStr) {
    Deque<std::string> stack;
    for (char &ch : inStr) {
        if (isLetter(ch)) {
            stack.insertBack(std::string(1, ch));
        }
        else if (isOperator(ch)) {
            std::string op2 = stack.back();
            stack.eraseBack();
            std::string op1 = stack.back();
            stack.eraseBack();
            stack.insertBack(std::string(1, ch) + " " + op1 + " " + op2);
        }
    }
    return stack.back();
}

std::string NotationConverter::infixToPrefix(std::string inStr) {
    std::reverse(inStr.begin(), inStr.end());

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

std::string NotationConverter::prefixToInfix(std::string inStr) {
    Deque<std::string> stack;
    for (auto it = inStr.rbegin(); it != inStr.rend(); ++it) {
        char ch = *it;
        if (isLetter(ch)) {
            stack.insertBack(std::string(1, ch));
        }
        else if (isOperator(ch)) {
            std::string op1 = stack.back();
            stack.eraseBack();
            std::string op2 = stack.back();
            stack.eraseBack();
            stack.insertBack("(" + op1 + " " + ch + " " + op2 + ")");
        }
    }
    return stack.back();
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    Deque<std::string> stack;
    for (auto it = inStr.rbegin(); it != inStr.rend(); ++it) {
        char ch = *it;
        if (isLetter(ch)) {
            stack.insertBack(std::string(1, ch));
        }
        else if (isOperator(ch)) {
            std::string op1 = stack.back();
            stack.eraseBack();
            std::string op2 = stack.back();
            stack.eraseBack();
            stack.insertBack(op1 + " " + op2 + " " + ch);
        }
    }
    return stack.back();
}
