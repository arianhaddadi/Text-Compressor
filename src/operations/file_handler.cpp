#include "file_handler.h"
#include <fstream>

std::string FileIO::read(const std::string &filename) {
  std::string content;

  std::ifstream infile(filename);

  std::string line;
  while (getline(infile, line)) {
    content += line + "\n";
  }
  content.erase(content.size() - 1);

  infile.close();

  return content;
}

void FileIO::write(const std::string &filename,
                   const std::vector<std::string> &content) {
  std::ofstream outfile(filename);

  for (const auto &s : content) {
    outfile << s;
  }

  outfile.close();
}
