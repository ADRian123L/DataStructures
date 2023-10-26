#include "HuffmanTree.hpp"

HuffmanTree::~HuffmanTree() {}

std::string HuffmanTree::serializeTree() const {
    std::string answer;
    HuffTable(ptr_to_tree, answer);
    return answer;
}

std::string HuffmanTree::decompress(const std::string inputCode,
                                    const std::string serializedTree) {
    std::string          answer;
    stack<HuffmanNode *> st; // Stack to store the node
    for (std::string::const_iterator ptr = serializedTree.cbegin();
         ptr != serializedTree.cend();
         ++ptr) {
        if (*ptr == LEAF) {
            HuffmanNode *tmp_ptr = new HuffmanNode(*(++ptr), size_t());
            st.push(tmp_ptr);
        }
        else if (*ptr == BRANCH) {
            HuffmanNode *ptr_to_second = st.get();
            st.pop();
            HuffmanNode *ptr_to_first = st.get();
            st.pop();
            HuffmanNode *tmp_ptr = new HuffmanNode(
                char(), size_t(), nullptr, ptr_to_first, ptr_to_second);
            ptr_to_first->parent = ptr_to_second->parent = tmp_ptr;
            st.push(tmp_ptr);
        }
    }
    std::string map[128];
    HuffS(st.get(), map); // Create a map with the encodings
    // Decompress the string:
    std::string codings;
    for (auto &ptr : inputCode) {
        codings.push_back(ptr);
        std::string tmp = HuffConvert(codings, map);
        if (!tmp.empty()) {
            answer += tmp;
            codings.clear();
        }
    }
    return answer;
}

std::string HuffmanTree::HuffConvert(std::string &code,
                                     std::string *map) const {
    std::string answer;
    for (std::size_t i = 0; i < 128; ++i) {
        if (code == map[i]) {
            answer.push_back(static_cast<char>(i));
        }
    }
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
    std::string table[128];
    HuffS(ptr_to_tree, table);
    for (auto &i : inputStr) {
        compressed_hoff_code += table[static_cast<int>(i)];
    }
    return compressed_hoff_code;
}

void HuffmanTree::HuffS(HuffmanNode *node, std::string *h_map) const {
    static std::string answer;
    if (node->isLeaf()) {
        h_map[static_cast<int>(node->getCharacter())] = answer;
        return;
    }
    if (node->left) {
        answer.push_back(ZERO);
        HuffS(node->left, h_map);
        answer.pop_back();
    }
    if (node->right) {
        answer.push_back(ONE);
        HuffS(node->right, h_map);
        answer.pop_back();
    }
}

void HuffmanTree::HuffTable(HuffmanNode *node, std::string &answer) const {
    if (node->left != nullptr) {
        HuffTable(node->left, answer);
    }
    if (node->right != nullptr) {
        HuffTable(node->right, answer);
    }
    if (node->isLeaf()) {
        answer.push_back(LEAF);
        answer.push_back(node->getCharacter());
    }
    else {
        answer.push_back(BRANCH);
    }
    return;
}
