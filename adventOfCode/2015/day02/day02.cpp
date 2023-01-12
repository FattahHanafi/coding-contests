#include <iostream>
#include <fstream>
#include <list>
#include <vector>

std::list<std::vector<int32_t>> Readfile()
{
    std::list<std::vector<int32_t>> res;

    std::ifstream file("input.txt");
    std::string s;
    std::string delimiter = "x\n";

    while (std::getline(file, s))
    {
        if (s.length() > 1)
        {
            std::vector<int32_t> tmp;
            uint32_t pos;
            std::string token;
            for (uint32_t i = 0; i < 3; ++i)
            {
                pos = s.find_first_of(delimiter);
                token = s.substr(0, pos);
                tmp.push_back(std::stoi(token));
                s.erase(0, pos + 1);
            }
            if (tmp[0] > tmp[1])
                std::swap(tmp[0], tmp[1]);
            if (tmp[1] > tmp[2])
                std::swap(tmp[1], tmp[2]);
            res.push_back(tmp);
        }
    }

    file.close();
    return res;
};

int32_t firstChalleng(std::list<std::vector<int32_t>> s)
{
    uint32_t total_area = 0;
    for (auto row : s)
        total_area += 3 * (row[0] * row[1]) + 2 * (row[1] * row[2] + row[0] * row[2]);
    return total_area;
};

int main()
{

    std::list<std::vector<int32_t>> inp = Readfile();

    int32_t s1 = firstChalleng(inp);
    std::cout << s1 << std::endl;

    return 0;
}