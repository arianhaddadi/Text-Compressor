#include "LZ77Codec.h"


void LZ77Codec::compress(const string &inputFileContent, string *compressed) {
    int windowSize = 32 * 1024; // Slicing Window size is 32KB
    int currentIndex = 0, matchCursorLeft, matchCursorRight, matchedLength, foundMatchIndexLeft;
    Match foundMatch;
    string token;
    while (currentIndex < inputFileContent.size()) {
        matchCursorLeft = max(0, currentIndex - windowSize);
        foundMatch.length = 0;
        foundMatch.index = currentIndex;
        while(matchCursorLeft < currentIndex) {
            if (inputFileContent[matchCursorLeft] == inputFileContent[currentIndex]) {
                foundMatchIndexLeft = matchCursorLeft;
                matchCursorRight = currentIndex + 1;
                matchCursorLeft++;
                matchedLength = 1;
                while (matchCursorLeft < currentIndex && matchCursorRight < inputFileContent.size()) {
                    if (matchedLength > 256 || inputFileContent[matchCursorLeft] != inputFileContent[matchCursorRight]) {
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
        token = to_string(currentIndex - foundMatch.index) + "|";
        token += to_string(foundMatch.length) + "|";
        if (currentIndex + foundMatch.length < inputFileContent.size()) {
            token += inputFileContent[currentIndex + foundMatch.length];
            token += "|";
        }
        else {
            token += "00";
        }
        currentIndex += foundMatch.length + 1;
        (*compressed) += token;
    }
}

void LZ77Codec::decompress(const string &inputFileContent, string *decompressed) {
    stringstream ss(inputFileContent);
    string leftOffset, length, nextChar;

    while (getline(ss, leftOffset, '|')) {
        getline(ss, length, '|');
        getline(ss, nextChar, '|');

        (*decompressed) += (*decompressed).substr((*decompressed).size() - stoi(leftOffset), stoi(length));
        if (nextChar != "00") {
            (*decompressed) += nextChar;
        }
    }
}
