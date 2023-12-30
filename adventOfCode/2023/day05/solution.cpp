#include <cctype>
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

struct map {
  uint32_t to;
  uint32_t from;
  uint32_t range;
};

struct map_vector {
  std::vector<map> map_vector;

  uint32_t transform(uint32_t source) {
    for (auto &m : map_vector) {
      uint32_t offset = source - m.from;
      if (offset < m.range) {
        return m.to + offset;
      }
    }
    return source;
  }

  uint32_t reverse_transform(uint32_t source) {
    for (auto &m : map_vector) {
      uint32_t offset = source - m.to;
      if (offset < m.range) {
        return m.from + offset;
      }
    }
    return source;
  }
};

bool valid_seed(std::vector<uint32_t> *seeds, const uint32_t seed) {
  for (uint32_t i = 0; i < seeds->size(); i += 2) {
    if (seed >= seeds->at(i) && seed < (seeds->at(i) + seeds->at(i + 1)))
      return true;
  }
  return false;
};

void parse_maps(std::vector<std::string> *input, std::vector<map_vector> *maps,
                std::vector<uint32_t> *seeds) {
  std::smatch match;
  std::regex reg("[\\d]+");

  auto line = input->cbegin();

  auto seed_it = std::sregex_iterator(line->cbegin(), line->cend(), reg);
  auto seed_end = std::sregex_iterator();
  while (seed_it != seed_end) {
    seeds->push_back(std::stol(seed_it->str()));
    ++seed_it;
  }
  ++line;

  while (line != input->cend()) {
    if (line->length()) {
      if (std::isdigit(line->at(0))) {
        map tmp;
        auto num_it = std::sregex_iterator(line->cbegin(), line->cend(), reg);
        auto num_end = std::sregex_iterator();
        tmp.to = std::stol(num_it->str());
        ++num_it;
        tmp.from = std::stol(num_it->str());
        ++num_it;
        tmp.range = std::stol(num_it->str());
        maps->back().map_vector.push_back(tmp);
      }
    } else
      maps->push_back(map_vector());
    ++line;
  }
}

uint32_t part1(std::vector<map_vector> *maps, std::vector<uint32_t> *seeds) {

  uint32_t min_height = -1;

  for (auto &s : *seeds) {
    uint32_t height = s;
    uint32_t min_seed;
    for (auto &v1 : *maps) {
      height = v1.transform(height);
    }

    if (height < min_height) {
      min_height = height;
      min_seed = s;
    }
  }

  return min_height;
}

uint32_t part2(std::vector<map_vector> *maps, std::vector<uint32_t> *seeds) {
  uint32_t seed = 0;
  while (true) {
    uint32_t height = seed;
    auto v = maps->rbegin();
    while (v != maps->rend()) {
      height = v->reverse_transform(height);
      ++v;
    }

    if (valid_seed(seeds, height)) {
      return seed;
    }
    ++seed;
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> text;
  readFile("input.txt", &text);

  std::vector<map_vector> maps;
  std::vector<uint32_t> seeds;

  parse_maps(&text, &maps, &seeds);

  uint32_t part1_res = part1(&maps, &seeds);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint32_t part2_res = part2(&maps, &seeds);
  std::cout << "Part 2 : " << part2_res << '\n';
}
