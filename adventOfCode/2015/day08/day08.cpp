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
        m_count += r.size() - 2;
        
        for(uint32_t i = 0; i < r.size(); ++i)
        if(r[i] == '\\')
        {
            if (r[i + 1] == '\\')
            {
                i += 1;
                m_count -= 1;
            }
            else if (r[i + 1] == '"')
            {
                i += 1;
                m_count -= 1;
            }
            else if (r[i + 1] == 'x')
            {
                i += 3;
                m_count -= 3;
            }
        }
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