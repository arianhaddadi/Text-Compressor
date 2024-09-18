#include "command_handler.h"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 4 && argc != 5) {
    std::cout << "Wrong number of arguments" << std::endl;
  } else {
    const std::string command = argv[1];
    const std::string inputFilename = argv[2];
    const std::string outputFilename = argv[3];
    const std::string kNum = (argc == 5) ? argv[4] : "0";

    CommandHandler::execute(inputFilename, outputFilename, command, stoi(kNum));
  }
  return 0;
}
