#ifndef COMPRESSOR_LZ77CODEC_H
#define COMPRESSOR_LZ77CODEC_H

#include "../common.h"


class LZ77Codec {
public:
    static void compress(const std::string &inputFileContent, std::string *compressed);
    static void decompress(const std::string &inputFileContent, std::string *decompressed);
private:
    struct Match {
        int index;
        int length;
    };
};


#endif //COMPRESSOR_LZ77CODEC_H
