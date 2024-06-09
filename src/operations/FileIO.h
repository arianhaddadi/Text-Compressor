#ifndef COMPRESSOR_FILEIO_H
#define COMPRESSOR_FILEIO_H

#include "../common.h"

class FileIO {
public:
    static void read(const std::string &filename, std::string &content);
    static void write(const std::string &filename, const std::vector<std::string> &content);
};


#endif //COMPRESSOR_FILEIO_H
