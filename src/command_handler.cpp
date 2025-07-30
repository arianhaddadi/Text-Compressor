#include <iostream>

#include "cipherist.h"
#include "command_handler.h"
#include "file_handler.h"
#include "huffman_codec.h"
#include "huffman_tree.h"
#include "lz77_codec.h"

void CommandHandler::execute(const std::string &input_filename,
                             const std::string &output_filename,
                             const std::string &command, const uint8_t k_num) {
  std::vector<std::string> result;
  std::string input_file_content = FileIO::read(input_filename);

  if (command == "compress" || command == "compress_encrypt") {
    const std::string lz_compressed = LZ77Codec::compress(input_file_content);

    auto [keys, huffman_compressed] = HuffmanCodec::compress(lz_compressed);

    if (command == "compress_encrypt") {
      Cipherist::encrypt(k_num, huffman_compressed);
    }

    result.push_back(keys);
    result.push_back(huffman_compressed);
    FileIO::write(output_filename, result);
  } else if (command == "encrypt") {
    Cipherist::encrypt(k_num, input_file_content);
    result.push_back(input_file_content);
    FileIO::write(output_filename, result);
  } else if (command == "decompress" || command == "decrypt_decompress") {
    const size_t line_break = input_file_content.find('\n');
    const std::string keys = input_file_content.substr(0, line_break);
    std::string compressed = input_file_content.substr(line_break + 1);

    if (command == "decrypt_decompress") {
      Cipherist::decrypt(k_num, compressed);
    }

    const std::string huffman_decompressed =
        HuffmanCodec::decompress(keys, compressed);

    const std::string lz_decompressed =
        LZ77Codec::decompress(huffman_decompressed);

    result.push_back(lz_decompressed);
    FileIO::write(output_filename, result);
  } else if (command == "decrypt") {
    Cipherist::decrypt(k_num, input_file_content);
    result.push_back(input_file_content);
    FileIO::write(output_filename, result);
  } else {
    std::cout << "Wrong Command" << std::endl;
  }
}
