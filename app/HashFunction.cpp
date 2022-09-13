#include "HashFunction.hpp"



unsigned int hash(const std::string key)
{
    int total = 0;
    for (int i = 0; i < key.length(); ++i)
    {
        total *= 31;
        total += int(key[i]);
    }
    return total;
}