
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"

class HuffmanTree : public HuffmanNode {
public:
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode,
                           const std::string serializedTree);

private:
};
#endif /* HUFFMANTREE_H */
