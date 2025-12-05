#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <string.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void readFile(const std::string filename,
              std::vector<std::vector<bool>> *values) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    values->push_back(std::vector<bool>());
    for (const auto &c : str) {
      values->back().emplace_back(c == '@');
    }
  }
}

uint64_t part1(const std::vector<std::vector<bool>> &values) {
  uint64_t total = 0;
  int32_t h = values.size();
  int32_t w = values.at(0).size();

  for (int32_t j = 0; j < h; ++j) {
    for (int32_t i = 0; i < w; ++i) {
      {
        uint32_t adj = 0;
        int32_t x_l = std::max(0, i - 1);
        int32_t x_r = std::min(i + 1, w - 1);
        int32_t y_l = std::max(0, j - 1);
        int32_t y_r = std::min(j + 1, h - 1);

        for (int32_t v = y_l; v <= y_r; ++v)
          for (int32_t u = x_l; u <= x_r; ++u)
            adj += values.at(v).at(u);
        adj -= values.at(j).at(i);
        total += values.at(j).at(i) && adj < 4;
      }
    }
  }
  return total;
}

uint64_t part2(std::vector<std::vector<bool>> &values) {
  uint64_t total = 0;
  uint64_t cur_total = 0;
  int32_t h = values.size();
  int32_t w = values.at(0).size();
  do {
    cur_total = 0;
    for (int32_t j = 0; j < h; ++j) {
      for (int32_t i = 0; i < w; ++i) {
        {
          uint32_t adj = 0;
          int32_t x_l = std::max(0, i - 1);
          int32_t x_r = std::min(i + 1, w - 1);
          int32_t y_l = std::max(0, j - 1);
          int32_t y_r = std::min(j + 1, h - 1);

          for (int32_t v = y_l; v <= y_r; ++v)
            for (int32_t u = x_l; u <= x_r; ++u)
              adj += values.at(v).at(u);
          adj -= values.at(j).at(i);
          if (values.at(j).at(i) && adj < 4) {
            values.at(j).at(i) = false;
            ++cur_total;
          }
        }
      }
    }
    total += cur_total;
  } while (cur_total != 0);
  return total;
}

int main(int argc, char *argv[]) {
  std::vector<std::vector<bool>> values;
  readFile("input.txt", &values);

  uint64_t part1_res = part1(values);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint64_t part2_res = part2(values);
  std::cout << "Part 2 : " << part2_res << '\n';
}
