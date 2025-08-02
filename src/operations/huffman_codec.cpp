#include <bitset>
#include <cstdint>
#include <sstream>

#include "huffman_codec.h"

/** Num of bits in a byte. */
constexpr int BYTE_LEN = 8;

int HuffmanCodec::getHuffmanCodes(std::map<std::string, char> &code_to_char_map,
                                  const std::string &keys) {
  std::stringstream ss(keys);
  std::string key;

  for (uint16_t i = 0; i < 256; i++) {
    ss >> key;
    code_to_char_map[key] = i;
  }

  ss >> key; // last token was the length of compressed text
  return stoi(key);
}

std::string HuffmanCodec::decompress(const std::string &keys,
                                     const std::string &compressed) {
  std::map<std::string, char> code_to_char_map;
  const int compressed_size = getHuffmanCodes(code_to_char_map, keys);

  std::string compressed_bits;
  for (const auto c : compressed) {
    compressed_bits += std::bitset<BYTE_LEN>(c).to_string();
  }
  if (compressed_size % BYTE_LEN != 0) {
    compressed_bits.erase(compressed_bits.begin() + compressed_size,
                          compressed_bits.end());
  }

  std::string decompressed;
  std::string code_token;
  for (const auto c : compressed_bits) {
    code_token += c;
    if (code_to_char_map.contains(code_token)) {
      decompressed += code_to_char_map[code_token];
      code_token.erase();
    }
  }

  return decompressed;
}

std::pair<std::string, std::string>
HuffmanCodec::compress(const std::string &file_content) {
  const std::vector<std::string> codes = HuffmanTree::parse(file_content);

  std::string compressed_bits;
  for (const auto c : file_content) {
    compressed_bits += codes[c];
  }

  std::string compressed;
  for (int i = 0; i < compressed_bits.size(); i += BYTE_LEN) {
    std::string compressed_byte = compressed_bits.substr(i, BYTE_LEN);
    if (compressed_byte.size() < BYTE_LEN) {
      /* If the number of bits is not a multiplier of BYTE_LEN, we add as many
       * "0"s as required to make the last chunk as long as BYTE_LEN. */
      for (int j = 0; j < BYTE_LEN - compressed_byte.size(); j++)
        compressed_byte += "0";
    }
    const char c = std::stoi(compressed_byte, nullptr, 2);
    compressed += c;
  }

  std::string keys;
  for (const auto &code : codes) {
    if (code.empty()) {
      // character did not exist in the original file
      keys += CHAR_NOT_FOUND_CODE;
    } else {
      keys += code;
    }
    keys += " ";
  }
  keys += std::to_string(compressed_bits.size()) + '\n';

  return std::pair{keys, compressed};
}
