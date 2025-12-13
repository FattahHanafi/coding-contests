#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <set>
#include <sstream>
#include <stack>
#include <string.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

void readFile(const std::string filename,
              std::vector<std::pair<uint64_t, std::vector<uint64_t>>> *values) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    std::pair<uint64_t, std::vector<uint64_t>> row;
    for (size_t i = 0; i < str.size(); ++i) {
      if (str[i] == '#') {
        row.first |= 1 << (i - 1);
      }

      if (str[i] == '(') {
        row.second.emplace_back(0);
        ++i;
        while (str[i] != ')') {
          row.second.back() |= (1 << (str[i] - '0'));
          if (str[i + 1] == ',')
            ++i;
          ++i;
        }
      }

      if (str[i] == '{') {
        values->emplace_back(row);
        continue;
      }
    }
  }
}

uint64_t
part1(std::vector<std::pair<uint64_t, std::vector<uint64_t>>> &values) {
  uint64_t total = 0;
  for (auto row : values) {
    uint64_t total_press = 0;
    std::deque<uint64_t> states;
    states.push_back(0);
    auto it = std::find(states.cbegin(), states.cend(), row.first);
    while (it == states.cend()) {
      ++total_press;
      auto len = states.size();
      for (auto i = 0; i < len; ++i) {
        auto s = states.front();
        for (auto k : row.second) {
          states.push_back(s ^ k);
        }
        states.pop_front();
      }
      it = std::find(states.cbegin(), states.cend(), row.first);
    }
    total += total_press;
  }
  return total;
}

int main(int argc, char *argv[]) {
  std::vector<std::pair<uint64_t, std::vector<uint64_t>>> values;
  readFile("input.txt", &values);

  uint64_t part1_res = part1(values);
  std::cout << "Part 1 : " << part1_res << '\n';
}
