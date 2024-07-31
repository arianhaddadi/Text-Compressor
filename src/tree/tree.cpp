#include "tree.h"

void Tree::makeTree(const std::string &inputFileContent) {
    fillCharFreqMap(inputFileContent);
    makeInitialNodes();

    Node *node1, *node2, *newNode;
    while(nodesQueue.size() > 1) {
        node1 = nodesQueue.top();
        nodesQueue.pop();

        node2 = nodesQueue.top();
        nodesQueue.pop();

        // internal nodes of the tree do not represent a character, so NULL_SYMBOL is used as their symbol
        newNode = new Node(NULL_SYMBOL, node1->getFreq() + node2->getFreq(), node1, node2);

        nodesQueue.push(newNode);
    }

    root = nodesQueue.top();
    nodesQueue.pop();
}

void Tree::makeInitialNodes() {
    Node* newNode;
    for (int i = 0; i < 256; i++) {
        if (charToFreqMap[i] > 0) {
            newNode = new Node(i, charToFreqMap[i]);
            nodesQueue.push(newNode);
        }
    }
}

void Tree::fillCharFreqMap(const std::string &inputFileContent) {
    for (unsigned char i : inputFileContent) {
        charToFreqMap[i]++;
    }
}

void Tree::getCodes(std::vector<std::string> &codes) const {
    dfs(root, codes);
}

void Tree::dfs(Node *node, std::vector<std::string> &codes, const std::string &code) const {
    if (node->getRight() == nullptr && node->getLeft() == nullptr) {
        codes[node->getSymbol()] = code;
    }
    else {
        dfs(node->getRight(), codes, code + RIGHT_CHILD_CHAR);
        dfs(node->getLeft(), codes, code + LEFT_CHILD_CHAR);
    }
}
