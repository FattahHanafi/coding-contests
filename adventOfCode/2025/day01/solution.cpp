#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

void readFile(const std::string filename, std::vector<int32_t> *values) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    str.at(0) = str.at(0) == 'L' ? '+' : '-';
    values->emplace_back(std::stoi(str));
  }
}

uint32_t part1(std::vector<int32_t> values) {
  int32_t value = 50;
  int32_t total = 0;
  for (const auto &v : values) {
    value += v;
    value %= 100;
    total += (value == 0);
  }
  return total;
}

int main(int argc, char *argv[]) {
  std::vector<int32_t> values;
  readFile("input.txt", &values);
  int part1_res = part1(values);
  std::cout << "Part 1 : " << part1_res << '\n';
}
