#include "CommandHandler.h"
#include "tree/Tree.h"
#include "operations/HuffmanCodec.h"
#include "operations/FileIO.h"
#include "operations/Cipherer.h"
#include "operations/LZ77Codec.h"


void CommandHandler::execute() {
    vector<string> result;
    string inputFileContent;
    FileIO::read(inputFile, inputFileContent);

    if (command == "compress" || command == "compress_encrypt") {
        string lzCompressed;
        LZ77Codec::compress(inputFileContent, &lzCompressed);

        Tree *tree = new Tree();
        tree->makeTree(lzCompressed);

        string firstLine, huffmanCompressed;
        HuffmanCodec::compress(tree, &firstLine, &huffmanCompressed, lzCompressed);
        if (command == "compress_encrypt") {
            Cipherer::encrypt(kNum, &huffmanCompressed);
        }

        result.push_back(firstLine);
        result.push_back(huffmanCompressed);
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

        string huffmanDecompressed;
        HuffmanCodec::decompress(keys, compressed, &huffmanDecompressed);

        string lzDecompressed;
        LZ77Codec::decompress(huffmanDecompressed, &lzDecompressed);


        result.push_back(lzDecompressed);
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
