#ifndef COMPRESSOR_LZ77CODEC_H
#define COMPRESSOR_LZ77CODEC_H

#include <string>

class LZ77Codec {
  static constexpr int SLICING_WINDOW_SIZE = 32;
  static constexpr char DELIMITER = '_';
  static std::string EOF_SIGN;

public:
  static std::string compress(const std::string &input_file_content);

  static std::string decompress(const std::string &input_file_content);

private:
  struct Match {
    int index;
    int length;
  };
};

#endif // COMPRESSOR_LZ77CODEC_H
