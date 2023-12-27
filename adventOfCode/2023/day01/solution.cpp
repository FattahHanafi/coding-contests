#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

void readFile(const std::string filename, std::vector<std::string> *input) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    input->push_back(str);
  }
}

uint32_t part1(std::vector<std::string> *input) {
  uint32_t total = 0;
  uint8_t nums[] = {0, 0};
  for (auto &line : *input) {
    auto first = line.find_first_of("0123456789");
    auto last = line.find_last_of("0123456789");
    nums[0] = line[first] - '0';
    nums[1] = line[last] - '0';
    total += 10 * nums[0] + nums[1];
  }
  return total;
}

size_t find_first(const std::string *str, const std::string *token) {
  size_t idx = 0;
  const size_t token_len = token->length();
  for (idx = str->find(token[0], idx); idx != std::string::npos;) {
    if (str->compare(idx, token_len, *token) == 0)
      return idx;
    ++idx;
  }
  return std::string::npos;
}

uint32_t part2(std::vector<std::string> *input) {
  size_t indices[9];
  std::array<std::string, 9> values = {"o1e", "t2o", "t3e", "f4r", "f5e",
                                       "s6x", "s7n", "e8t", "n9e"};
  size_t min = std::string::npos;
  uint8_t num = 0;
  std::array<std::string, 9> tokens = {"one", "two",   "three", "four", "five",
                                       "six", "seven", "eight", "nine"};
  for (auto &line : *input) {
    while (true) {
      for (uint8_t i = 0; i < tokens.size(); ++i) {
        indices[i] = find_first(&line, &tokens.at(i));
        if (indices[i] < min) {
          min = indices[i];
          num = i;
        }
      }
      if (min != std::string::npos) {
        line.replace(min, tokens[num].length(), values[num]);
        min = std::string::npos;
      } else {
        break;
      }
    }
  }
  return part1(input);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> text;
  readFile("input.txt", &text);

  uint32_t part1_res = part1(&text);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint32_t part2_res = part2(&text);
  std::cout << "Part 2 : " << part2_res << '\n';
}
