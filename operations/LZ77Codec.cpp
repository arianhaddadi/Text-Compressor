#include "LZ77Codec.h"


void LZ77Codec::compress(const string &inputFileContent, string *compressed) {
    int currentIndex = 0, matchCursorLeft, matchCursorRight, matchedLength, foundMatchIndexLeft;
    Match foundMatch;
    string token;
    while (currentIndex < inputFileContent.size()) {
        matchCursorLeft = 0;
        foundMatch.length = 0;
        foundMatch.index = currentIndex;
        while(matchCursorLeft < currentIndex) {
            if (inputFileContent[matchCursorLeft] == inputFileContent[currentIndex]) {
                foundMatchIndexLeft = matchCursorLeft;
                matchCursorRight = currentIndex + 1;
                matchCursorLeft++;
                matchedLength = 1;
                while (matchCursorLeft < currentIndex && matchCursorRight < inputFileContent.size()) {
                    if (inputFileContent[matchCursorLeft] != inputFileContent[matchCursorRight]) {
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
        token = to_string(currentIndex - foundMatch.index) + "_";
        token += to_string(foundMatch.length) + "_";
        if (currentIndex + foundMatch.length < inputFileContent.size() - 1) {
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

void LZ77Codec::decompress(const string &inputFileContent, string *decompressed) {
    stringstream ss(inputFileContent);
    string leftOffset, length, nextChar;

    while (getline(ss, leftOffset, '_')) {
        getline(ss, length, '_');
        getline(ss, nextChar, '_');

        (*decompressed) += (*decompressed).substr((*decompressed).size() - stoi(leftOffset), stoi(length));
        if (nextChar != "00") {
            (*decompressed) += nextChar;
        }
    }
}
