#ifndef COMPRESSOR_HUFFMANCODEC_H
#define COMPRESSOR_HUFFMANCODEC_H

#include "tree.h"
#include <map>
#include <string>

class HuffmanCodec {
public:
  static void compress(Tree *tree, std::string &firstLine,
                       std::string &compressed, const std::string &fileContent);
  static void decompress(const std::string &keys, const std::string &compressed,
                         std::string &decompressed);

private:
  static int
  getHuffmanCodes(std::map<std::string, unsigned char> &codeToCharMap,
                  const std::string &keys);
};

#endif // COMPRESSOR_HUFFMANCODEC_H
