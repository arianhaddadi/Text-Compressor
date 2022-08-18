#ifndef COMPRESSOR_NODE_H
#define COMPRESSOR_NODE_H

#include "../Common.h"


class Node {
public:
    Node(Node* right, Node* left, int freq, unsigned char symbol = '\0'): right(right), left(left), freq(freq), symbol(symbol) {}

    Node* getRight() {
        return right;
    }

    Node* getLeft() {
        return left;
    }

    int getFreq() {
        return freq;
    }

    unsigned char getSymbol() {
        return symbol;
    }

private:
    int freq;
    unsigned char symbol;
    Node* right;
    Node* left;
};


#endif //COMPRESSOR_NODE_H
