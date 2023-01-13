#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <openssl/md5.h>

int32_t firstChallenge(std::string s)
{
    int32_t res = 0;
    bool found = false;
    std::string tmp;
    unsigned char hash[MD5_DIGEST_LENGTH];
    do
    {
        ++res;
        tmp = s + std::to_string(res);
        MD5((unsigned char *)tmp.c_str(), tmp.size(), hash);

        found = hash[0] == 0 && hash[1] == 0 && hash[2] < 16;

    } while (!found);

    return res;
};

int main()
{
    std::string s = "bgvyzdsv";
    int32_t s1 = firstChallenge(s);
    std::cout << s1 << std::endl;

    return 0;
}