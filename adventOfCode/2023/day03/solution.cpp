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

uint32_t part1(std::vector<std::string> *input) {
  const std::string numbers = ".0123456789";
  std::set<char> symbols;
  for (const auto &line : *input) {
    for (char c : line) {
      if (numbers.find_first_of(c) == std::string::npos) {
        symbols.insert(c);
      }
    }
  }

  std::string syms = "";
  for (auto c : symbols)
    syms = syms + c;

  uint32_t total = 0;
  std::smatch match;
  std::regex reg("[\\d]+");

  for (size_t i = 0; i < input->size(); ++i) {
    std::string line = input->at(i);
    auto num_it = std::sregex_iterator(line.cbegin(), line.cend(), reg);
    auto games_end = std::sregex_iterator();
    while (num_it != games_end) {
      size_t idx_0 =
          line.length() - num_it->suffix().length() - num_it->length();
      size_t idx_1 = line.length() - num_it->suffix().length();
      if (idx_0 != 0)
        idx_0--;
      idx_1 = std::min(idx_1 + 1, line.length());

      std::string region = line.substr(idx_0, idx_1 - idx_0);

      if (i != 0)
        region += input->at(i - 1).substr(idx_0, idx_1 - idx_0);

      if (i != input->size() - 1)
        region += input->at(i + 1).substr(idx_0, idx_1 - idx_0);

      if (region.find_first_of(syms) != std::string::npos)
        total += std::stoi(num_it->str());
      num_it++;
    }
  }
  return total;
}

struct gear {
  uint32_t nums;
  std::vector<uint32_t> x;
  std::vector<uint32_t> y;
  bool counted = false;
};

uint32_t part2(std::vector<std::string> *input) {
  const std::string numbers = ".0123456789";
  std::vector<gear> gears;
  std::set<char> symbols;
  for (const auto &line : *input) {
    for (char c : line) {
      if (numbers.find_first_of(c) == std::string::npos) {
        symbols.insert(c);
      }
    }
  }

  std::string syms = "*";

  uint32_t total = 0;
  std::smatch match;
  std::regex reg("[\\d]+");

  for (size_t i = 0; i < input->size(); ++i) {
    std::string line = input->at(i);
    auto num_it = std::sregex_iterator(line.cbegin(), line.cend(), reg);
    auto games_end = std::sregex_iterator();
    while (num_it != games_end) {
      size_t idx_0 =
          line.length() - num_it->suffix().length() - num_it->length();
      size_t idx_1 = line.length() - num_it->suffix().length();
      if (idx_0 != 0)
        idx_0--;
      idx_1 = std::min(idx_1 + 1, line.length());

      gear tmp;
      tmp.nums = std::stoi(num_it->str());

      std::string region = line.substr(idx_0, idx_1 - idx_0);
      for (uint32_t j = 0; j < region.length(); ++j) {
        if (region[j] == '*') {
          tmp.x.push_back(idx_0 + j);
          tmp.y.push_back(i);
        }
      }

      if (i != 0) {
        region = input->at(i - 1).substr(idx_0, idx_1 - idx_0);
        for (uint32_t j = 0; j < region.length(); ++j) {
          if (region[j] == '*') {
            tmp.x.push_back(idx_0 + j);
            tmp.y.push_back(i - 1);
          }
        }
      }

      if (i != input->size() - 1) {
        region = input->at(i + 1).substr(idx_0, idx_1 - idx_0);
        for (uint32_t j = 0; j < region.length(); ++j) {
          if (region[j] == '*') {
            tmp.x.push_back(idx_0 + j);
            tmp.y.push_back(i + 1);
          }
        }
      }
      if (tmp.x.size())
        gears.push_back(tmp);
      num_it++;
    }
  }

  auto g1 = gears.begin();

  while (g1 != gears.end()) {
    auto g2 = gears.begin();
    while (g2 != gears.end()) {
      if (g1 != g2 && !g1->counted && !g2->counted &&
          g1->x.at(0) == g2->x.at(0) && g1->y.at(0) == g2->y.at(0)) {
        total += g1->nums * g2->nums;
        g1->counted = true;
        g2->counted = true;
      }
      ++g2;
    }
    ++g1;
  }

  return total;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> text;
  readFile("input.txt", &text);

  uint32_t part1_res = part1(&text);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint32_t part2_res = part2(&text);
  std::cout << "Part 2 : " << part2_res << '\n';
}
