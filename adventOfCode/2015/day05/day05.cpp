#include <iostream>
#include <fstream>
#include <string>
#include <list>

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
    uint32_t nice_count = 0;

    for(auto r : s)
    { 
        bool isNice = true;
        
        isNice &= r.find("ab") == std::string::npos;
        isNice &= r.find("cd") == std::string::npos;
        isNice &= r.find("pq") == std::string::npos;
        isNice &= r.find("xy") == std::string::npos;
        
        uint32_t vowel_count = 0;
        bool duplicate = false;
        for(uint32_t i = 0; i < r.length(); ++i)
        {
            vowel_count += (r[i] == 'a') || (r[i] == 'e') || (r[i] == 'i') || (r[i] == 'o') || (r[i] == 'u');
            if(i) duplicate |= (r[i - 1] == r[i]);
        }

        if(isNice && (vowel_count > 2) && duplicate) ++nice_count;
    }

    return nice_count;
};

int main()
{
    std::list<std::string> inp = Readfile();
    
    int32_t s1 = firstChallenge(inp);
    std::cout << s1 << std::endl;

    return 0;
}