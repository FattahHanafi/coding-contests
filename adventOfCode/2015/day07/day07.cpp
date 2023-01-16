#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <bitset>
#include <cstring>
#include <unordered_map>

enum instruction
{
    ASSIGN = 0,
    NOT,
    AND,
    OR,
    LSHIFT,
    RSHIFT
};

struct Command
{
    instruction instruct = ASSIGN;
    std::string rega;
    std::string regb;
    std::string regc;
};

std::list<Command> Readfile()
{
    std::list<Command> res;

    std::ifstream file("input.txt");
    std::string s;
    size_t idx;
    size_t idxa;

    while (std::getline(file, s))
    {
        Command c;
        idxa = s.find(" -> ");
        c.regc = s.substr(idxa + 4);
        s.erase(idxa);

        idx = s.find("NOT");
        if (idx != std::string::npos)
        {
            c.instruct = NOT;
            c.rega = s.substr(idx + 4);
        }

        idx = s.find("AND");
        if (idx != std::string::npos)
        {
            c.instruct = AND;
            c.rega = s.substr(0, idx - 1);
            c.regb = s.substr(idx + 4);
        }

        idx = s.find("OR");
        if (idx != std::string::npos)
        {
            c.instruct = OR;
            c.rega = s.substr(0, idx - 1);
            c.regb = s.substr(idx + 3);
        }

        idx = s.find("LSHIFT");
        if (idx != std::string::npos)
        {
            c.instruct = LSHIFT;
            c.rega = s.substr(0, idx - 1);
            c.regb = s.substr(idx + 7);
        }

        idx = s.find("RSHIFT");
        if (idx != std::string::npos)
        {
            c.instruct = RSHIFT;
            c.rega = s.substr(0, idx - 1);
            c.regb = s.substr(idx + 7);
        }

        if (c.instruct == ASSIGN)
        {
            c.rega = s;
        }

        res.push_back(c);
    }

    file.close();
    return res;
};

int32_t firstChallenge(std::list<Command> s)
{
    std::unordered_map<std::string, uint16_t> res;

    while (!s.empty())
    {
        for (auto it = s.begin(); it != s.end();)
        {
            switch (it->instruct)
            {
            case ASSIGN:
                if (res.find(it->rega) != res.end())
                {
                    res[it->regc] = res[it->rega];
                    it = s.erase(it);
                }
                else if (std::isdigit(it->rega[0]))
                {
                    res[it->regc] = std::stoi(it->rega);
                    it = s.erase(it);
                }
                break;

                case NOT:
                if (res.find(it->rega) != res.end())
                {
                    res[it->regc] = ~res[it->rega];
                    it = s.erase(it);
                }
                else if (std::isdigit(it->rega[0]))
                {
                    res[it->regc] = ~std::stoi(it->rega);
                    it = s.erase(it);
                }
                break;

                case LSHIFT:
                if (res.find(it->rega) != res.end())
                {
                    res[it->regc] = res[it->rega] << std::stoi(it->regb);
                    it = s.erase(it);
                }
                else if (std::isdigit(it->rega[0]))
                {
                    res[it->regc] = std::stoi(it->rega) << std::stoi(it->regb);
                    it = s.erase(it);
                }
                break;

                case RSHIFT:
                if (res.find(it->rega) != res.end())
                {
                    res[it->regc] = res[it->rega] >> std::stoi(it->regb);
                    it = s.erase(it);
                }
                else if (std::isdigit(it->rega[0]))
                {
                    res[it->regc] = std::stoi(it->rega) >> std::stoi(it->regb);
                    it = s.erase(it);
                }
                break;

                case AND:
                if (res.find(it->rega) != res.end())
                {
                    if (res.find(it->regb) != res.end())
                    {
                        res[it->regc] = res[it->rega] & res[it->regb];
                        it = s.erase(it);
                    }
                    else if (std::isdigit(it->regb[0]))
                    {
                        res[it->regc] = res[it->rega] & std::stoi(it->regb);
                        it = s.erase(it);
                    }
                }
                else if (std::isdigit(it->rega[0]))
                {
                    if (res.find(it->regb) != res.end())
                    {
                        res[it->regc] = std::stoi(it->rega) & res[it->regb];
                        it = s.erase(it);
                    }
                    else if (std::isdigit(it->regb[0]))
                    {
                        res[it->regc] = std::stoi(it->rega) & std::stoi(it->regb);
                        it = s.erase(it);
                    }
                }
                break;

                case OR:
                if (res.find(it->rega) != res.end())
                {
                    if (res.find(it->regb) != res.end())
                    {
                        res[it->regc] = res[it->rega] | res[it->regb];
                        it = s.erase(it);
                    }
                    else if (std::isdigit(it->regb[0]))
                    {
                        res[it->regc] = res[it->rega] | std::stoi(it->regb);
                        it = s.erase(it);
                    }
                }
                else if (std::isdigit(it->rega[0]))
                {
                    if (res.find(it->regb) != res.end())
                    {
                        res[it->regc] = std::stoi(it->rega) | res[it->regb];
                        it = s.erase(it);
                    }
                    else if (std::isdigit(it->regb[0]))
                    {
                        res[it->regc] = std::stoi(it->rega) | std::stoi(it->regb);
                        it = s.erase(it);
                    }
                }
                break;
            }

            ++it;
        }
    }

    return res["a"];
};

