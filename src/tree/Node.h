#ifndef COMPRESSOR_NODE_H
#define COMPRESSOR_NODE_H

#include "../common.h"

#define NULL_SYMBOL '\0'

class Node {
public:
    Node(unsigned char symbol, int freq, Node* right = nullptr,
         Node* left = nullptr): symbol(symbol), freq(freq),
                                right(right), left(left) {}

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

struct NodeComparator {
    bool operator()(Node* lhs, Node* rhs) const {
        return rhs->getFreq() <= lhs->getFreq();
    }
};


#endif //COMPRESSOR_NODE_H
