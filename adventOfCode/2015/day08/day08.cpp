#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cstring>

std::list<std::string> Readfile()
{
    std::list<std::string> res;

    std::ifstream file("input.txt");
    std::string s;

    while (std::getline(file, s))
    {
        res.push_back(s);
    }

    file.close();
    return res;
};

int32_t firstChallenge(std::list<std::string> s)
{
    int32_t s_count = 0;
    int32_t m_count = 0;

    for (auto &r : s)
    {
        s_count += r.size();
        size_t idx = r.find_first_of('\\');
        while (idx != std::string::npos)
        {
            if (r[idx + 1] == '\\')
            {
                r.erase(idx + 1, 1);
                r[idx] = '_';
            }
            else if (r[idx + 1] == '"')
            {
                r.erase(idx + 1, 1);
                r[idx] = '_';
            }
            else if (r[idx + 1] == 'x')
            {
                r.erase(idx + 1, 3);
                r[idx] = '_';
            }
            idx = r.find_first_of('\\');
        }
        m_count += r.size() - 2;
    }

    return s_count - m_count;
};

int main()
{
    std::list<std::string> inp = Readfile();

    int32_t s1 = firstChallenge(inp);
    std::cout << s1 << std::endl;

    return 0;
}