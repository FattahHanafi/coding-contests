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
              std::vector<std::vector<uint32_t>> *values) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    values->push_back(std::vector<uint32_t>());
    for (const auto &c : str) {
      values->back().emplace_back(c - '0');
    }
  }
}

uint64_t part1(const std::vector<std::vector<uint32_t>> &values) {
  std::vector<uint32_t> max_jol;
  for (const auto &row : values) {
    auto max_it_1 = std::max_element(row.cbegin(), --row.cend());
    auto max_it_2 = std::max_element(max_it_1 + 1, row.cend());
    max_jol.emplace_back(*max_it_1 * 10 + *max_it_2);
  }
  return std::accumulate(max_jol.cbegin(), max_jol.cend(), 0);
}

uint64_t part2(const std::vector<std::vector<uint32_t>> &values) {
  std::vector<uint64_t> max_jol;
  for (const auto &row : values) {
    size_t len = 12;
    max_jol.emplace_back(0);
    auto first_it = row.cbegin();
    auto last_it = row.cend();
    std::advance(last_it, -len);
    int32_t s = len - 1;
    while (s >= 0) {
      last_it = row.cend();
      std::advance(last_it, -s);
      first_it = std::max_element(first_it, last_it);
      max_jol.back() = max_jol.back() * 10 + *first_it;
      ++last_it;
      ++first_it;
      --s;
    }
  }
  return std::accumulate(max_jol.cbegin(), max_jol.cend(), std::uint64_t(0));
}

int main(int argc, char *argv[]) {
  std::vector<std::vector<uint32_t>> values;
  readFile("input.txt", &values);

  uint64_t part1_res = part1(values);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint64_t part2_res = part2(values);
  std::cout << "Part 2 : " << part2_res << '\n';
}
