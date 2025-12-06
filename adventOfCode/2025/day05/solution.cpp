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
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

void readFile(const std::string filename,
              std::vector<std::pair<uint64_t, uint64_t>> *ranges,
              std::vector<uint64_t> *values) {
  std::ifstream file(filename);
  std::string str;
  char hyphen;
  while (std::getline(file, str)) {
    auto it = str.find('-');
    if (it != std::string::npos) {
      std::pair<uint64_t, uint64_t> pair;
      pair.first = std::stoll(str.substr(0, it));
      pair.second = std::stoll(str.substr(it + 1));
      ranges->push_back(pair);
    } else if (!str.empty()) {
      values->emplace_back(std::stoll(str));
    }
  }
}

uint64_t part1(const std::vector<std::pair<uint64_t, uint64_t>> &ranges,
               const std::vector<uint64_t> &values) {
  uint64_t total = 0;
  for (const auto &id : values) {
    for (const auto &range : ranges) {
      if (id >= range.first && id <= range.second) {
        // std::cout << id << " : " << range.first << " - " << range.second
        //           << std::endl;
        ++total;
        break;
      }
    }
  }
  return total;
}

uint64_t part2(const std::vector<std::pair<uint64_t, uint64_t>> &ranges) {
  std::vector<std::pair<uint64_t, uint64_t>> old_ranges;
  std::vector<std::pair<uint64_t, uint64_t>> new_ranges;
  old_ranges = ranges;

  uint64_t total = 0;
  bool modified = false;
  do {

    modified = false;
    for (const auto &range : old_ranges) {
      bool added = false;
      for (auto &row : new_ranges) {
        if (range.first <= row.first && range.second >= row.first) {
          row.first = range.first;
          added = true;
          modified = true;
        }
        if (range.second >= row.second && range.first <= row.second) {
          row.second = range.second;
          added = true;
          modified = true;
        }
        if (range.first >= row.first && range.second <= row.second) {
          added = true;
        }
      }
      if (!added) {
        new_ranges.emplace_back(range);
      }
    }

    old_ranges = new_ranges;
    new_ranges.clear();

  } while (modified);

  for (const auto &row : old_ranges) {
    total += (row.second - row.first) + 1;
  }
  return total;
}

int main(int argc, char *argv[]) {
  std::vector<std::pair<uint64_t, uint64_t>> ranges;
  std::vector<uint64_t> values;
  readFile("input.txt", &ranges, &values);

  uint64_t part1_res = part1(ranges, values);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint64_t part2_res = part2(ranges);
  std::cout << "Part 2 : " << part2_res << '\n';
}