int32_t secondChallenge(std::list<Command> s)
{
    std::unordered_map<std::string, uint16_t> res;

    for(auto it = s.begin(); it != s.end(); ++it)
    {
        if(it->instruct == ASSIGN && it->regc == "b")
            it->rega = "956";
    }

    while (!s.empty())
    {
        for (auto it = s.begin(); it != s.end();)
        {
            switch (it->instruct)
            {
            case ASSIGN:
                if (res.find(it->rega) != res.end())
                {
                    res[it->regc] = res[it->rega];
                    it = s.erase(it);
                }
                else if (std::isdigit(it->rega[0]))
                {
                    res[it->regc] = std::stoi(it->rega);                     
                    it = s.erase(it);
                }
                break;

                case NOT:
                if (res.find(it->rega) != res.end())
                {
                    res[it->regc] = ~res[it->rega];
                    it = s.erase(it);
                }
                else if (std::isdigit(it->rega[0]))
                {
                    res[it->regc] = ~std::stoi(it->rega);
                    it = s.erase(it);
                }
                break;

                case LSHIFT:
                if (res.find(it->rega) != res.end())
                {
                    res[it->regc] = res[it->rega] << std::stoi(it->regb);
                    it = s.erase(it);
                }
                else if (std::isdigit(it->rega[0]))
                {
                    res[it->regc] = std::stoi(it->rega) << std::stoi(it->regb);
                    it = s.erase(it);
                }
                break;

                case RSHIFT:
                if (res.find(it->rega) != res.end())
                {
                    res[it->regc] = res[it->rega] >> std::stoi(it->regb);
                    it = s.erase(it);
                }
                else if (std::isdigit(it->rega[0]))
                {
                    res[it->regc] = std::stoi(it->rega) >> std::stoi(it->regb);
                    it = s.erase(it);
                }
                break;

                case AND:
                if (res.find(it->rega) != res.end())
                {
                    if (res.find(it->regb) != res.end())
                    {
                        res[it->regc] = res[it->rega] & res[it->regb];
                        it = s.erase(it);
                    }
                    else if (std::isdigit(it->regb[0]))
                    {
                        res[it->regc] = res[it->rega] & std::stoi(it->regb);
                        it = s.erase(it);
                    }
                }
                else if (std::isdigit(it->rega[0]))
                {
                    if (res.find(it->regb) != res.end())
                    {
                        res[it->regc] = std::stoi(it->rega) & res[it->regb];
                        it = s.erase(it);
                    }
                    else if (std::isdigit(it->regb[0]))
                    {
                        res[it->regc] = std::stoi(it->rega) & std::stoi(it->regb);
                        it = s.erase(it);
                    }
                }
                break;

                case OR:
                if (res.find(it->rega) != res.end())
                {
                    if (res.find(it->regb) != res.end())
                    {
                        res[it->regc] = res[it->rega] | res[it->regb];
                        it = s.erase(it);
                    }
                    else if (std::isdigit(it->regb[0]))
                    {
                        res[it->regc] = res[it->rega] | std::stoi(it->regb);
                        it = s.erase(it);
                    }
                }
                else if (std::isdigit(it->rega[0]))
                {
                    if (res.find(it->regb) != res.end())
                    {
                        res[it->regc] = std::stoi(it->rega) | res[it->regb];
                        it = s.erase(it);
                    }
                    else if (std::isdigit(it->regb[0]))
                    {
                        res[it->regc] = std::stoi(it->rega) | std::stoi(it->regb);
                        it = s.erase(it);
                    }
                }
                break;
            }

            ++it;
        }
    }

    return res["a"];
};

int main()
{
    std::list<Command> inp = Readfile();

    int32_t s1 = firstChallenge(inp);
    std::cout << s1 << std::endl;

    int32_t s2 = secondChallenge(inp);
    std::cout << s2 << std::endl;

    return 0;
}