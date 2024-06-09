#include "HuffmanCodec.h"

int HuffmanCodec::getHuffmanCodes(std::map<std::string, unsigned char> *codeToCharMap, const std::string &keys) {
    std::stringstream ss(keys);
    std::string key;

    for (int i = 0; i < 256; i++) {
        ss >> key;
        (*codeToCharMap)[key] = i;
    }

    ss >> key; // last token was the length of compressed text
    int compressedSize = stoi(key);
    return compressedSize;
}

void HuffmanCodec::decompress(const std::string &keys, const std::string &compressed, std::string *decompressed) {

    std::map<std::string, unsigned char> codeToCharMap;
    int compressedSize = getHuffmanCodes(&codeToCharMap, keys);

    std::string compressedBits;
    for(char c : compressed) {
        compressedBits += std::bitset<8> (c).to_string();
    }
    if (compressedSize % 8 != 0) {
        compressedBits.erase(compressedBits.begin() + compressedSize, compressedBits.end());
    }

    std::string codeToken;
    for(char c : compressedBits) {
        codeToken += c;
        if (codeToCharMap.contains(codeToken)) {
            (*decompressed) += codeToCharMap[codeToken];
            codeToken.erase();
        }
    }
}

void HuffmanCodec::compress(Tree *tree, std::string *firstLine, std::string *compressed, const std::string &fileContent) {
    std::vector<std::string> codes(256);

    tree->getCodes(&codes);
    std::string compressedBits;
    for (unsigned char c : fileContent) {
        compressedBits += codes[c];
    }

    std::string compressedByte;
    for(int i = 0; i < compressedBits.size(); i+=8) {
        compressedByte = compressedBits.substr(i, 8);
        if (compressedByte.size() < 8) {
            size_t substringSize = compressedByte.size();
            for (int j = 0; j < 8 - substringSize; j++)
                compressedByte += "0";
        }
        char c = std::bitset<8>(compressedByte).to_ulong();
        (*compressed) += c;
    }

    for (const std::string &s : codes) {
        if (s.empty()) {
            (*firstLine) += "2 "; // 2 means that this character was not in the original file
        }
        else {
            (*firstLine) += s + " ";
        }
    }
    (*firstLine) += std::to_string(compressedBits.size()) + '\n';
}
