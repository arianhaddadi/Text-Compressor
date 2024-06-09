#ifndef COMPRESSOR_TREE_H
#define COMPRESSOR_TREE_H

#include "Node.h"

class Tree {
public:
    Tree() {
        root = nullptr;
        for (int i = 0; i < 256; i++) {
            charFreqMap[i] = 0;
        }
    }

    void getCodes(std::vector<std::string> *codes);
    void makeTree(const std::string &inputFileContent);
private:
    Node* root;
    std::map<unsigned char, int> charFreqMap;
    std::priority_queue<Node*, std::vector<Node*>,
            decltype([](Node* lhs, Node* rhs) {return rhs->getFreq() <= lhs->getFreq(); })> nodesQueue;

    void fillCharFreqMap(const std::string &inputFileContent);
    void makeInitialNodes();
    void dfs(Node* node, std::vector<std::string> *codes, const std::string &code);
};


#endif //COMPRESSOR_TREE_H
