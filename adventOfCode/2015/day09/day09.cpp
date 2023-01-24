#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
#include <unordered_map>

typedef std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>> map;

uint32_t min_dist = UINT32_MAX;

map Readfile()
{
    map res;

    std::ifstream file("input.txt");
    std::string from;
    std::string to;
    uint32_t distance;

    std::string s;
    while (std::getline(file, s))
    {
        uint32_t idx1 = s.find_first_of(' ');
        from = s.substr(0, idx1);
        uint32_t idx2 = s.find_first_of('=');
        to = s.substr(idx1 + 4, idx2 - idx1 - 5);
        distance = std::stoi(s.substr(idx2 + 1));

        res[from][to] = distance;
        res[to][from] = distance;
    }
    file.close();
    return res;
};

void NextRound(map s, uint32_t partial_distance, std::string from)
{
    s.erase(from);

    if (s.size() > 1)
        for (auto r : s)
            NextRound(s, partial_distance + s[r.first][from], r.first);
    else
        min_dist = std::min(partial_distance + s.begin()->second[from], min_dist);
};

uint32_t firstChallenge(map s)
{
    for (auto r : s)
    {
        NextRound(s, 0, r.first);
    }
    return min_dist;
};

int main()
{
    map inp = Readfile();

    uint32_t s1 = firstChallenge(inp);
    std::cout << s1 << std::endl;
}