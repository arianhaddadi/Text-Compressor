#ifndef COMPRESSOR_CODEC_H
#define COMPRESSOR_CODEC_H

#include "../Common.h"
#include "../tree/Tree.h"


class Codec {
public:
    void compress(Tree *tree, vector<string> &result, const string &fileContent);
    void decompress(const string &fileContent, vector<string> &result);
    int getHuffmanCodes(map<string, char> *codeToCharMap, const string &keys);
};


#endif //COMPRESSOR_CODEC_H
