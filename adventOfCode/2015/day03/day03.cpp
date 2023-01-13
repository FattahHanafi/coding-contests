#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::string Readfile()
{
    std::fstream file;
    file.open("input.txt", std::ios::in);
    std::string s;
    std::getline(file, s);
    file.close();
    return s;
};

int32_t firstChallenge(std::string s)
{
    std::unordered_map<std::string, uint32_t> res;
    res.clear();

    int32_t x = 0;
    int32_t y = 0;
    
    std::string tmp = std::to_string(x) + "_" + std::to_string(y);
    res[tmp] == 0;
    
    for (char c : s)
    {
        switch (c)
        {
            case '>':
            ++x;
            break;
            case '<':
            --x;
            break;
            case '^':
            ++y;
            break;
            case 'v':
            --y;
            break;
        }
        tmp = std::to_string(x) + "_" + std::to_string(y);
        res[tmp] == 0;
    }

    uint32_t count = 0;
    for( const auto& r : res)
        ++count;
    
    return count;
};

int32_t secondChallenge(std::string s)
{
    std::unordered_map<std::string, uint32_t> res;
    res.clear();

    int32_t xs = 0;
    int32_t ys = 0;
    int32_t xr = 0;
    int32_t yr = 0;
    
    std::string tmp = std::to_string(xs) + "_" + std::to_string(ys);
    res[tmp] == 0;
    
    const uint32_t len = s.size();
    for(uint32_t i = 0; i < len; i += 2)
    {
        switch (s[i])
        {
            case '>':
            ++xs;
            break;
            case '<':
            --xs;
            break;
            case '^':
            ++ys;
            break;
            case 'v':
            --ys;
            break;
        }
        tmp = std::to_string(xs) + "_" + std::to_string(ys);
        res[tmp] == 0;

        switch (s[i + 1])
        {
            case '>':
            ++xr;
            break;
            case '<':
            --xr;
            break;
            case '^':
            ++yr;
            break;
            case 'v':
            --yr;
            break;
        }
        tmp = std::to_string(xr) + "_" + std::to_string(yr);
        res[tmp] == 0;
    }

    uint32_t count = 0;
    for( const auto& r : res)
        ++count;
    
    return count;
};

int main()
{
    std::string s;
    s = Readfile();
    int32_t s1 = firstChallenge(s);
    std::cout << s1 << std::endl;

    int32_t s2 = secondChallenge(s);
    std::cout << s2 << std::endl;
    
    return 0;
}