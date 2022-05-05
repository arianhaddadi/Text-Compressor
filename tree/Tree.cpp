#include "Tree.h"

void Tree::makeTree(string &fileContent) {
    fillCharFreqMap(fileContent);
    makeInitialNodes();

    Node *node1, *node2, *newNode;
    while(nodesQueue.size() > 1) {
        node1 = nodesQueue.top();
        nodesQueue.pop();

        node2 = nodesQueue.top();
        nodesQueue.pop();

        newNode = new Node(node1, node2, node1->getFreq() + node2->getFreq());
        nodesQueue.push(newNode);
    }

    root = nodesQueue.top();
    nodesQueue.pop();
}

void Tree::makeInitialNodes() {
    Node* newNode;
    for (int i = 0; i < 255; i++) {
        newNode = new Node(nullptr, nullptr, charFreqMap[i], i);
        nodesQueue.push(newNode);
    }
}

void Tree::fillCharFreqMap(string &fileContent) {
    for (int i = 0; i < fileContent.size(); i++) {
        charFreqMap[fileContent[i]]++;
    }
}

void Tree::getCodes(vector<string> &codes) {
    dfs(root, codes, "");
}

void Tree::dfs(Node *node, vector<string> &codes, string code) {
    if (node->getRight() == nullptr && node->getLeft() == nullptr) {
        codes[node->getSymbol()] = code;
    }
    else {
        dfs(node->getRight(), codes, code + "1");
        dfs(node->getLeft(), codes, code + "0");
    }
}
