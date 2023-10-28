#include "Heap.hpp"
#include <iostream>

int main() {
    heap<int, compare> h;
    for (int i = 0, val; i < 50000; i++) {
        val = i & 7737;
        h.insert(val);
    }

    for (int i = 0; i < 500; ++i) {
        std::cout << h.getMin() << std::endl;
        h.pop();
    }
    return EXIT_SUCCESS;
}
