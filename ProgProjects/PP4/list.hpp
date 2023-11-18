#ifndef LIST_H
#define LIST_H

#include <stdexcept>
#include <string>

template <typename T>
struct DoubleNode { // Node for double linked list
    T           val;
    DoubleNode *next;
    DoubleNode *prev;
    DoubleNode(const T    &val, // Constructor with default settings
               DoubleNode *next_ptr = nullptr,
               DoubleNode *prev_ptr = nullptr)
        : val(val), next(next_ptr), prev(prev_ptr) {}
};

template <typename T>
class DoubleList {
private:
    std::size_t    number_of_nodes; // Track the number of nodes
    DoubleNode<T> *sentinel;        // Pointer to sentinel node

public:
    DoubleList() : number_of_nodes(0) {
        sentinel = new DoubleNode<T>(T()); // Initialized with default value.
        sentinel->next = sentinel;         // Point the node to itself
        sentinel->prev = sentinel;
    }

    ~DoubleList() {
        DoubleNode<T> *current = sentinel->next;
        while (current != sentinel) { // Delete all nodes after the sentinel
            DoubleNode<T> *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        delete sentinel;
    }

    class Iterator {
    private:
        DoubleNode<T> *currentNode;

    public:
        Iterator(DoubleNode<T> *startNode) : currentNode(startNode) {}

        T   &operator*() { return currentNode->val; }
        bool operator!=(const Iterator &other) const {
            return currentNode != other.currentNode;
        }
        bool operator==(const Iterator &other) const {
            return currentNode == other;
        }
        Iterator &operator++() {
            currentNode = currentNode->next;
            return *this;
        }
    };
    Iterator begin() { return Iterator(sentinel->next); }
    Iterator end() { return Iterator(sentinel); }

    bool isEmpty() const { return number_of_nodes == 0; } // Check if empty
    std::size_t size() const { return number_of_nodes; }  // Return the size
    const T    &getNode(
           std::size_t index) const { // Return a reference to the value of a node
        if (index >= size()) {
            throw std::out_of_range("Index out of range 1");
        }
        DoubleNode<T> *ptr = sentinel->next;
        for (std::size_t i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
        return ptr->val;
    }

    void pushBack(const T &value) {
        DoubleNode<T> *new_node = new DoubleNode(
            value,
            sentinel,
            sentinel->prev); // Initialize the node and set the values
        sentinel->prev->next = new_node;
        sentinel->prev       = new_node;
        number_of_nodes++; // Increment the number of nodes
    }

    void pushFront(const T &value) {
        DoubleNode<T> *new_node =
            new DoubleNode(value,
                           sentinel->next,
                           sentinel); // Initialize the node and set the values

        sentinel->next->prev = new_node;
        sentinel->next       = new_node;
        number_of_nodes++;
    }

    void popBack() {
        if (isEmpty())
            throw std::runtime_error("The list is empty 1");
        DoubleNode<T> *toDelete =
            sentinel->prev; // Create a pointer which will delete the node
        sentinel->prev       = toDelete->prev; // Move the pointer of the node:
        toDelete->prev->next = sentinel;
        delete toDelete;
        number_of_nodes--; // Decrement the number of nodes
    }

    void popFront() {
        if (isEmpty())
            throw std::runtime_error("The list is empty 2");
        DoubleNode<T> *toDelete =
            sentinel->next; // Create a pointer which will delete the node
        sentinel->next       = toDelete->next; // Move the pointers:
        toDelete->next->prev = sentinel;
        delete toDelete;
        number_of_nodes--;
    }

    void insert(std::size_t index, const T &value) {
        if (index > size()) { // If front or back
            throw std::out_of_range("The index is out of range 2");
        }
        if (index == 0) {
            pushFront(value);
        }
        else if (index == size()) {
            pushBack(value);
        }
        else { // Search for the node:
            DoubleNode<T> *ptr = sentinel->next;
            for (std::size_t i = 0; i < index; ++i) {
                ptr = ptr->next;
            }
            DoubleNode<T> *new_node = new DoubleNode(value, ptr, ptr->prev);
            ptr->prev->next         = new_node;
            ptr->prev               = new_node;
            number_of_nodes++;
        }
    }

    void setVal(std::size_t index, T value) { // Change the value of a node
        if (index >= size()) {
            throw std::out_of_range("Index out of range 3");
        }
        DoubleNode<T> *ptr = sentinel->next;
        for (std::size_t i = 0; i < index; ++i) { // Search for the node:
            ptr = ptr->next;
        }
        ptr->val = value;
    }

    void deleteNode(std::string val) {
        DoubleNode<T> *ptr = sentinel->next;
        while (ptr != sentinel && ptr->val->label_ptr->label != val) {
            ptr = ptr->next;
        }
        if (ptr != sentinel) {
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;

            delete ptr;
        }
    }
};
#endif
