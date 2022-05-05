#include "FileIO.h"

void FileIO::read(const string &filename, string &content) {
    ifstream infile(filename);
    string line;

    while (getline(infile, line)) {
        content += line + "\n";
    }

    content.erase(content.size()-1);
    infile.close();
}

void FileIO::write(const string &filename, vector<string> &content) {
    ofstream outfile(filename);
    outfile << content[0];

    if (content.size() > 1) {
        string substring;
        string compressed = content[1];
        for(int i = 0; i < compressed.size(); i+=8) {
            substring = compressed.substr(i, 8);
            if (substring.size() < 8) {
                size_t substringSize = substring.size();
                for (int j = 0; j < 8 - substringSize; j++)
                    substring += "0";
            }
            char c = bitset<8>(substring).to_ulong();

            outfile.write(&c, sizeof(c));
        }
    }

    outfile.close();
}
