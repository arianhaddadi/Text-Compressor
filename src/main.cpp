#include <cstdint>
#include <iostream>

#include "command_handler.h"

int main(const int argc, char *argv[]) {
  if (argc != 4 && argc != 5) {
    std::cout << "Wrong number of arguments" << std::endl;
  } else {
    const std::string command = argv[1];
    const std::string input_filename = argv[2];
    const std::string output_filename = argv[3];
    const uint8_t k_num = (argc == 5) ? std::stoi(argv[4]) : 0;

    CommandHandler::execute(input_filename, output_filename, command, k_num);
  }
  return 0;
}
