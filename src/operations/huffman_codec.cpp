#include "huffman_codec.h"
#include <bitset>
#include <sstream>
#include <iostream>

// This is used to encode characters that did not exist in the input file
#define CHAR_NOT_FOUND_CODE "2"
#define BYTE_LEN 8

int HuffmanCodec::getHuffmanCodes(
    std::map<std::string, unsigned char> &codeToCharMap,
    const std::string &keys) {
  std::stringstream ss(keys);
  std::string key;

  for (uint16_t i = 0; i < 256; i++) {
    ss >> key;
    codeToCharMap[key] = i;
  }

  ss >> key; // last token was the length of compressed text
  const int compressedSize = stoi(key);
  return compressedSize;
}

void HuffmanCodec::decompress(const std::string &keys,
                              const std::string &compressed,
                              std::string &decompressed) {
  std::map<std::string, unsigned char> codeToCharMap;
  const int compressedSize = getHuffmanCodes(codeToCharMap, keys);

  std::string compressedBits;
  for (const char c : compressed) {
    compressedBits += std::bitset<BYTE_LEN>(c).to_string();
  }
  if (compressedSize % BYTE_LEN != 0) {
    compressedBits.erase(compressedBits.begin() + compressedSize,
                         compressedBits.end());
  }

  std::string codeToken;
  for (const char c : compressedBits) {
    codeToken += c;
    if (codeToCharMap.contains(codeToken)) {
      decompressed += codeToCharMap[codeToken];
      codeToken.erase();
    }
  }
}

void HuffmanCodec::compress(const Tree *tree, std::string &firstLine,
                            std::string &compressed,
                            const std::string &fileContent) {
  std::vector<std::string> codes(256);

  tree->getCodes(codes);
  std::string compressedBits;
  for (const unsigned char c : fileContent) {
    compressedBits += codes[c];
  }

  for (int i = 0; i < compressedBits.size(); i += BYTE_LEN) {
    std::string compressedByte = compressedBits.substr(i, BYTE_LEN);
    if (compressedByte.size() < BYTE_LEN) {
      /* If the number of bits is not a multiplier of BYTE_LEN, we add as many
       * "0"s as required to make the last chunk as long as BYTE_LEN. */
      const size_t substringSize = compressedByte.size();
      for (int j = 0; j < BYTE_LEN - substringSize; j++)
        compressedByte += "0";
    }
    const char c = std::stoi(compressedByte, nullptr, 2);
    compressed += c;
  }

  for (auto &code : codes) {
    if (code.empty()) {
      // character did not exist in the original file
      firstLine += CHAR_NOT_FOUND_CODE;
      firstLine += " ";
    } else {
      firstLine += code + " ";
    }
  }
  firstLine += std::to_string(compressedBits.size()) + '\n';
}
