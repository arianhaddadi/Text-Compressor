#ifndef COMPRESSOR_CODEC_H
#define COMPRESSOR_CODEC_H

#include "../Common.h"
#include "../tree/Tree.h"


class Codec {
public:
    static void compress(Tree *tree, string *firstLine, string *compressed, const string &fileContent);
    static void decompress(const string &keys, const string &compressed, string *decompressed);

private:
    static int getHuffmanCodes(map<string, unsigned char> *codeToCharMap, const string &keys);
};


#endif //COMPRESSOR_CODEC_H
