#ifndef COMPRESSOR_FILEIO_H
#define COMPRESSOR_FILEIO_H

#include "../Common.h"

class FileIO {
public:
    static void read(const string &filename, string &content);
    static void write(const string &filename, vector<string> &content);
};


#endif //COMPRESSOR_FILEIO_H
