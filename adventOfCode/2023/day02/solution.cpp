#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string.h>
#include <string>
#include <vector>

void readFile(const std::string filename, std::vector<std::string> *input) {
  std::ifstream file(filename);
  std::string str;
  while (std::getline(file, str)) {
    input->push_back(str);
  }
}

struct game {
  uint32_t id;
  std::vector<uint32_t> m_red = {0};
  std::vector<uint32_t> m_green = {0};
  std::vector<uint32_t> m_blue = {0};
};

void parse_games(const std::vector<std::string> *input,
                 std::vector<game> *games) {
  std::smatch r_match;
  std::smatch g_match;
  std::smatch b_match;
  std::regex game_reg("[\\d\\w ,]+[;\\n]?");
  std::regex r_reg("[0-9]+ red");
  std::regex g_reg("[0-9]+ green");
  std::regex b_reg("[0-9]+ blue");

  for (auto &line : *input) {
    game tmp;
    size_t idx_0 = line.find(" ");
    size_t idx_1 = line.find(":");
    tmp.id = std::stoi(line.substr(idx_0, idx_1 - idx_0));
    auto game_str = line.substr(idx_1 + 1, line.length());

    auto games_begin =
        std::sregex_iterator(game_str.cbegin(), game_str.cend(), game_reg);
    auto games_end = std::sregex_iterator();
    for (std::sregex_iterator i = games_begin; i != games_end; ++i) {
      const std::string ss = i->str().c_str();
      std::regex_search(ss, r_match, r_reg);
      std::regex_search(ss, g_match, g_reg);
      std::regex_search(ss, b_match, b_reg);
      if (r_match.size()) {
        auto num_str = r_match.str().substr(0, r_match.str().find('r') - 1);
        tmp.m_red.push_back(std::stoi(num_str));
      }
      if (g_match.size()) {
        auto num_str = g_match.str().substr(0, g_match.str().find('g') - 1);
        tmp.m_green.push_back(std::stoi(num_str));
      }
      if (b_match.size()) {
        auto num_str = b_match.str().substr(0, b_match.str().find('b') - 1);
        tmp.m_blue.push_back(std::stoi(num_str));
      }
    }
    games->push_back(tmp);
  }
}

uint32_t part1(std::vector<game> *games) {
  uint32_t total = 0;
  for (const auto &game : *games) {
    uint32_t max_r = *std::max_element(game.m_red.cbegin(), game.m_red.cend());
    uint32_t max_g =
        *std::max_element(game.m_green.cbegin(), game.m_green.cend());
    uint32_t max_b =
        *std::max_element(game.m_blue.cbegin(), game.m_blue.cend());
    if ((max_r <= 12) && (max_g <= 13) && (max_b <= 14))
      total += game.id;
  }
  return total;
}

uint32_t part2(std::vector<game> *games) {
  uint32_t total = 0;
  for (const auto &game : *games) {
    uint32_t max_r = *std::max_element(game.m_red.cbegin(), game.m_red.cend());
    uint32_t max_g =
        *std::max_element(game.m_green.cbegin(), game.m_green.cend());
    uint32_t max_b =
        *std::max_element(game.m_blue.cbegin(), game.m_blue.cend());
    uint32_t power = max_r * max_g * max_b;
    total += power;
  }
  return total;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> text;
  readFile("input.txt", &text);

  std::vector<game> games;
  parse_games(&text, &games);

  uint32_t part1_res = part1(&games);
  std::cout << "Part 1 : " << part1_res << '\n';

  uint32_t part2_res = part2(&games);
  std::cout << "Part 2 : " << part2_res << '\n';
}
