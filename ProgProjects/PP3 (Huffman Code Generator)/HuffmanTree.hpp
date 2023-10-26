#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"
#include "TestStrings.hpp"
#include "stack.hpp"
#include <string>

#define ONE '1'
#define ZERO '0'
#define LEAF 'L'
#define BRANCH 'B'

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
    void        HuffTable(HuffmanNode *node, std::string &answer) const;
    void        HuffS(HuffmanNode *node, std::string *h_map) const;
    std::string HuffConvert(std::string &code, std::string *map) const;

private:
    HuffmanNode *ptr_to_tree; // It points to the tree
};
#endif /* HUFFMANTREE_H */
