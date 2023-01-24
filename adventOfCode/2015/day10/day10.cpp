#include <iostream>
#include <string>

size_t firstChallenge(std::string s)
{
    std::string res;

    for (size_t i = 0; i < 40; ++i)
    {
        res = "";
        while (s.length())
        {
            size_t idx = s.find_first_not_of(s[0]);
            idx = std::min(idx, s.length());
            res += '0' + idx;
            res += s[0];
            s.erase(0, idx);
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
}