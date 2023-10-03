#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include <stdexcept>
#include <string>

class NotationConverter : public NotationConverterInterface {
public:
    std::string postfixToInfix(std::string inStr) override;
    std::string postfixToPrefix(std::string inStr) override;
    std::string infixToPostfix(std::string inStr) override;
    std::string infixToPrefix(std::string inStr) override;
    std::string prefixToInfix(std::string inStr) override;
    std::string prefixToPostfix(std::string inStr) override;

private:
    template <typename T>
    class Deque {
    private:
        // 'DoubleList' implements the circular doubly linked list:
        class DoubleList {
        private:
            // The node for the circular double linked list:
            class DoubleNode {
            public:
                // Pointers:
                DoubleNode *next;
                DoubleNode *prev;
                // Value
                T val;
                // Constructors:
                DoubleNode(const T    &val,
                           DoubleNode *next_ptr,
                           DoubleNode *prev_ptr)
                    : val(val), next(next_ptr), prev(prev_ptr) {}
                DoubleNode(const T &val) : val(val) {}
                DoubleNode(DoubleNode *next, DoubleNode *prev)
                    : next(next), prev(prev) {}
            };

            class Iterator {
            public:
                friend class DoubleNode;

            private:
            };

            std::size_t number_of_nodes;
            // Sentinel Node:
            DoubleNode *sentinel = nullptr;

        public:
            DoubleList() {
                // Create an object of DoubleNode:
                this->sentinel = new DoubleNode;
                // Point next and prev to the sentinel node:
                this->sentinel->next = this->sentinel;
                this->sentinel->prev = this->sentinel;
                // Set the number of nodes to zero:
                this->number_of_nodes = 0;
            }

            // Deallocates all of the nodes' memory:
            ~DoubleList() {
                // Declare and initialize temp nodes:
                DoubleNode *ptr_current   = this->sentinel->next;
                DoubleNode *ptr_to_delete = nullptr;
                // Delete all of the nodes:
                while (ptr_current != sentinel) {
                    ptr_to_delete = ptr_current;
                    ptr_current   = ptr_current->next;
                    delete ptr_to_delete;
                }
                // Delete the sentinel node:
                delete this->sentinel;
                this->sentinel = nullptr;
            }

            // Queries:
            bool        isEmpty() const { return this->number_of_nodes == 0; }
            std::size_t size() const { return this->number_of_nodes; }
            const T    &getNode(std::size_t index) const {
                DoubleNode *ptr = this->sentinel->next;
                for (std::size_t i = 0; i < index; ++i, ptr = ptr->next)
                    ;
                return ptr->val;
            }

            Iterator begin() const;
            Iterator end() const;

            // Main operations:
            void pushBack(const T &value) {
                // create a new node and point 'next' and 'prev' to the
                // corresponding nodes:
                DoubleNode *new_node =
                    new DoubleNode(value, this->sentinel, this->sentinel->prev);
                this->sentinel->prev = new_node;
                new_node->prev->next = new_node;
                this->number_of_nodes++;
            }
            void pushFront(const T &value) {
                // create a new node and point 'next' and 'prev' to the
                // corresponding nodes:
                DoubleNode *new_node =
                    new DoubleNode(value, this->sentinel->next, this->sentinel);
                this->sentinel->next = new_node;
                new_node->next->prev = new_node;
                this->number_of_nodes++;
            }
            void popBack() {
                // Check if the list is empty:
                if (isEmpty()) {
                    // If empty throw an exception:
                    throw std::runtime_error("The list is empty");
                }
                else {
                    // Delete the node by creating a temp node moving the
                    // pointers:
                    DoubleNode *temp_node = this->sentinel->prev;
                    this->sentinel->prev  = temp_node->prev;
                    temp_node->prev->next = this->sentinel;
                    delete temp_node;
                    this->number_of_nodes--;
                }
            }
            void popFront() {
                // Check if the list is empty:
                if (isEmpty()) {
                    // If empty throw an exception:
                    throw std::runtime_error("The list is empty");
                }
                else {
                    DoubleNode *temp_node = this->sentinel->next;
                    this->sentinel->next  = temp_node->next;
                    temp_node->next->prev = this->sentinel;
                    delete temp_node;
                    this->number_of_nodes--;
                }
            }

            void insert(std::size_t index, const T &value) {
                if (index <= size()) {
                    DoubleNode *ptr = this->sentinel->next;
                    // Search for the node:
                    for (std::size_t i = 0; i < index; ++i, ptr = ptr->next)
                        ;
                    // Create a new node:
                    DoubleNode *new_node =
                        new DoubleNode(value, ptr->next, ptr);
                    // Change where the nodes point to:
                    ptr->next            = new_node;
                    new_node->next->prev = new_node;
                    new_node->prev->next = new_node;
                }
                else {
                    throw std::out_of_range("The index is out of range");
                }
            }
            void setVal(std::size_t index, T value) {
                if (index < size()) {
                    DoubleNode *ptr = this->sentinel->next;
                    // Search for the node:
                    for (std::size_t i = 0; i < index; ++i, ptr = ptr->next)
                        ;
                    ptr->val = value;
                }
                else {
                    throw std::runtime_error(
                        "The list is either empty or the index is out of "
                        "range");
                }
            }
            void insert(Iterator &position, T value) {
                if (!isEmpty()) {
                }
                else {
                    throw std::runtime_error("The list is empty");
                }
            }
            void setVal(Iterator &position, T value);
        };
        DoubleList *double_list = nullptr;

    public:
        Deque() { this->double_list = new DoubleList; }
        ~Deque() { delete this->double_list; }
        // Queries:
        std::size_t size(void) const { return this->double_list->size(); }
        bool        isEmpty(void) const { return this->double_list->isEmpty(); }
        const T    &front() const { return this->double_list->getNode(0); }
        const T &back() const { return this->double_list->getNode(size() - 1); }

        // Operations:
        void insertFront(T &value) { this->double_list->pushFront(value); }
        void insertBack(T &value) { this->double_list->pushBack(value); }
        void eraseFront() { this->double_list->popFront(); }
        void eraseBack() { this->double_list->popBack(); }
    };
};

#endif
