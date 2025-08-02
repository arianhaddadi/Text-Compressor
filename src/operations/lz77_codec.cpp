#include "lz77_codec.h"
#include <sstream>

std::string LZ77Codec::EOF_SIGN = "00";

std::string LZ77Codec::compress(const std::string &input_file_content) {
  constexpr int window_size = SLICING_WINDOW_SIZE * 1024;
  int current_index = 0;
  std::string compressed;
  while (current_index < input_file_content.size()) {
    Match found_match = {current_index, 0};
    int match_cursor_left = std::max(0, current_index - window_size);
    while (match_cursor_left < current_index) {
      if (input_file_content[match_cursor_left] ==
          input_file_content[current_index]) {
        const int found_match_index_left = match_cursor_left;
        int match_cursor_right = current_index + 1;
        match_cursor_left++;
        int matched_length = 1;
        while (match_cursor_left < current_index &&
               match_cursor_right < input_file_content.size()) {
          if (matched_length > 256 ||
              input_file_content[match_cursor_left] !=
                  input_file_content[match_cursor_right]) {
            break;
          }
          matched_length++;
          match_cursor_left++;
          match_cursor_right++;
        }
        if (matched_length > found_match.length) {
          found_match.length = matched_length;
          found_match.index = found_match_index_left;
        }
        match_cursor_left = found_match_index_left + 1;
      } else {
        match_cursor_left++;
      }
    }
    auto token = std::to_string(current_index - found_match.index) + DELIMITER;
    token += std::to_string(found_match.length) + DELIMITER;
    if (current_index + found_match.length < input_file_content.size()) {
      token += input_file_content[current_index + found_match.length];
      token += DELIMITER;
    } else {
      token += EOF_SIGN;
    }
    current_index += found_match.length + 1;
    compressed += token;
  }
  return compressed;
}

std::string LZ77Codec::decompress(const std::string &input_file_content) {
  std::string decompressed;

  std::stringstream ss(input_file_content);
  std::string left_offset, length, next_char;

  while (getline(ss, left_offset, DELIMITER)) {
    getline(ss, length, DELIMITER);
    getline(ss, next_char, DELIMITER);
    if (next_char.empty()) {
      // if the delimiter is the same as the character
      getline(ss, next_char, DELIMITER);
      next_char = DELIMITER;
    }

    decompressed += decompressed.substr(decompressed.size() - stoi(left_offset),
                                        stoi(length));
    if (next_char != EOF_SIGN) {
      decompressed += next_char;
    }
  }

  return decompressed;
}
