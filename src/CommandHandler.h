#ifndef COMPRESSOR_CMDHNDLR_H
#define COMPRESSOR_CMDHNDLR_H

#include "common.h"


class CommandHandler {
public:
    CommandHandler(std::string inputFile, std::string outputFile, std::string command, std::string kNum):
        inputFile(inputFile), outputFile(outputFile), command(command), kNum(stoi(kNum)) {}
    void execute();
private:
    std::string inputFile;
    std::string outputFile;
    std::string command;
    int kNum;
};

#endif //COMPRESSOR_CMDHNDLR_H
