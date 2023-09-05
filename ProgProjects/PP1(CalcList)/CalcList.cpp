#include "CalcListInterface.hpp"
#include <iostream>
#include <string>

class CalcList : public CalcListInterface {
private:
    // Class for the linked list:
    class Node {
    public:
        double    rightOperand;
        double    leftOperand;
        FUNCTIONS funct;
        Node     *next;
        Node(double Rightval, double Leftval, Node *ptr)
            : rightOperand(Rightval), leftOperand(Leftval), next(ptr) {}
        Node(double Rightval, double Leftval)
            : rightOperand(Rightval), leftOperand(Leftval) {
            next = nullptr;
        }
    };

    // Declaring and initializing the main variables:
    double totalSum = 0;
    Node  *head     = nullptr;

public:
    double      total() const;
    void        newOperation(const FUNCTIONS func, const double operand);
    void        removeLastOperation();
    std::string toString(unsigned short precision) const;
    ~CalcList();
};

double CalcList::total() const { return totalSum; }

void CalcList::newOperation(const FUNCTIONS func, const double operand) {
    try {
        Node *node = new Node(this->totalSum, operand, head);
        head       = node;
    } catch (const std::bad_alloc &e) {
        std::cout << "Memory allocation failed: " << e.what() << std::endl;
    }

    switch (func) {
    case ADDITION: {
        this->totalSum += operand;
        break;
    }
    case SUBTRACTION: {
        this->totalSum -= operand;
        break;
    }
    case MULTIPLICATION: {
        this->totalSum *= operand;
        break;
    }
    case DIVISION: {
        this->totalSum /= operand;
        break;
    }
    }
}

void CalcList::removeLastOperation() {}

std::string CalcList::toString(unsigned short precision) const {
    std::string ans;
    return ans;
}
