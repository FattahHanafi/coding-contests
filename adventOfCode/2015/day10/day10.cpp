#include <iostream>
#include <string>
#include <chrono>

size_t firstChallenge(std::string s)
{
    std::string res;

    for (size_t i = 0; i < 40; ++i)
    {
        size_t idx1 = 0;
        size_t idx2 = 0;
        res = "";
        const size_t len = s.size();

        while (idx2 < len)
        {
            idx2 = s.find_first_not_of(s[idx1], idx1);
            idx2 = std::min(idx2, len);
            res += '0' + (idx2 - idx1);
            res += s[idx1];
            idx1 = idx2;
        }
        s = res;
    }

    return res.length();
};

size_t secondChallenge(std::string s)
{
    std::string res;

    for (size_t i = 0; i < 50; ++i)
    {
        size_t idx1 = 0;
        size_t idx2 = 0;
        res = "";
        const size_t len = s.size();

        while (idx2 < len)
        {
            idx2 = s.find_first_not_of(s[idx1], idx1);
            idx2 = std::min(idx2, len);
            res += '0' + (idx2 - idx1);
            res += s[idx1];
            idx1 = idx2;
        }
        s = res;
    }

    return res.length();
};

int main()
{
    std::string inp = "3113322113";

    size_t s1 = firstChallenge(inp);
    std::cout << s1 << std::endl;

    size_t s2 = secondChallenge(inp);
    std::cout << s2 << std::endl;
}