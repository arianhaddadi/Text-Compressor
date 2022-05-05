#include "CommandHandler.h"
#include "Tree/Tree.h"
#include "operations/Codec.h"
#include "operations/FileIO.h"


void CommandHandler::execute() {
    vector<string> result;

    string fileContent;
    FileIO::read(inputFile, fileContent);

    Tree *tree = new Tree();
    tree->makeTree(fileContent);

    Codec *codec = new Codec();
    codec->compress(tree, result, fileContent);

    FileIO::write(outputFile, result);
}
