#include "Cipherer.h"


void Cipherer::encrypt(int key, string *text) {
    for (char &i : *text) {
        i += key;
    }
}

void Cipherer::decrypt(int key, string *text) {
    for (char &i : *text) {
        i -= key;
    }
}
