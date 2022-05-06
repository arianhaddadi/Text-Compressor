#include "Codec.h"

int Codec::getHuffmanCodes(map<string, unsigned char> *codeToCharMap, const string &keys) {
    stringstream ss(keys);
    string key;

    for (int i = 0; i < 256; i++) {
        ss >> key;
        (*codeToCharMap)[key] = i;
    }

    ss >> key; // last token was the length of compressed text
    int compressedSize = stoi(key);
    return compressedSize;
}

void Codec::decompress(const string &keys, const string &compressed, string *decompressed) {

    map<string, unsigned char> codeToCharMap;
    int compressedSize = getHuffmanCodes(&codeToCharMap, keys);

    string compressedBits;
    for(char c : compressed) {
        compressedBits += bitset<8> (c).to_string();
    }
    if (compressedSize % 8 != 0) {
        compressedBits.erase(compressedBits.begin() + compressedSize, compressedBits.end());
    }

    string codeToken;
    for(char c : compressedBits) {
        codeToken += c;
        if (codeToCharMap.contains(codeToken)) {
            (*decompressed) += codeToCharMap[codeToken];
            codeToken.erase();
        }
    }

}

void Codec::compress(Tree *tree, string *firstLine, string *compressed, const string &fileContent) {
    vector<string> codes(256);

    tree->getCodes(codes);
    string compressedBits;
    for (unsigned char c : fileContent) {
        compressedBits += codes[c];
    }

    string compressedByte;
    for(int i = 0; i < compressedBits.size(); i+=8) {
        compressedByte = compressedBits.substr(i, 8);
        if (compressedByte.size() < 8) {
            size_t substringSize = compressedByte.size();
            for (int j = 0; j < 8 - substringSize; j++)
                compressedByte += "0";
        }
        char c = bitset<8>(compressedByte).to_ulong();
        (*compressed) += c;
    }

    for (const string &s : codes) {
        if (s.empty()) {
            (*firstLine) += "2 "; // 2 means that this character was not in the original file
        }
        else {
            (*firstLine) += s + " ";
        }
    }
    (*firstLine) += to_string(compressedBits.size()) + '\n';
}
