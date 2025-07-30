#ifndef COMPRESSOR_NODE_H
#define COMPRESSOR_NODE_H

class Node {
public:
  Node(const unsigned char symbol, const int freq, Node *right, Node *left)
      : freq(freq), symbol(symbol), right(right), left(left) {}

  Node(const unsigned char symbol, const int freq)
      : freq(freq), symbol(symbol) {}

  Node *getRight() const { return right; }

  Node *getLeft() const { return left; }

  int getFreq() const { return freq; }

  unsigned char getSymbol() const { return symbol; }

private:
  int freq;
  unsigned char symbol;
  Node *right = nullptr;
  Node *left = nullptr;
};

struct NodeComparator {
  bool operator()(const Node *lhs, const Node *rhs) const {
    return rhs->getFreq() <= lhs->getFreq();
  }
};

#endif // COMPRESSOR_NODE_H
