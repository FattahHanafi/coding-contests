#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <bitset>

#define LENGTH 1000

enum instruction
{
    OFF = 0,
    ON,
    TOGGLE,
};

struct Command
{
    instruction instruct;
    size_t xs;
    size_t ys;
    size_t xe;
    size_t ye;
};

std::list<Command> Readfile()
{
    std::list<Command> res;

    std::ifstream file("input.txt");
    std::string s;

    while (std::getline(file, s))
    {
        Command c;
        if (s[1] == 'o')
        {
            c.instruct = TOGGLE;
        }
        else
        {
            c.instruct = (s[6] == 'n') ? ON : OFF;
        }

        switch (c.instruct)
        {
        case ON:
            s.erase(0, 8);
            break;
        case OFF:
            s.erase(0, 9);
            break;
        case TOGGLE:
            s.erase(0, 7);
            break;
        }

        size_t idx = s.find_first_of(',');
        c.xs = std::stoi(s.substr(0, idx));
        s.erase(0, idx + 1);
        idx = s.find_first_of(' ');
        c.ys = std::stoi(s.substr(0, idx));
        s.erase(0, idx + 1);
        s.erase(0, 8);
        idx = s.find_first_of(',');
        c.xe = std::stoi(s.substr(0, idx));
        s.erase(0, idx + 1);
        idx = s.find_first_of(' ');
        c.ye = std::stoi(s.substr(0, idx));
        res.push_back(c);
    }

    file.close();
    return res;
};

int32_t firstChallenge(std::list<Command> s)
{
    std::vector<std::bitset<LENGTH>> res;
    res.resize(LENGTH);

    for (auto r : s)
    {
        switch (r.instruct)
        {
        case ON:
            for (size_t j = r.ys; j <= r.ye; ++j)
                for (size_t i = r.xs; i <= r.xe; ++i)
                    res[j].set(i);
            break;
        case OFF:
            for (size_t j = r.ys; j <= r.ye; ++j)
                for (size_t i = r.xs; i <= r.xe; ++i)
                    res[j].reset(i);
            break;
        case TOGGLE:
            for (size_t j = r.ys; j <= r.ye; ++j)
                for (size_t i = r.xs; i <= r.xe; ++i)
                    res[j].flip(i);
            break;

        default:
            break;
        }
    }
    size_t count = 0;
    for (size_t i = 0; i < LENGTH; ++i)
        count += res[i].count();

    return count;
};

int main()
{
    std::list<Command> inp = Readfile();

    int32_t s1 = firstChallenge(inp);
    std::cout << s1 << std::endl;

    return 0;
}