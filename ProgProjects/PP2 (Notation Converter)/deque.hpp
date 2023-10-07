#ifndef DEQUE_H
#define DEQUE_H

#include "list.hpp"
#include <iostream>

template <typename T>
class Deque {
private:
    DoubleList<T> *double_list; // Sentinel Node

public:
    Deque() : double_list(new DoubleList<T>()) {}
    ~Deque() { delete double_list; }

    std::size_t size() const { return double_list->size(); }
    bool        isEmpty() const { return double_list->isEmpty(); }
    const T    &front() const { return double_list->getNode(0); }
    const T    &back() const { return double_list->getNode(size() - 1); }
    void        display() const {
        for (std::size_t i = 0; i < size(); ++i) {
            std::cout << double_list->getNode(i) << std::endl;
        }
    }
    void insertFront(const T &value) { double_list->pushFront(value); }
    void insertBack(const T &value) { double_list->pushBack(value); }
    void eraseFront() { double_list->popFront(); }
    void eraseBack() { double_list->popBack(); }
};
#endif
