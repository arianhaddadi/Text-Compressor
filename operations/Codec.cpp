#include "Codec.h"

void Codec::decompress() {

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
    firstLine += to_string(compressed.size()) + "\n";

    result.push_back(firstLine);
    result.push_back(compressed);
}
