#include "cipherist.h"

void Cipherist::encrypt(const uint8_t key, std::string &text) {
  for (char &i : text) {
    i += key;
  }
}

void Cipherist::decrypt(const uint8_t key, std::string &text) {
  for (char &i : text) {
    i -= key;
  }
}
