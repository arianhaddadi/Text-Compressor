#include "lz77_codec.h"


void LZ77Codec::compress(const std::string &inputFileContent, std::string &compressed) {
    int windowSize = SLICING_WINDOW_SIZE * 1024;
    int currentIndex = 0, matchCursorLeft, matchCursorRight, matchedLength, foundMatchIndexLeft;
    Match foundMatch;
    std::string token;
    while (currentIndex < inputFileContent.size()) {
        matchCursorLeft = std::max(0, currentIndex - windowSize);
        foundMatch.length = 0;
        foundMatch.index = currentIndex;
        while(matchCursorLeft < currentIndex) {
            if (inputFileContent[matchCursorLeft] == inputFileContent[currentIndex]) {
                foundMatchIndexLeft = matchCursorLeft;
                matchCursorRight = currentIndex + 1;
                matchCursorLeft++;
                matchedLength = 1;
                while (matchCursorLeft < currentIndex && matchCursorRight < inputFileContent.size()) {
                    if (matchedLength > 256 ||
                        inputFileContent[matchCursorLeft] != inputFileContent[matchCursorRight]) {
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
            }
            else {
                matchCursorLeft++;
            }
        }
        token = std::to_string(currentIndex - foundMatch.index) + DELIMITER;
        token += std::to_string(foundMatch.length) + DELIMITER;
        if (currentIndex + foundMatch.length < inputFileContent.size()) {
            token += inputFileContent[currentIndex + foundMatch.length];
            token += DELIMITER;
        }
        else {
            token += EOF_SIGN;
        }
        currentIndex += foundMatch.length + 1;
        compressed += token;
    }
}

void LZ77Codec::decompress(const std::string &inputFileContent, std::string &decompressed) {
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

        decompressed += decompressed.substr(decompressed.size() - stoi(leftOffset), stoi(length));
        if (nextChar != EOF_SIGN) {
            decompressed += nextChar;
        }
    }
}
