#ifndef COMPRESSOR_FILE_HANDLER_H
#define COMPRESSOR_FILE_HANDLER_H

#include <string>
#include <vector>

class FileIO {
public:
  static void read(const std::string &filename, std::string &content);
  static void write(const std::string &filename,
                    const std::vector<std::string> &content);
};

#endif // COMPRESSOR_FILE_HANDLER_H
