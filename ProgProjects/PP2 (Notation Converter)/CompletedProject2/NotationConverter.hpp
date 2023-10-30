
/*****************************************************************************
 *                        NotationConverter                               *
 *****************************************************************************
 * Author    : Adrian Lozada *
 * Course    : Data Structures *
 ****************************************************************************/

#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include "deque.hpp"
#include <stdexcept>
#include <string>

#define WHITE_SPACE ' ' // Macros for the functions:
#define OPENING_PAREN '('
#define CLOSING_PAREN ')'

class NotationConverter : public NotationConverterInterface {
public:
    // Operations:
    std::string postfixToInfix(std::string inStr) override;
    std::string postfixToPrefix(std::string inStr) override;
    std::string infixToPostfix(std::string inStr) override;
    std::string infixToPrefix(std::string inStr) override;
    std::string prefixToInfix(std::string inStr) override;
    std::string prefixToPostfix(std::string inStr) override;

    // Helper functions:
    bool isLetter(char letter) const;
    bool isOperator(char oper) const;
    int  precedence_out(char oper) const;
    int  precedence_in(char oper) const;
    void reverse_infix(std::string::iterator begin,
                       std::string::iterator end) const;
};
#endif
