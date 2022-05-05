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

    void getCodes(vector<string> &codes);
    void makeTree(string &fileContent);
private:
    Node* root;
    map<unsigned char, int> charFreqMap;
    priority_queue<Node*, vector<Node*>, decltype([](Node* lhs, Node* rhs) {return rhs->getFreq() <= lhs->getFreq(); })> nodesQueue;

    void fillCharFreqMap(string &fileContent);
    void makeInitialNodes();
    void dfs(Node* node, vector<string> &codes, string code);
};


#endif //COMPRESSOR_TREE_H
