#include "NotationConverter.hpp"
#include <sstream>
#include <stdexcept>
#include <string>

bool NotationConverter::isLetter(char letter) const {
    // Returns true if the argument is one of these chars:
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}

bool NotationConverter::isOperator(char oper) const {
    // Returns true if the argument is one of these operators:
    return oper == '+' || oper == '-' || oper == '*' || oper == '/' ||
           oper == '(' || oper == ')';
}

int NotationConverter::precedence_out(char oper) const {
    // Returns precedence of the operator when out of the stack:
    switch (oper) {
    case ')':
        return 0;
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

int NotationConverter::precedence_in(char oper) const {
    // Returns precedence of the operator when out of the stack:
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

void NotationConverter::reverse_infix(std::string::iterator begin,
                                      std::string::iterator end) const {
    // Reverses an infix equation:
    --end;
    while (begin < end) {
        if (*begin == OPENING_PAREN) // Switch the parenthesis:
            *begin = CLOSING_PAREN;
        else if (*begin == CLOSING_PAREN)
            *begin = OPENING_PAREN;
        if (*end == OPENING_PAREN)
            *end = CLOSING_PAREN;
        else if (*end == CLOSING_PAREN)
            *end = OPENING_PAREN;
        std::swap(*begin, *end);
        ++begin;
        --end;
    } // Check if the middle char is a parenthesis:
    if (*begin == CLOSING_PAREN)
        *begin = OPENING_PAREN;
    else if (*begin == OPENING_PAREN)
        *begin = CLOSING_PAREN;
}

std::string NotationConverter::postfixToInfix(std::string inStr) {
    Deque<std::string> stack;
    // Conversion:
    std::string::iterator ptr = inStr.begin();
    // Iterate over the string:
    while (ptr != inStr.end()) {
        if (isLetter(*ptr)) { // Pushes all letters into the stack
            stack.insertFront(std::string(1, *ptr));
            ++ptr;
        }
        else if (isOperator(*ptr)) {
            if (stack.size() < 2) { // If the stack is empty throw an error
                throw std::runtime_error("Invalid input 1");
            }
            else {
                // Pop from stack and push the equation into the string
                std::stringstream term; // Use a string stream to insert the
                                        // letters and operands
                std::string front = stack.front();
                stack.eraseFront();
                std::string back = stack.front();
                stack.eraseFront();
                term << OPENING_PAREN;
                term << back;
                term << WHITE_SPACE;
                term << *ptr;
                term << WHITE_SPACE;
                term << front;
                term << CLOSING_PAREN;
                stack.insertFront(term.str()); // Push it back to the stack
                ++ptr;
            }
        }
        else if (*ptr == WHITE_SPACE) {
            ++ptr; // If white space continue
            continue;
        }
        else {
            throw std::runtime_error("Invalid input 2");
        }
    }
    return stack.front(); // Return the last string in the stack
}

std::string NotationConverter::infixToPostfix(std::string inStr) {
    Deque<char> stack;
    std::string postfix;
    // Conversion:
    std::string::iterator ptr = inStr.begin();
    while (ptr != inStr.end()) {
        if (isLetter(*ptr)) {
            postfix.push_back(*ptr); // Push all letters into the string
            postfix.push_back(WHITE_SPACE);
            ++ptr;
        }
        else if (isOperator(*ptr)) {
            if (stack.isEmpty()) {
                stack.insertFront(*ptr); // Push the operator into the stack
                                         // if the stack is empty
                ++ptr;
            }
            else if (precedence_in(stack.front()) <= precedence_out(*ptr)) {
                if (*ptr == CLOSING_PAREN && stack.front() == OPENING_PAREN) {
                    stack.eraseFront();
                    ++ptr; // Check for parenthesis
                    continue;
                }
                else if (*ptr == CLOSING_PAREN) {
                    throw std::runtime_error("Invalid input 1");
                }
                stack.insertFront(
                    *ptr); // If the precedence of the operand being checked
                           // is higher than the one at the top of the
                           // stack, the operand is pushed into the stack.
                ++ptr;
            }
            else {
                postfix.push_back(
                    stack.front()); // Push the operator to the string and
                                    // pop it from the stack
                postfix.push_back(WHITE_SPACE);
                stack.eraseFront();
            }
        }
        else if (*ptr == WHITE_SPACE) {
            ++ptr; // Skip white spaces
            continue;
        }
        else {
            throw std::runtime_error("Invalid input 2");
        }
    }
    while (!stack.isEmpty()) {
        if (precedence_in(stack.front()) ==
            0) { // Do not push the parenthesis into the string
            stack.eraseFront();
            continue;
        }
        postfix.push_back(
            stack.front()); // Push all remaining operators to the string.
        stack.eraseFront();
        postfix.push_back(WHITE_SPACE);
    }
    return postfix;
}

std::string NotationConverter::postfixToPrefix(std::string inStr) {
    std::string answer =
        postfixToInfix(inStr);      // Convert the equation into infix
    answer = infixToPrefix(answer); // Convert the equation into prefix
    return answer;
}

std::string NotationConverter::infixToPrefix(std::string inStr) {
    reverse_infix(inStr.begin(), inStr.end());     // Reverse the string
    std::string postfix = infixToPostfix(inStr);   // Convert to postfix
    reverse_infix(postfix.begin(), postfix.end()); // Reverse to get prefix
    return postfix;
}

std::string NotationConverter::prefixToInfix(std::string inStr) {
    Deque<std::string> stack;
    reverse_infix(inStr.begin(), inStr.end()); // Reverse the string
    // Conversion:
    std::string::iterator ptr = inStr.begin();
    while (ptr != inStr.end()) {
        if (isLetter(*ptr)) { // Push all letters into the stack
            stack.insertFront(std::string(1, *ptr));
            ++ptr;
        }
        else if (isOperator(*ptr)) {
            // Combine the letters with the operator:
            std::stringstream term;
            term << OPENING_PAREN;
            term << stack.front();
            stack.eraseFront();
            term << WHITE_SPACE;
            term << std::string(1, *ptr);
            term << WHITE_SPACE;
            term << stack.front();
            stack.eraseFront();
            term << CLOSING_PAREN;
            stack.insertFront(term.str()); // Push into the stack
            ++ptr;
        }
        else if (*ptr == WHITE_SPACE) {
            ++ptr; // Skip white space
            continue;
        }
        else {
            throw std::runtime_error("Invalid input");
        }
    }
    return stack.front(); // Return the last string from the stack
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    std::string answer = prefixToInfix(inStr);   // Convert the into infix
    answer             = infixToPostfix(answer); // Convert the it into postfix
    return answer;
}
