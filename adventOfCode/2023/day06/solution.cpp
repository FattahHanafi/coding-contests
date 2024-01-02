#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

void readFile(const std::string filename, std::vector<std::string> *input) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    input->push_back(str);
  }
}

struct race {
  uint64_t time = 0;
  uint64_t beat_distance = 0;
  uint64_t min_hold = 0;
  uint64_t max_hold = 0;

  inline uint64_t distance(const uint64_t hold_time) {
    return hold_time * (time - hold_time);
  }

  void calc_min() {
    uint64_t hold_time = 0;
    while (true) {
      if (distance(hold_time) > beat_distance) {
        min_hold = hold_time;
        return;
      }
      ++hold_time;
    }
  }

  void calc_max() {
    uint64_t hold_time = time;
    while (true) {
      if (distance(hold_time) > beat_distance) {
        max_hold = hold_time;
        return;
      }
      --hold_time;
    }
  }
};

void parse_races(std::vector<std::string> *input, std::vector<race> *races) {
  std::smatch match;
  std::regex reg("[\\d]+");

  auto time_str = input->at(0);
  auto dist_str = input->at(1);

  auto time_it = std::sregex_iterator(time_str.cbegin(), time_str.cend(), reg);
  auto time_end = std::sregex_iterator();
  auto dist_it = std::sregex_iterator(dist_str.cbegin(), dist_str.cend(), reg);
  auto dist_end = std::sregex_iterator();
  while (time_it != time_end) {
    race tmp;
    tmp.time = std::stol(time_it->str());
    tmp.beat_distance = std::stol(dist_it->str());
    races->push_back(tmp);
    ++time_it;
    ++dist_it;
  }
}

uint64_t part1(std::vector<race> *races) {
  uint64_t comnibnations = 1;
  for (auto &r : *races) {
    r.calc_min();
    r.calc_max();
    comnibnations *= (1 + r.max_hold - r.min_hold);
  }
  return comnibnations;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> text;
  readFile("input.txt", &text);

  std::vector<race> races;
  parse_races(&text, &races);

  uint64_t part1_res = part1(&races);
  std::cout << "Part 1 : " << part1_res << '\n';

  for (auto &l : text) {
    while (l.find(' ') != std::string::npos)
      l.replace(l.find(' '), 1, "");
  }
  std::vector<race> races2;
  parse_races(&text, &races2);

  uint64_t part2_res = part1(&races2);
  std::cout << "Part 2 : " << part2_res << '\n';
}
