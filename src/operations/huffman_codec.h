#ifndef COMPRESSOR_HUFFMANCODEC_H
#define COMPRESSOR_HUFFMANCODEC_H

#include "../common.h"
#include "../tree/tree.h"

#define CHAR_NOT_FOUND_CODE "2" // This is used to encode characters that did not exist in the input file
#define BYTE_LEN 8

class HuffmanCodec {
public:
    static void compress(Tree *tree, std::string &firstLine, std::string &compressed, const std::string &fileContent);
    static void decompress(const std::string &keys, const std::string &compressed, std::string &decompressed);

private:
    static int getHuffmanCodes(std::map<std::string, unsigned char> &codeToCharMap, const std::string &keys);
};


#endif //COMPRESSOR_HUFFMANCODEC_H
