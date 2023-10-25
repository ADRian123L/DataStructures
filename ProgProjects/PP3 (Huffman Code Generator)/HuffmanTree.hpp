#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"
#include <string>

class HuffmanTree : public HuffmanTreeBase {
public:
    // Constructor // Destructor
    HuffmanTree() : ptr_to_tree(nullptr) {}
    ~HuffmanTree();

    std::string compress(const std::string inputStr) override;
    std::string serializeTree() const override;
    std::string decompress(const std::string inputCode,
                           const std::string serializedTree) override;

    // Helper functions:
    std::string HuffTable(HuffmanNode const &node) const;

private:
    HuffmanNode *ptr_to_tree; // It points to the tree
};
#endif /* HUFFMANTREE_H */
