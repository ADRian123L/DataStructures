#include "HuffmanTree.hpp"

HuffmanTree::~HuffmanTree() {}

std::string HuffmanTree::serializeTree() const {
    std::string answer;
    return answer;
}

std::string HuffmanTree::decompress(const std::string inputCode,
                                    const std::string serializedTree) {
    std::string answer;
    return answer;
}

std::string HuffmanTree::compress(const std::string inputStr) {
    std::string compressed_hoff_code;
    int         char_frequencies[128]{0}; // Hash map
    // Count the frequency of each letter:
    for (auto &ptr : inputStr) {
        ++char_frequencies[static_cast<int>(ptr)];
    }
    return compressed_hoff_code;
}

int main() {
    HuffmanTree t;
    t.compress("Hello There Are you?AA");
    return EXIT_SUCCESS;
}
