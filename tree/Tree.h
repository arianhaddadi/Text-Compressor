#ifndef COMPRESSOR_TREE_H
#define COMPRESSOR_TREE_H

#include "Node.h"


class Tree {
public:
    Tree() {
        root = nullptr;
        for (int i = 0; i < 255; i++) {
            charFreqMap[i] = 0;
        }
    }

    void makeTree(string fileName);
    void fillCharFreqMap(string filename);
    void makeInitialNodes();

private:
    Node* root;
    map<unsigned char, int> charFreqMap;
    priority_queue<Node*, vector<Node*>, decltype([](Node* lhs, Node* rhs) {return rhs->getFreq() < lhs->getFreq(); })> nodesQueue;
};


#endif //COMPRESSOR_TREE_H
