#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

void readFile(const std::string filename, std::vector<int> *left,
              std::vector<int> *right) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    auto idx = str.find_first_of(" ");
    left->push_back(std::stoi(str.substr(0, idx)));
    right->push_back(std::stoi(str.substr(idx + 1)));
  }
}

uint32_t part1(std::vector<int> left, std::vector<int> right) {
  int total = 0;

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  for (auto i = 0; i < left.size(); ++i) {
    total += abs(left.at(i) - right.at(i));
  }
  return total;
}

uint32_t part2(std::vector<int> left, std::vector<int> right) {
  int total = 0;
  for (auto i = 0; i < left.size(); ++i) {
    int count = std::count(right.cbegin(), right.cend(), left.at(i));
    total += left.at(i) * count;
  }
  return total;
}
int main(int argc, char *argv[]) {
  std::vector<int> left, right;
  readFile("input.txt", &left, &right);

  int part1_res = part1(left, right);
  std::cout << "Part 1 : " << part1_res << '\n';

  int part2_res = part2(left, right);
  std::cout << "Part 2 : " << part2_res << '\n';
}
