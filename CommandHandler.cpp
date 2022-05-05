#include "CommandHandler.h"
#include "tree/Tree.h"
#include "operations/Codec.h"
#include "operations/FileIO.h"


void CommandHandler::execute() {
    Codec *codec = new Codec();
    vector<string> result;
    string fileContent;
    FileIO::read(inputFile, fileContent);

    if (command == "compress" || command == "encode") {
        Tree *tree = new Tree();
        tree->makeTree(fileContent);

        codec->compress(tree, result, fileContent);
        FileIO::write(outputFile, result);
    }
    else if(command == "decompress" || command == "decode") {
        codec->decompress(fileContent, result);
        FileIO::write(outputFile, result);
    }
    else {
        cout << "Wrong Command" << endl;
    }
}
