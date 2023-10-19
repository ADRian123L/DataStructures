#ifndef VECTOT_H
#define VECTOT_H

#include <iostream>

template <typename T>
class vector {
public:
    vector();
    ~vector();

    // Queries:
    size_t size() const;
    bool   empty() const;
    size_t max_size() const;
    size_t capacity() const;
    // Modifiers:
    void clear();

private:
    T *ptr_array = nullptr;
};

#endif
