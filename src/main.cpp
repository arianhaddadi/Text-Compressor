#include "command_handler.h"


int main(int argc, char *argv[]) {
    if (argc != 4 && argc != 5) {
        std::cout << "Wrong number of arguments" << std::endl;
    }
    else {
        std::string command = argv[1];
        std::string inputFilename = argv[2];
        std::string outputFilename = argv[3];
        std::string kNum = (argc == 5) ? argv[4] : "0";

        CommandHandler::execute(inputFilename, outputFilename, command, stoi(kNum));
    }
    return 0;
}
