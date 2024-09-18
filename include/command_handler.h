#ifndef COMPRESSOR_CMD_HANDLER_H
#define COMPRESSOR_CMD_HANDLER_H

#include <string>

class CommandHandler {
public:
  static void execute(const std::string &inputFile,
                      const std::string &outputFile, const std::string &command,
                      uint8_t kNum);
};

#endif // COMPRESSOR_CMD_HANDLER_H
