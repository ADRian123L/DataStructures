#include "CalcList.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

/* The class implements a single linked list.*/
class CalcList::Node {
public:
    double    rightOperand;
    double    leftOperand;
    FUNCTIONS funct;
    Node     *next;
    /* The constructor assigns all the values to their corresponding variable.
     */
    Node(double Leftval, double Rightval, FUNCTIONS func, Node *ptr)
        : rightOperand(Rightval), leftOperand(Leftval), funct(func), next(ptr) {
    }
    /* The method returns a string with the corresponding operator. */
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
        default: {
            throw std::invalid_argument("The operator is not valid");
        }
        };
    }
};

/* The destructor delete all of the allocated memory from the heap.*/
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
    /* The switch function conducts the proper operation on "totalSum."*/
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
        /* Checks if the operand is zero. If it is zero it throws an
         * exception.*/
        if (operand == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        else {
            this->totalSum /= operand;
            break;
        }
    }
    default: {
        throw std::invalid_argument("The operator passed is not valid");
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
    else {
        throw std::out_of_range("The linked list is empty");
    }
}

std::string CalcList::toString(unsigned short precision) const {
    /* The method uses a operations on a string as it were a cout
     * function.*/
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
