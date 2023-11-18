#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>

template <typename T>
class doublelist {
public:
    doublelist();
    ~doublelist();
    void        push_back(T);
    void        push_front(T);
    void        remove_back();
    void        remove_front();
    T          &getVal(std::size_t) const;
    std::size_t size() const;

private:
    struct doubleNode {
        T           val;
        doubleNode *next;
        doubleNode *prev;
        doubleNode(T _val, doubleNode *_next, doubleNode *_prev)
            : val(_val), next(_next), prev(_prev) {}
        doubleNode(doubleNode *_next, doubleNode *_prev)
            : val(T()), next(_next), prev(_prev) {}
    };
    std::size_t _size;
    doubleNode *sentinel;

    // Helper functions:
    doubleNode *find(std::size_t index) const {
        if (size() < 1) {
            throw std::out_of_range("The list is empty");
        }
        doubleNode *ptr = sentinel->next;
        while (ptr != sentinel && index > 0) {
            ptr = ptr->next;
            --index;
        }
        return ptr;
    }
};

template <typename T>
doublelist<T>::doublelist() : _size(0) {
    sentinel       = new doubleNode(sentinel, sentinel); // Empty node
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
}

template <typename T>
doublelist<T>::~doublelist() {
    while (sentinel->next != sentinel) {
        doubleNode *node_to_delete = sentinel->next;
        sentinel->next             = node_to_delete->next;
        delete node_to_delete;
    }
    delete sentinel;
}

template <typename T>
void doublelist<T>::push_front(T val) {
    doubleNode *new_node = new doubleNode(val, sentinel->next, sentinel);
    sentinel->next->prev = new_node;
    sentinel->next       = new_node;
    _size++;
}

template <typename T>
void doublelist<T>::push_back(T val) {
    doubleNode *new_node = new doubleNode(val, sentinel, sentinel->prev);
    sentinel->prev->next = new_node;
    sentinel->prev       = new_node;
    _size++;
}

template <typename T>
void doublelist<T>::remove_back() {
    if (size() < 1) {
        throw std::out_of_range("The list if empty");
    }
    doubleNode *node_to_delete = sentinel->prev;
    sentinel->prev             = sentinel->prev->prev;
    sentinel->prev->next       = sentinel;
    delete node_to_delete;
}

template <typename T>
void doublelist<T>::remove_front() {
    if (size() < 1) {
        throw std::out_of_range("The list is empty");
    }
    doubleNode *node_to_delete = sentinel->next;
    sentinel->next             = node_to_delete->next;
    sentinel->next->prev       = sentinel;
    delete node_to_delete;
}

template <typename T>
std::size_t doublelist<T>::size() const {
    return _size;
}

template <typename T>
T &doublelist<T>::getVal(std::size_t index) const {
    return (find(index))->val;
}

#endif // DOUBLELIST_H
