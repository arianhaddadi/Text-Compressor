#ifndef COMPRESSOR_TREE_H
#define COMPRESSOR_TREE_H

#include <cstdint>
#include <string>
#include <vector>

#include "node.h"

class HuffmanTree {
  static constexpr uint16_t NUM_OF_CHARS = 256;
  static constexpr char NULL_SYMBOL = '\0';
  static constexpr char RIGHT_CHILD_CHAR = '1';
  static constexpr char LEFT_CHILD_CHAR = '0';

public:
  static std::vector<std::string> parse(const std::string &input);

private:
  static Node *constructTree(const std::string &input_file_content);

  static std::vector<int>
  getCharFrequencies(const std::string &input_file_content);

  static void dfs(const Node *node, std::vector<std::string> &codes,
                  const std::string &code);
};

#endif // COMPRESSOR_TREE_H
