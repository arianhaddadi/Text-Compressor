#ifndef COMPRESSOR_CMDHNDLR_H
#define COMPRESSOR_CMDHNDLR_H

#include <string>

class CommandHandler {
public:
  static void execute(const std::string &inputFile,
                      const std::string &outputFile, const std::string &command,
                      int kNum);
};

#endif // COMPRESSOR_CMDHNDLR_H
