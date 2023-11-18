#ifndef QUEUE_H
#define QUEUE_H

#include "cdoublelist.hpp"

template <typename T>
class queue {
public:
    void        enqueue(T);
    void        dequeue();
    T          &getdeq() const;
    std::size_t size() const;
    bool        isEmpty() const;

private:
    doublelist<T> list;
};

template <typename T>
bool queue<T>::isEmpty() const {
    return (size() == 0);
}

template <typename T>
void queue<T>::enqueue(T val) {
    list.push_back(val);
}

template <typename T>
void queue<T>::dequeue() {
    list.remove_front();
}

template <typename T>
T &queue<T>::getdeq() const {
    return list.getVal(0);
}

template <typename T>
std::size_t queue<T>::size() const {
    return list.size();
}

#endif // QUEUE_H
