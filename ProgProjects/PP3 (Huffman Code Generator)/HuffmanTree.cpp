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
    size_t      char_frequencies[128]{0}; // Hash map
    // Count the frequency of each letter:
    for (auto &ptr : inputStr) {
        ++char_frequencies[static_cast<int>(ptr)];
    }
    // Create each node and insert them into queue:
    HeapQueue<HuffmanNode *, HuffmanNode::Compare> que;
    HuffmanNode                                   *ptr_to_each_node = nullptr;
    for (std::size_t i = 0; i < 127; i++) {
        if (char_frequencies[i]) {
            ptr_to_each_node = new HuffmanNode(char(i), char_frequencies[i]);
            que.insert(ptr_to_each_node);
        }
    }
    // Build the tree:
    while (que.size() > 1) {
        HuffmanNode *tmp_1 = nullptr, *tmp_2 = nullptr;
        tmp_1 = que.min();
        que.removeMin();
        tmp_2 = que.min();
        que.removeMin();
        ptr_to_each_node =
            new HuffmanNode(char(),
                            tmp_1->getFrequency() + tmp_2->getFrequency(),
                            ptr_to_each_node,
                            tmp_1,
                            tmp_2);
        que.insert(ptr_to_each_node);
    }
    ptr_to_tree = que.min();
    que.removeMin();
    // Create the Huffman code:
    std::cout << HuffTable(*ptr_to_tree);
    return compressed_hoff_code;
}

std::string HuffmanTree::HuffTable(HuffmanNode const &node) const {
    static std::string answer;
    if (node.isLeaf()) {
        answer.push_back(node.getCharacter());
        return answer;
    }
    if (node.left != nullptr) {
        answer.push_back('L');
        HuffTable(*node.left);
    }
    if (node.right != nullptr) {
        answer.push_back('R');
        HuffTable(*node.right);
    }
    return answer;
}

int main() {
    HuffmanTree t;
    t.compress("Hello There Are you?AA");
    return EXIT_SUCCESS;
}
