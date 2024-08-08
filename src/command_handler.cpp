#include "command_handler.h"
#include "cipherer.h"
#include "file_handler.h"
#include "huffman_codec.h"
#include "lz77_codec.h"
#include "tree.h"
#include <iostream>

void CommandHandler::execute(const std::string &inputFile,
                             const std::string &outputFile,
                             const std::string &command, int kNum) {
  std::vector<std::string> result;
  std::string inputFileContent;
  FileIO::read(inputFile, inputFileContent);

  if (command == "compress" || command == "compress_encrypt") {
    std::string lzCompressed;
    LZ77Codec::compress(inputFileContent, lzCompressed);

    Tree *tree = new Tree();
    tree->makeTree(lzCompressed);

    std::string firstLine, huffmanCompressed;
    HuffmanCodec::compress(tree, firstLine, huffmanCompressed, lzCompressed);
    if (command == "compress_encrypt") {
      Cipherer::encrypt(kNum, huffmanCompressed);
    }

    result.push_back(firstLine);
    result.push_back(huffmanCompressed);
    FileIO::write(outputFile, result);
  } else if (command == "encrypt") {
    Cipherer::encrypt(kNum, inputFileContent);
    result.push_back(inputFileContent);
    FileIO::write(outputFile, result);
  } else if (command == "decompress" || command == "decrypt_decompress") {
    size_t lineBreak = inputFileContent.find('\n');
    std::string keys = inputFileContent.substr(0, lineBreak);
    std::string compressed = inputFileContent.substr(lineBreak + 1);

    if (command == "decrypt_decompress") {
      Cipherer::decrypt(kNum, compressed);
    }

    std::string huffmanDecompressed;
    HuffmanCodec::decompress(keys, compressed, huffmanDecompressed);

    std::string lzDecompressed;
    LZ77Codec::decompress(huffmanDecompressed, lzDecompressed);

    result.push_back(lzDecompressed);
    FileIO::write(outputFile, result);
  } else if (command == "decrypt") {
    Cipherer::decrypt(kNum, inputFileContent);
    result.push_back(inputFileContent);
    FileIO::write(outputFile, result);
  } else {
    std::cout << "Wrong Command" << std::endl;
  }
}
