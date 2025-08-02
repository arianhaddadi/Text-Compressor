#include "huffman_tree.h"
#include <queue>

Node *HuffmanTree::constructTree(const std::string &input_file_content) {
  const std::vector<int> char_frequencies =
      getCharFrequencies(input_file_content);

  std::priority_queue<Node *, std::vector<Node *>, NodeComparator> queue;
  for (uint16_t i = 0; i < NUM_OF_CHARS; i++) {
    if (char_frequencies[i] > 0) {
      queue.push(new Node(i, char_frequencies[i]));
    }
  }

  while (queue.size() > 1) {
    Node *node1 = queue.top();
    queue.pop();

    Node *node2 = queue.top();
    queue.pop();

    /* Internal nodes of the tree do not represent a character, so NULL_SYMBOL
     * is used as their symbol */
    queue.push(new Node(NULL_SYMBOL, node1->getFreq() + node2->getFreq(), node1,
                        node2));
  }

  return queue.top();
}

std::vector<int>
HuffmanTree::getCharFrequencies(const std::string &input_file_content) {
  std::vector<int> char_frequencies(NUM_OF_CHARS, 0);
  for (const auto i : input_file_content) {
    char_frequencies[i]++;
  }
  return char_frequencies;
}

void HuffmanTree::dfs(const Node *node, std::vector<std::string> &codes,
                      const std::string &code) {
  if (node->getRight() == nullptr && node->getLeft() == nullptr) {
    codes[node->getSymbol()] = code;
  } else {
    dfs(node->getRight(), codes, code + RIGHT_CHILD_CHAR);
    dfs(node->getLeft(), codes, code + LEFT_CHILD_CHAR);
  }
}

std::vector<std::string> HuffmanTree::parse(const std::string &input) {
  const Node *root = constructTree(input);
  std::vector<std::string> codes(NUM_OF_CHARS);
  dfs(root, codes, "");
  return codes;
}
