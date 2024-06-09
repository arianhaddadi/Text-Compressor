#include "LZ77Codec.h"


void LZ77Codec::compress(const std::string &inputFileContent, std::string *compressed) {
    int windowSize = 32 * 1024; // Slicing Window size is 32KB
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
        token = std::to_string(currentIndex - foundMatch.index) + "_";
        token += std::to_string(foundMatch.length) + "_";
        if (currentIndex + foundMatch.length < inputFileContent.size()) {
            token += inputFileContent[currentIndex + foundMatch.length];
            token += "_";
        }
        else {
            token += "00";
        }
        currentIndex += foundMatch.length + 1;
        (*compressed) += token;
    }
}

void LZ77Codec::decompress(const std::string &inputFileContent, std::string *decompressed) {
    std::stringstream ss(inputFileContent);
    std::string leftOffset, length, nextChar;

    while (getline(ss, leftOffset, '_')) {
        getline(ss, length, '_');
        getline(ss, nextChar, '_');
        if (nextChar.empty()) { // if the delimiter is the same as the character
            getline(ss, nextChar, '_');
            nextChar = "_";
        }

        (*decompressed) += (*decompressed).substr((*decompressed).size() - stoi(leftOffset), stoi(length));
        if (nextChar != "00") {
            (*decompressed) += nextChar;
        }
    }
}
