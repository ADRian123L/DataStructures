#ifndef LIST_H
#define LIST_H

#include <exception>
#include <string>

template <typename T>
class DoubleList {
private:
    class DoubleNode {
    public:
        T           val;
        DoubleNode *next;
        DoubleNode *prev;
        DoubleNode(const T    &val,
                   DoubleNode *next_ptr = nullptr,
                   DoubleNode *prev_ptr = nullptr)
            : val(val), next(next_ptr), prev(prev_ptr) {}
    };

    class Iterator {
    public:
        // TODO: Implement Iterator functionality.
    };

    std::size_t number_of_nodes;
    DoubleNode *sentinel;

public:
    DoubleList() : number_of_nodes(0) {
        sentinel       = new DoubleNode(T()); // Initialized with default value.
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
    }

    ~DoubleList() {
        DoubleNode *current = sentinel->next;
        while (current != sentinel) {
            DoubleNode *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        delete sentinel;
    }

    bool        isEmpty() const { return number_of_nodes == 0; }
    std::size_t size() const { return number_of_nodes; }
    const T    &getNode(std::size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range 1");
        }
        DoubleNode *ptr = sentinel->next;
        for (std::size_t i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
        return ptr->val;
    }

    // TODO: Implement the begin() and end() iterator methods.

    void pushBack(const T &value) {
        DoubleNode *new_node = new DoubleNode(value, sentinel, sentinel->prev);
        sentinel->prev->next = new_node;
        sentinel->prev       = new_node;
        number_of_nodes++;
    }

    void pushFront(const T &value) {
        DoubleNode *new_node = new DoubleNode(value, sentinel->next, sentinel);
        sentinel->next->prev = new_node;
        sentinel->next       = new_node;
        number_of_nodes++;
    }

    void popBack() {
        if (isEmpty()) throw std::runtime_error("The list is empty 1");
        DoubleNode *toDelete = sentinel->prev;
        sentinel->prev       = toDelete->prev;
        toDelete->prev->next = sentinel;
        delete toDelete;
        number_of_nodes--;
    }

    void popFront() {
        if (isEmpty()) throw std::runtime_error("The list is empty 2");
        DoubleNode *toDelete = sentinel->next;
        sentinel->next       = toDelete->next;
        toDelete->next->prev = sentinel;
        delete toDelete;
        number_of_nodes--;
    }

    void insert(std::size_t index, const T &value) {
        if (index > size()) {
            throw std::out_of_range("The index is out of range 2");
        }
        if (index == 0) {
            pushFront(value);
        }
        else if (index == size()) {
            pushBack(value);
        }
        else {
            DoubleNode *ptr = sentinel->next;
            for (std::size_t i = 0; i < index; ++i) {
                ptr = ptr->next;
            }
            DoubleNode *new_node = new DoubleNode(value, ptr, ptr->prev);
            ptr->prev->next      = new_node;
            ptr->prev            = new_node;
            number_of_nodes++;
        }
    }

    void setVal(std::size_t index, T value) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range 3");
        }
        DoubleNode *ptr = sentinel->next;
        for (std::size_t i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
        ptr->val = value;
    }

    // TODO: Implement the methods using the Iterator.
};
#endif
