#include "Tree.h"


void Tree::makeTree(string fileName) {
    fillCharFreqMap(fileName);
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

void Tree::fillCharFreqMap(string filename) {
    ifstream infile(filename);
    char* character = new char[1];

    while (!infile.eof()) {
        infile.read(character, 1);
        charFreqMap[*character]++;
    }

    infile.close();
}
