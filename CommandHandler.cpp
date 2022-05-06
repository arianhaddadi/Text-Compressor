#include "CommandHandler.h"
#include "tree/Tree.h"
#include "operations/Codec.h"
#include "operations/FileIO.h"
#include "operations/Cipherer.h"


void CommandHandler::execute() {
    vector<string> result;
    string inputFileContent;
    FileIO::read(inputFile, inputFileContent);

    if (command == "compress" || command == "compress_encrypt") {
        Tree *tree = new Tree();
        tree->makeTree(inputFileContent);

        string firstLine, compressed;
        Codec::compress(tree, &firstLine, &compressed, inputFileContent);
        if (command == "compress_encrypt") {
            Cipherer::encrypt(kNum, &compressed);
        }

        result.push_back(firstLine);
        result.push_back(compressed);
        FileIO::write(outputFile, result);
    }
    else if (command == "encrypt") {
        Cipherer::encrypt(kNum, &inputFileContent);
        result.push_back(inputFileContent);
        FileIO::write(outputFile, result);
    }
    else if(command == "decompress" || command == "decrypt_decompress") {
        size_t lineBreak = inputFileContent.find('\n');
        string keys = inputFileContent.substr(0, lineBreak);
        string compressed = inputFileContent.substr(lineBreak + 1);

        if (command == "decrypt_decompress") {
            Cipherer::decrypt(kNum, &compressed);
        }

        string decompressed;
        Codec::decompress(keys, compressed, &decompressed);

        result.push_back(decompressed);
        FileIO::write(outputFile, result);
    }
    else if (command == "decrypt") {
        Cipherer::decrypt(kNum, &inputFileContent);
        result.push_back(inputFileContent);
        FileIO::write(outputFile, result);
    }
    else {
        cout << "Wrong Command" << endl;
    }
}
