#include "cipherer.h"

void Cipherer::encrypt(int key, std::string &text) {
  for (char &i : text) {
    i += key;
  }
}

void Cipherer::decrypt(int key, std::string &text) {
  for (char &i : text) {
    i -= key;
  }
}
