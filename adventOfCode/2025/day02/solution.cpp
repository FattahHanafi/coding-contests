#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void readFile(const std::string filename,
              std::vector<std::array<uint64_t, 2>> *values) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    std::array<uint64_t, 2> ranges = {0, 0};
    auto u = ranges.begin();
    for (auto &c : str) {
      if (c == '-') {
        u++;
      } else if (c == ',') {
        values->emplace_back(ranges);
        ranges.fill(0);
        u = ranges.begin();
      } else {
        *u = *u * 10 + c - '0';
      }
    }
    values->emplace_back(ranges);
  }
}

uint64_t part1(const std::vector<std::array<uint64_t, 2>> &values) {
  uint64_t total = 0;
  for (const auto &row : values) {
    for (auto id = row.front(); id <= row.back(); ++id) {
      auto str = std::to_string(id);
      auto len = str.size();
      if (!(len % 2)) {
        bool invalid = true;
        for (auto i = 0; i < len / 2; ++i) {
          invalid &= str.at(i) == str.at(i + len / 2);
        }
        if (invalid) {
          total += id;
        }
      }
    }
  }
  return total;
}

uint64_t part2(const std::vector<std::array<uint64_t, 2>> &values) {
  uint64_t total = 0;
  for (const auto &row : values) {
    for (auto id = row.front(); id <= row.back(); ++id) {
      auto str = std::to_string(id);
      auto len = str.size();
      bool complete_invalid = false;
      for (auto i = 1; i <= len / 2; ++i) {
        if (len % i == 0) {
          bool invalid = true;
          auto it_1 = str.cbegin();
          auto it_2 = str.cbegin();
          std::advance(it_2, i);
          while (it_2 != str.cend()) {
            if (*it_1 != *it_2) {
              invalid = false;
            }
            ++it_1;
            ++it_2;
          }
          complete_invalid |= invalid;
        }
      }
      if (complete_invalid) {
        total += id;
        continue;
      }
    }
  }
  return total;
}

int main(int argc, char *argv[]) {
  std::vector<std::array<uint64_t, 2>> values;
  readFile("input.txt", &values);

  uint64_t part1_res = part1(values);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint64_t part2_res = part2(values);
  std::cout << "Part 2 : " << part2_res << '\n';
}
