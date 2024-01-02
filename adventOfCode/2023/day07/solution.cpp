#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
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

enum class Hand_Type {
  FIVE_OF_A_KIND = 7,
  FOUR_OF_A_KIND = 6,
  FULL_HOUSE = 5,
  THREE_OF_A_KIND = 4,
  TWO_PAIR = 3,
  ONE_PAIR = 2,
  HIGH_CARD = 1,
};

struct hand {
  uint32_t bet;
  std::array<uint8_t, 13> num_cards = {0};
  Hand_Type hand_type = Hand_Type::HIGH_CARD;
  std::array<uint8_t, 5> cards;

  friend bool operator<(const hand &a, const hand &b) {
    if (a.hand_type > b.hand_type)
      return true;
    if (a.hand_type < b.hand_type)
      return false;
    for (uint8_t i = 0; i < a.cards.size(); ++i) {
      if (a.cards.at(i) > b.cards.at(i))
        return true;
      if (a.cards.at(i) < b.cards.at(i))
        return false;
    }
    printf("Error\n");
    return false;
  }

  void determine_type() {
    uint8_t five_pairs = 0;
    uint8_t four_pairs = 0;
    uint8_t three_pairs = 0;
    uint8_t two_pairs = 0;

    for (auto &c : num_cards)
      if (c == 5)
        ++five_pairs;
      else if (c == 4)
        ++four_pairs;
      else if (c == 3)
        ++three_pairs;
      else if (c == 2)
        ++two_pairs;

    if (five_pairs)
      hand_type = Hand_Type::FIVE_OF_A_KIND;
    else if (four_pairs)
      hand_type = Hand_Type::FOUR_OF_A_KIND;
    else if (three_pairs && two_pairs)
      hand_type = Hand_Type::FULL_HOUSE;
    else if (three_pairs)
      hand_type = Hand_Type::THREE_OF_A_KIND;
    else if (two_pairs > 1)
      hand_type = Hand_Type::TWO_PAIR;
    else if (two_pairs)
      hand_type = Hand_Type::ONE_PAIR;
  }
};

struct game {
  std::array<hand, 5> games;
  uint32_t total = 0;

  void calc_total() {
    uint8_t i = 5;
    for (auto &h : games) {
      total += i * h.bet;
      --i;
    }
  }
};

void parse_games(std::vector<std::string> *input, std::vector<game> *games) {
  auto line = input->cbegin();
  while (line != input->cend()) {
    game tmp;
    for (uint32_t i = 0; i < 5; ++i) {
      for (uint32_t j = 0; j < 5; ++j) {
        switch (line->at(j)) {
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          tmp.games.at(i).cards.at(j) = line->at(j) - '2';
          tmp.games.at(i).num_cards.at(line->at(j) - '2') += 1;
          break;
        case 'T':
          tmp.games.at(i).cards.at(j) = 8;
          tmp.games.at(i).num_cards.at(8) += 1;
          break;
        case 'J':
          tmp.games.at(i).cards.at(j) = 9;
          tmp.games.at(i).num_cards.at(9) += 1;
          break;
        case 'Q':
          tmp.games.at(i).cards.at(j) = 10;
          tmp.games.at(i).num_cards.at(10) += 1;
          break;
        case 'K':
          tmp.games.at(i).cards.at(j) = 11;
          tmp.games.at(i).num_cards.at(11) += 1;
          break;
        case 'A':
          tmp.games.at(i).cards.at(j) = 12;
          tmp.games.at(i).num_cards.at(12) += 1;
          break;
        }
      }

      std::sort(tmp.games.at(i).cards.begin(), tmp.games.at(i).cards.end(),
                std::greater<uint8_t>());
      tmp.games.at(i).determine_type();
      tmp.games.at(i).bet = std::stoi(line->substr(5, line->length() - 5));
      ++line;
    }
    games->push_back(tmp);
  }
}

uint32_t part1(std::vector<game> *games) {
  uint32_t total = 0;
  for (auto &g : *games) {
    printf("\n-------\n");
    std::sort(g.games.begin(), g.games.end());
    for (auto &q1 : g.games) {
      printf("%d - %d\n", static_cast<int>(q1.hand_type), q1.bet);
    }
    g.calc_total();
    total += g.total;
    printf("%d\n", g.total);
  }

  return total;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> text;
  readFile("input.txt", &text);

  std::vector<game> games;
  parse_games(&text, &games);

  uint64_t part1_res = part1(&games);
  std::cout << "Part 1 : " << part1_res << '\n';
}
