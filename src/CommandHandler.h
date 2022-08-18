#ifndef COMPRESSOR_COMMANDHANDLER_H
#define COMPRESSOR_COMMANDHANDLER_H

#include "Common.h"


class CommandHandler {
public:
    CommandHandler(string inputFile, string outputFile, string command, string kNum): inputFile(inputFile), outputFile(outputFile), command(command), kNum(stoi(kNum)) {}
    void execute();
private:
    string inputFile;
    string outputFile;
    string command;
    int kNum;
};

#endif //COMPRESSOR_COMMANDHANDLER_H
