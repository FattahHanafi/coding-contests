#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string.h>
#include <string>
#include <vector>

#include <set>

void readFile(const std::string filename, std::vector<std::string> *input) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    input->push_back(str);
  }
}

struct game {
  std::vector<uint32_t> wins;
  std::vector<uint32_t> nums;
  uint32_t count = 1;

  uint32_t win_count() {
    uint32_t win = 0;
    for (auto n : nums)
      for (auto w : wins)
        if (w == n)
          ++win;
    return win;
  }

  uint32_t score() {
    uint32_t sc = 0;
    if (win_count())
      sc = count * (1 << (win_count() - 1));
    return sc;
  }
};

void parse_cards(std::vector<std::string> *input, std::vector<game> *games) {
  std::smatch match;
  std::regex reg("[\\d]+");

  for (auto &line : *input) {
    game tmp;
    uint32_t idx_0 = line.find(':');
    uint32_t idx_1 = line.find('|');
    auto win_str = line.substr(idx_0, idx_1 - idx_0);
    auto num_str = line.substr(idx_1, line.length() - idx_1);
    auto win_it = std::sregex_iterator(win_str.cbegin(), win_str.cend(), reg);
    auto win_end = std::sregex_iterator();
    auto num_it = std::sregex_iterator(num_str.cbegin(), num_str.cend(), reg);
    auto num_end = std::sregex_iterator();
    while (win_it != win_end) {
      tmp.wins.push_back(std::stoi(win_it->str()));
      ++win_it;
    }
    while (num_it != num_end) {
      tmp.nums.push_back(std::stoi(num_it->str()));
      ++num_it;
    }
    games->push_back(tmp);
  }
}

uint32_t part1(std::vector<game> *games) {
  uint32_t total = 0;
  for (auto g : *games) {
    total += g.score();
  }
  return total;
}

uint32_t part2(std::vector<game> *games) {
  for (uint32_t i = 0; i < games->size(); ++i) {
    uint32_t w = games->at(i).win_count();
    for (uint32_t j = 1; j <= w; ++j) {
      uint32_t q = i + j;
      if (q < games->size()) {
        games->at(q).count += games->at(i).count;
      }
    }
  }

  uint32_t total = 0;
  for (auto g : *games)
    total += g.count;
  return total;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> text;
  readFile("input.txt", &text);

  std::vector<game> games;

  parse_cards(&text, &games);

  uint32_t part1_res = part1(&games);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint32_t part2_res = part2(&games);
  std::cout << "Part 2 : " << part2_res << '\n';
}
