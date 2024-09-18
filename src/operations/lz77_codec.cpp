#include "lz77_codec.h"
#include <sstream>

#define SLICING_WINDOW_SIZE 32
#define DELIMITER '_'
#define EOF_SIGN "00"

void LZ77Codec::compress(const std::string &inputFileContent,
                         std::string &compressed) {
  constexpr int windowSize = SLICING_WINDOW_SIZE * 1024;
  int currentIndex = 0;
  while (currentIndex < inputFileContent.size()) {
    Match foundMatch = {currentIndex, 0};
    int matchCursorLeft = std::max(0, currentIndex - windowSize);
    while (matchCursorLeft < currentIndex) {
      if (inputFileContent[matchCursorLeft] == inputFileContent[currentIndex]) {
        const int foundMatchIndexLeft = matchCursorLeft;
        int matchCursorRight = currentIndex + 1;
        matchCursorLeft++;
        int matchedLength = 1;
        while (matchCursorLeft < currentIndex &&
               matchCursorRight < inputFileContent.size()) {
          if (matchedLength > 256 || inputFileContent[matchCursorLeft] !=
                                         inputFileContent[matchCursorRight]) {
            break;
          }
          matchedLength++;
          matchCursorLeft++;
          matchCursorRight++;
        }
        if (matchedLength > foundMatch.length) {
          foundMatch.length = matchedLength;
          foundMatch.index = foundMatchIndexLeft;
        }
        matchCursorLeft = foundMatchIndexLeft + 1;
      } else {
        matchCursorLeft++;
      }
    }
    auto token = std::to_string(currentIndex - foundMatch.index) + DELIMITER;
    token += std::to_string(foundMatch.length) + DELIMITER;
    if (currentIndex + foundMatch.length < inputFileContent.size()) {
      token += inputFileContent[currentIndex + foundMatch.length];
      token += DELIMITER;
    } else {
      token += EOF_SIGN;
    }
    currentIndex += foundMatch.length + 1;
    compressed += token;
  }
}

void LZ77Codec::decompress(const std::string &inputFileContent,
                           std::string &decompressed) {
  std::stringstream ss(inputFileContent);
  std::string leftOffset, length, nextChar;

  while (getline(ss, leftOffset, DELIMITER)) {
    getline(ss, length, DELIMITER);
    getline(ss, nextChar, DELIMITER);
    if (nextChar.empty()) {
      // if the delimiter is the same as the character
      getline(ss, nextChar, DELIMITER);
      nextChar = DELIMITER;
    }

    decompressed += decompressed.substr(decompressed.size() - stoi(leftOffset),
                                        stoi(length));
    if (nextChar != EOF_SIGN) {
      decompressed += nextChar;
    }
  }
}
