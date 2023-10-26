#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <stdexcept>

template <typename T>
class stack {
private:
    struct Linked_Node {
        T            val;
        Linked_Node *next;
        Linked_Node() : val(T()), next(nullptr) {}
        Linked_Node(T _val, Linked_Node *_next) : val(_val), next(_next) {}
    };
    Linked_Node *ptr_to_node;
    std::size_t  counter;

public:
    stack() : ptr_to_node(nullptr), counter(0){};
    ~stack();
    void        push(T val);
    void        pop();
    T          &get() const;
    bool        isEmpty() const;
    std::size_t size() const;
};

template <typename T>
stack<T>::~stack() {
    Linked_Node *node_to_delete = nullptr;
    while (ptr_to_node != nullptr) {
        node_to_delete = ptr_to_node;
        ptr_to_node    = ptr_to_node->next;
        delete node_to_delete;
    }
}

template <typename T>
void stack<T>::push(T val) {
    Linked_Node *tmp_ptr = new Linked_Node(val, ptr_to_node);
    ptr_to_node          = tmp_ptr;
    counter++;
}

template <typename T>
void stack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("The linked list is empty");
    }
    Linked_Node *tmp_ptr_to_delete = ptr_to_node;
    ptr_to_node                    = ptr_to_node->next;
    delete tmp_ptr_to_delete;
    counter--;
}

template <typename T>
T &stack<T>::get() const {
    if (isEmpty()) {
        throw std::out_of_range("The linked list is empty");
    }
    return ptr_to_node->val;
}
template <typename T>
bool stack<T>::isEmpty() const {
    return (ptr_to_node == nullptr);
}

template <typename T>
std::size_t stack<T>::size() const {
    return counter;
}

#endif /* STACK_H */
