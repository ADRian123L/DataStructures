#ifndef CalcList_H
#define CalcList_H
#include "CalcListInterface.hpp"
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

#endif /* CalcList_H */
