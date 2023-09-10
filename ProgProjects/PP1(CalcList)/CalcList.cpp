#include "CalcListInterface.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

class CalcList : public CalcListInterface {
private:
    // Class for the linked list:
    class Node {
    public:
        double    rightOperand;
        double    leftOperand;
        FUNCTIONS funct;
        Node     *next;
        Node(double Leftval, double Rightval, FUNCTIONS func, Node *ptr)
            : rightOperand(Rightval), leftOperand(Leftval), funct(func),
              next(ptr) {}

        std::string oper() {
            switch (funct) {
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
    };

    // Declaring and initializing the main variables:
    double totalSum = 0.0;
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
        Node *node = new Node(this->totalSum, operand, func, head);
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
        this->totalSum = head->leftOperand;
        Node *ptr      = head;
        head           = head->next;
        delete ptr;
        --(this->numNode);
    }
}

std::string CalcList::toString(unsigned short precision) const {
    std::ostringstream ans;
    Node              *ptr = head;
    ans << std::fixed << std::setprecision(precision);
    double prevAns = total();
    for (size_t i = 0; i < numNode; ++i, ptr = ptr->next) {
        ans << (numNode - i) << ": ";
        ans << ptr->leftOperand;
        ans << ptr->oper();
        ans << ptr->rightOperand;
        ans << "=" << prevAns;
        ans << std::endl;
        prevAns = ptr->leftOperand;
    }
    return ans.str();
}

// int main(void) {
//     CalcList calc;                        // Total == 0
//     calc.newOperation(ADDITION, 10);      // Total == 10
//     calc.newOperation(MULTIPLICATION, 5); // Total == 50
//     calc.newOperation(SUBTRACTION, 15);   // Total == 35
//     calc.newOperation(DIVISION, 7);       // Total == 5
//     calc.removeLastOperation();           // Total == 35
//     calc.newOperation(SUBTRACTION, 30);   // Total == 5
//     calc.newOperation(ADDITION, 5);       // Total == 10
//     calc.removeLastOperation();           // Total == 5
//     // Should Return:
//     // 4: 35.00-30.00=5.00
//     // 3: 50.00-15.00=35.00
//     // 2: 10.00*5.00=50.00
//     // 1: 0.00+10.00=10.00
//     std::cout << calc.toString(2);
//     calc.removeLastOperation(); // Total == 35
//     // Should Return:
//     // 3: 50-15=35
//     // 2: 10*5=50
//     // 1: 0+10=10
//     std::cout << calc.toString(0);
//     return EXIT_SUCCESS;
// }
