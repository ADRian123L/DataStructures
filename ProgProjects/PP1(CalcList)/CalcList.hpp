#ifndef CalcList_H
#define CalcList_H
#include "CalcListInterface.hpp"
#include <string>

class CalcList : public CalcListInterface {
private:
    // Class for the linked list:
    class Node;

    // Declaring and initializing the main variables:
    double totalSum = 0.0;
    Node  *head     = nullptr;
    size_t numNode  = 0;

public:
    double total() const override;
    void   newOperation(const FUNCTIONS func, const double operand) override;
    void   removeLastOperation() override;
    std::string toString(unsigned short precision) const override;
    /* Deallocates the memory from the heap.*/
    ~CalcList();
};

#endif /* CalcList_H */
