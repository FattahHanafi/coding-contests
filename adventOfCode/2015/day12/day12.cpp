#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::vector<int32_t> Readfile() {
  std::vector<int32_t> res;

  std::ifstream file("input.txt");
  std::string s;
  std::regex reg("[-]?[0-9]+");

  while (std::getline(file, s)) {

    auto numbers_beign = std::sregex_iterator(s.begin(), s.end(), reg);
    auto numbers_end = std::sregex_iterator();

    for (std::sregex_iterator i = numbers_beign; i != numbers_end; ++i) {
      std::smatch match = *i;
      std::string match_str = match.str();
      res.push_back(std::stoi(match_str));
    }
  }

  file.close();
  return res;
};

int32_t firstChallenge(std::vector<int32_t> s) {
  int32_t res = 0;
  for (auto n : s)
    res += n;

  return res;
};

int main() {
  std::vector<int32_t> inp = Readfile();

  int32_t s1 = firstChallenge(inp);
  std::cout << s1 << std::endl;

  return 0;
}
