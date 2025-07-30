#ifndef COMPRESSOR_HUFFMAN_CODEC_H
#define COMPRESSOR_HUFFMAN_CODEC_H

#include <map>
#include <string>
#include <utility>

#include "huffman_tree.h"

class HuffmanCodec {
  /** This is used to encode characters that did not exist in the input file.
   * The value can be anything other than 0 and 1 as we work with string
   * representation of bits. */
  static constexpr char CHAR_NOT_FOUND_CODE = '_';

public:
  static std::pair<std::string, std::string>
  compress(const std::string &file_content);

  static std::string decompress(const std::string &keys,
                                const std::string &compressed);

private:
  static int getHuffmanCodes(std::map<std::string, char> &code_to_char_map,
                             const std::string &keys);
};

#endif // COMPRESSOR_HUFFMAN_CODEC_H
