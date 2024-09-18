#ifndef COMPRESSOR_TREE_H
#define COMPRESSOR_TREE_H

#include "node.h"
#include <map>
#include <queue>
#include <string>
#include <vector>

class Tree {
public:
  Tree() {
    root = nullptr;
    for (int i = 0; i < 256; i++) {
      charToFreqMap[i] = 0;
    }
  }

  void getCodes(std::vector<std::string> &codes) const;
  void makeTree(const std::string &inputFileContent);

private:
  Node *root;
  std::map<unsigned char, int>
      charToFreqMap; // Maps characters to the number of times they were
                     // repeated in the file
  std::priority_queue<Node *, std::vector<Node *>, NodeComparator> nodesQueue;

  void fillCharFreqMap(const std::string &inputFileContent);
  void makeInitialNodes();
  static void dfs(const Node *node, std::vector<std::string> &codes,
           const std::string &code = "");
};

#endif // COMPRESSOR_TREE_H
