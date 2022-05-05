#include "Codec.h"

int Codec::getHuffmanCodes(map<string, char> *codeToCharMap, const string &keys) {
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

void Codec::decompress(const string &fileContent, vector<string> &result) {
    size_t lineBreak = fileContent.find('\n');
    string keys = fileContent.substr(0, lineBreak);
    string compressed = fileContent.substr(lineBreak + 1);

    map<string, char> codeToCharMap;
    int compressedSize = getHuffmanCodes(&codeToCharMap, keys);

    string compressedBits;
    for(char c : compressed) {
        compressedBits += bitset<8> (c).to_string();
    }
    compressedBits.erase(compressedBits.begin() + compressedSize);

    string codeToken, originalString;
    for(char c : compressedBits) {
        codeToken += c;
        if (codeToCharMap.contains(codeToken)) {
            originalString += codeToCharMap[codeToken];
            codeToken.erase();
        }
    }

    result.push_back(originalString);
}

void Codec::compress(Tree *tree, vector<string> &result, const string &fileContent) {
    vector<string> codes(256);
    tree->getCodes(codes);

    string compressed;
    for (char c : fileContent) {
        compressed += codes[c];
    }

    string firstLine;
    for (const string& s : codes) {
        firstLine += s + " ";
    }
    firstLine += to_string(compressed.size()) + '\n';

    result.push_back(firstLine);
    result.push_back(compressed);
}
