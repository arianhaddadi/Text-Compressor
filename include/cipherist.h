#ifndef COMPRESSOR_CIPHERER_H
#define COMPRESSOR_CIPHERER_H

#include <string>

class Cipherist {
public:
  static void encrypt(uint8_t key, std::string &text);
  static void decrypt(uint8_t key, std::string &text);
};

#endif // COMPRESSOR_CIPHERER_H
