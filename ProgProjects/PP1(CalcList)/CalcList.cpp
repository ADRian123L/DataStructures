#include "CalcListInterface.hpp"
#include <iostream>
#include <string>

std::string oper(FUNCTIONS func);

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
    };

    // Declaring and initializing the main variables:
    double totalSum = 0;
    Node  *head     = nullptr;
    size_t numNode  = 0;

public:
    double total() const override;
    void   newOperation(const FUNCTIONS func, const double operand) override;
    void   removeLastOperation() override;
    std::string toString(unsigned short precision) const override;
    ~CalcList();
};

CalcList::~CalcList() {
    Node *ptr = head;
    while (head != nullptr) {
        head = head->next;
        delete ptr;
        ptr = head;
    }
}

double CalcList::total() const { return totalSum; }

void CalcList::newOperation(const FUNCTIONS func, const double operand) {
    try {
        Node *node = new Node(this->totalSum, operand, head);
        head       = node;
        ++(this->numNode);
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

void CalcList::removeLastOperation() {
    if (head != nullptr) {
        this->totalSum = head->rightOperand;
        Node *ptr      = head;
        head           = head->next;
        delete ptr;
        --(this->numNode);
    }
}

std::string CalcList::toString(unsigned short precision) const {
    std::string ans((20 + precision * 3), '\0');
    Node       *ptr = this->head;
    for (size_t i = numNode; i > 0; --i, ptr = ptr->next) {
        ans += std::to_string(i) + std::string(": ");
        ans += std::string(std::to_string(static_cast<int>(ptr->rightOperand)));
        ans += oper(ptr->funct) + std::string("+");
        ans += std::to_string(3);
    }
    return ans;
}

std::string oper(FUNCTIONS func) {
    switch (func) {
    case ADDITION: {
        return std::string("+");
    }
    case SUBTRACTION: {
        return std::string("-");
    }
    case MULTIPLICATION: {
        return std::string("*");
    }
    case DIVISION: {
        return std::string("/");
    }
    };
}
