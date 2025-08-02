#ifndef COMPRESSOR_CMD_HANDLER_H
#define COMPRESSOR_CMD_HANDLER_H

#include <string>

class CommandHandler {
public:
  static void execute(const std::string &input_filename,
                      const std::string &output_filename,
                      const std::string &command, uint8_t k_num);
};

#endif // COMPRESSOR_CMD_HANDLER_H
