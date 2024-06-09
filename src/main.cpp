#include "CommandHandler.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4 && argc != 5) {
        cout << "Wrong number of arguments" << endl;
    }
    else {
        string command = argv[1];
        string inputFilename = argv[2];
        string outputFilename = argv[3];
        string kNum = (argc == 5) ? argv[4] : "0";

        auto *commandHandler = new CommandHandler(inputFilename, outputFilename, command, kNum);
        commandHandler->execute();
    }
    return 0;
}
