#include "FileIO.h"

void FileIO::read(const string &filename, string &content) {
    ifstream infile(filename);
    string line;
    while (getline(infile, line)) {
        content += line;
    }
    infile.close();
}

void FileIO::write(const string &filename, vector<string> &content) {
    ofstream outfile(filename);
    outfile << content[0];

    string substring;
    string compressed = content[1];
    for(int i = 0; i < compressed.size(); i+=8) {
        substring = compressed.substr(i, 8);
        if (substring.size() < 8) {
            for (int j = 0; j < 8 - substring.size(); j++)
                substring += "0";
        }

        char c = bitset<8>(substring).to_ulong();

        outfile.write(&c, sizeof(c));
    }

    outfile.close();
}
