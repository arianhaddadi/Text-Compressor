#include "tree.h"

#define NULL_SYMBOL '\0'
#define RIGHT_CHILD_CHAR '1'
#define LEFT_CHILD_CHAR '0'

void Tree::makeTree(const std::string &inputFileContent) {
  fillCharFreqMap(inputFileContent);
  makeInitialNodes();

  while (nodesQueue.size() > 1) {
    Node *node1 = nodesQueue.top();
    nodesQueue.pop();

    Node *node2 = nodesQueue.top();
    nodesQueue.pop();

    /* internal nodes of the tree do not represent a character, so NULL_SYMBOL
     * is used as their symbol */
    auto *newNode = new Node(NULL_SYMBOL, node1->getFreq() + node2->getFreq(),
                             node1, node2);

    nodesQueue.push(newNode);
  }

  root = nodesQueue.top();
  nodesQueue.pop();
}

void Tree::makeInitialNodes() {
  for (int i = 0; i < 256; i++) {
    if (charToFreqMap[i] > 0) {
      auto *newNode = new Node(i, charToFreqMap[i]);
      nodesQueue.push(newNode);
    }
  }
}

void Tree::fillCharFreqMap(const std::string &inputFileContent) {
  for (unsigned char i : inputFileContent) {
    charToFreqMap[i]++;
  }
}

void Tree::getCodes(std::vector<std::string> &codes) const { dfs(root, codes); }

void Tree::dfs(const Node *node, std::vector<std::string> &codes,
               const std::string &code) {
  if (node->getRight() == nullptr && node->getLeft() == nullptr) {
    codes[node->getSymbol()] = code;
  } else {
    dfs(node->getRight(), codes, code + RIGHT_CHILD_CHAR);
    dfs(node->getLeft(), codes, code + LEFT_CHILD_CHAR);
  }
}
