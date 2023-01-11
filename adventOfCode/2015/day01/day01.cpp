#include <iostream>
#include <fstream>
#include <string>

std::string Readfile()
{
    std::fstream file;
    file.open("input1.txt", std::ios::in);
    std::string s;
    std::getline(file, s);
    file.close();
    return s;
};

int32_t firstChalleng(std::string s)
{
    int32_t f = 0;
    for (char c : s)
    {
        if(c == '(')
            ++f;
        else
            --f;
    }
    return f;
};

int32_t secondChallenge(std::string s)
{
    int32_t f = 0;
    int32_t idx = 1;
    for (char c : s)
    {
        if(c == '(')
            ++f;
        else
            --f;
        if(f == -1)
            return idx;
        ++idx;
    }
    return 0;
};

int main()
{
    std::string s;
    s = Readfile();
    int32_t s1 = firstChalleng(s);
    std::cout << s1 << std::endl;

    int32_t s2 = secondChallenge(s);
    std::cout << s2 << std::endl;
    
    return 0;
}