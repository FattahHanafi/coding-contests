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
#include <sstream>
#include <string.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

void readFile(const std::string filename,
              std::vector<std::vector<uint64_t>> *values,
              std::vector<char> *operation) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    std::stringstream ss(str);
    if (str.find('*') == std::string::npos) {
      values->emplace_back(
          std::vector<uint64_t>(std::istream_iterator<uint64_t>(ss),
                                std::istream_iterator<uint64_t>()));
    } else {
      for (const auto &c : str) {
        if (c != ' ')
          operation->emplace_back(c);
      }
    }
  }
}

void readFile2(const std::string filename,
               std::vector<std::vector<uint64_t>> *values,
               std::vector<char> *operation) {
  std::ifstream file(filename);
  std::string str;
  std::vector<std::string> str_vec;

  while (std::getline(file, str)) {
    str_vec.emplace_back(str);
  }

  auto op = str_vec.back();
  auto left_it = op.find_first_not_of(' ');
  while (left_it < op.length()) {
    auto right_it = op.find_first_not_of(' ', left_it + 1);
    // right_it = std::min(right_it, op.length());
    std::vector<std::string> val_str;
    for (auto it = left_it; it < right_it; ++it) {
      val_str.push_back(str_vec.at(0).at(it));
      // val_str.at(it - left_it) += str_vec.at(0).at(it);
      // val_str.at(it - left_it) += std::to_string(str_vec.at(1).at(it));
      // val_str.at(it - left_it) += std::to_string(str_vec.at(2).at(it));
      // val_str.at(it - left_it) += str_vec.at(3).at(it);
      std::cout << val_str.at(it - left_it) << std::endl;
    }
    if (op.at(left_it) == '*') {
    }
    left_it = right_it;
  }
}

// auto val = str_vec.cbegin();
// auto end_val = str_vec.cend();
// --end_val;
// std::vector<uint64_t> vals;
// for (size_t i = left_it; i <= right_it; ++i) {
//   vals.emplace_back(val->at(i) == ' ' ? 0 : val->at(i) - '0');
//   ++val;
//   while (val != end_val) {
//     vals.at(i) *= 10;
//     vals.at(i) += val->at(i) == ' ' ? 0 : val->at(i) - '0';
//   }
// }
// if (op.at(left_it) == '+') {
// } else if (op.at(left_it) == '*') {
// } else {
//   std::cout << "Invalid\n";
// }
// }

// uint64_t part1(const std::vector<std::vector<uint64_t>> &values,
//                const std::vector<char> &operation) {
//   uint64_t total = 0;
//
//   for (size_t i = 0; i < operation.size(); ++i) {
//     uint64_t cur_total;
//     if (operation.at(i) == '+') {
//       cur_total = 0;
//       for (const auto &row : values) {
//         cur_total += row.at(i);
//       }
//     } else if (operation.at(i) == '*') {
//       cur_total = 1;
//       for (const auto &row : values) {
//         cur_total *= row.at(i);
//       }
//     } else {
//       std::cout << "invalid (" << operation.at(i) << ")\n";
//     }
//     total += cur_total;
//   }
//   return total;
// }

// uint64_t part2(const std::vector<std::pair<uint64_t, uint64_t>> &ranges) {
//   std::vector<std::pair<uint64_t, uint64_t>> old_ranges;
//   std::vector<std::pair<uint64_t, uint64_t>> new_ranges;
//   old_ranges = ranges;
//
//   uint64_t total = 0;
//   bool modified = false;
//   do {
//     modified = false;
//     for (const auto &range : old_ranges) {
//       bool added = false;
//       for (auto &row : new_ranges) {
//         if (range.first <= row.first && range.second >= row.first) {
//           row.first = range.first;
//           added = true;
//           modified = true;
//         }
//         if (range.second >= row.second && range.first <= row.second) {
//           row.second = range.second;
//           added = true;
//           modified = true;
//         }
//         if (range.first >= row.first && range.second <= row.second) {
//           added = true;
//         }
//       }
//       if (!added) {
//         new_ranges.emplace_back(range);
//       }
//     }
//
//     old_ranges = new_ranges;
//     new_ranges.clear();
//
//   } while (modified);
//
//   for (const auto &row : old_ranges) {
//     total += (row.second - row.first) + 1;
//   }
//   return total;
// }

int main(int argc, char *argv[]) {
  std::vector<std::vector<uint64_t>> values;
  std::vector<char> operation;
  readFile2("input.txt", &values, &operation);

  // uint64_t part1_res = part1(values, operation);
  // std::cout << "Part 1 : " << part1_res << '\n';

  // readFile("input.txt");
  // uint64_t part2_res = part2(ranges);
  // std::cout << "Part 2 : " << part2_res << '\n';
}
