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
  Point(int64_t _x, int64_t _y, int64_t _z) : x(_x), y(_y), z(_z) {}
  int64_t x, y, z;
  int64_t dis(const Point &P) const {
    const int64_t dx = P.x - this->x;
    const int64_t dy = P.y - this->y;
    const int64_t dz = P.z - this->z;
    return dx * dx + dy * dy + dz * dz;
  }

  void print() const { std::cout << x << ' ' << y << ' ' << z << std::endl; }
};

struct PointPair {
  PointPair(size_t i, size_t j, int64_t dis) {
    this->A = std::min(i, j);
    this->B = std::max(i, j);
    this->dis = dis;
  }

  friend bool operator<(const PointPair &lhs, const PointPair &rhs) {
    return lhs.dis < rhs.dis;
  }
  size_t A;
  size_t B;
  int64_t dis;
};

void readFile(const std::string filename, std::vector<Point> *values) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    auto first = str.find_first_of(',');
    auto second = str.find_last_of(',');
    int64_t x = std::stoll(str.substr(0, first));
    int64_t y = std::stoll(str.substr(first + 1, second));
    int64_t z = std::stoll(str.substr(second + 1));
    values->emplace_back(Point(x, y, z));
  }
}

int64_t part1(const std::vector<Point> &values) {
  int64_t total = 1;
  const size_t M = 1000;
  const size_t K = 3;
  const size_t N = values.size();
  std::vector<PointPair> point_pairs;
  std::vector<size_t> circ;
  for (auto i = 0; i < N; ++i) {
    circ.emplace_back(i);
  }

  for (size_t i = 0; i < N - 1; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      auto dis = values.at(i).dis(values.at(j));
      point_pairs.emplace_back(PointPair(i, j, dis));
    }
  }

  std::sort(point_pairs.begin(), point_pairs.end());

  for (size_t i = 0; i < M; ++i) {
    auto pp = point_pairs.at(i);
    auto cc_to = circ.at(pp.A);
    auto cc_fr = circ.at(pp.B);
    for (auto &c : circ) {
      if (c == cc_fr) {
        c = circ.at(pp.A);
      }
    }
  }
  std::vector<uint64_t> counts;
  counts.resize(N);
  for (auto v : circ) {
    ++counts[v];
  }

  std::sort(counts.begin(), counts.end(), std::greater<size_t>());
  for (auto i = 0; i < K; ++i) {
    total *= counts[i];
  }

  return total;
}

int64_t part2(const std::vector<Point> &values) {
  int64_t total;
  const size_t N = values.size();
  std::vector<PointPair> point_pairs;
  std::vector<size_t> circ;
  for (auto i = 0; i < N; ++i) {
    circ.emplace_back(i);
  }

  for (size_t i = 0; i < N - 1; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      auto dis = values.at(i).dis(values.at(j));
      point_pairs.emplace_back(PointPair(i, j, dis));
    }
  }

  std::sort(point_pairs.begin(), point_pairs.end());

  size_t i = 0;
  size_t seperate = N;

  while (seperate > 1) {

    auto pp = point_pairs.at(i);
    auto cc_to = circ.at(pp.A);
    auto cc_fr = circ.at(pp.B);
    for (auto &c : circ) {
      if (c == cc_fr) {
        c = circ.at(pp.A);
      }
    }
    std::unordered_set<size_t> sets;
    for (auto c : circ) {
      sets.insert(c);
    }
    seperate = sets.size();
    ++i;
  }

  int64_t xA = values.at(point_pairs.at(i - 1).A).x;
  int64_t xB = values.at(point_pairs.at(i - 1).B).x;

  return xA * xB;
}

int main(int argc, char *argv[]) {
  std::vector<Point> values;
  readFile("input.txt", &values);

  uint64_t part1_res = part1(values);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint64_t part2_res = part2(values);
  std::cout << "Part 2 : " << part2_res << '\n';
}
