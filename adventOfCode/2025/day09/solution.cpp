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

struct Point {
  Point(uint64_t _x, uint64_t _y) : x(_x), y(_y) {}
  uint64_t x, y;

  uint64_t area(const Point *p) {
    uint64_t dx = std::max(this->x, p->x) - std::min(this->x, p->x);
    uint64_t dy = std::max(this->y, p->y) - std::min(this->y, p->y);

    return (dx + 1) * (dy + 1);
  }
};

void readFile(const std::string filename, std::vector<Point> *values) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    auto first = str.find_first_of(',');
    uint64_t x = std::stoll(str.substr(0, first));
    uint64_t y = std::stoll(str.substr(first + 1));
    values->emplace_back(Point(x, y));
  }
}

int64_t part1(std::vector<Point> &values) {
  uint64_t total = 0;

  for (size_t i = 0; i < values.size() - 1; ++i) {
    for (size_t j = i + 1; j < values.size(); ++j) {
      total = std::max(total, values.at(i).area(&values.at(j)));
    }
  }

  return total;
}

int64_t part2(const std::vector<Point> &values) {
  uint64_t total;
  return total;
}

int main(int argc, char *argv[]) {
  std::vector<Point> values;
  readFile("input.txt", &values);

  uint64_t part1_res = part1(values);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint64_t part2_res = part2(values);
  std::cout << "Part 2 : " << part2_res << '\n';
}
