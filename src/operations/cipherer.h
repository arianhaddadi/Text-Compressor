#ifndef COMPRESSOR_CIPHERER_H
#define COMPRESSOR_CIPHERER_H

#include "../common.h"

class Cipherer {
public:
    static void encrypt(int key, std::string &text);
    static void decrypt(int key, std::string &text);
};


#endif //COMPRESSOR_CIPHERER_H
