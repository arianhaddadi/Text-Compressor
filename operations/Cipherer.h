#ifndef COMPRESSOR_CIPHERER_H
#define COMPRESSOR_CIPHERER_H

#include "../Common.h"

class Cipherer {
public:
    static void encrypt(int key, string *text);
    static void decrypt(int key, string *text);

};


#endif //COMPRESSOR_CIPHERER_H
