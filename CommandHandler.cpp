#include "CommandHandler.h"
#include "Tree/Tree.h"



void CommandHandler::execute() {
    Tree* tree = new Tree();
    tree->makeTree(inputFile);


}
