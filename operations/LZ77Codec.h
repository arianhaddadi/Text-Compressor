#ifndef COMPRESSOR_LZ77CODEC_H
#define COMPRESSOR_LZ77CODEC_H

#include "../Common.h"


class LZ77Codec {
public:
    static void compress(const string &inputFileContent, string *compressed);
    static void decompress(const string &inputFileContent, string *decompressed);
private:
    class Match {
    public:
        int index;
        int length;
    };
};


#endif //COMPRESSOR_LZ77CODEC_H
