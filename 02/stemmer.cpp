#include "stemmer.hpp"

bool IsAlpha (const std::string& str)
{
    for (char simb : str)
    {
        if (!((simb >= 'A' && simb <= 'Z') || (simb >= 'a' && simb <= 'z'))) return false;
    }
    return true;
}

std::string ToUpper (const std::string& str)
{
    std::string res = str;
    for (char& simb : res)
    {
        simb = std::toupper (simb);
    }
    return res;
}

std::string Stem (const std::string& str)
{
    std::string res = str;
    if (res.length() >= 2)
    {
        if (res.substr(res.length() - 2) == "ed")   res = res.substr(0, res.length() - 2);
        if (res.substr(res.length() - 3) == "ing")  res = res.substr(0, res.length() - 3);
        if (res.substr(res.length() - 1) == "s")    res = res.substr(0, res.length() - 1);
        if (res.substr(res.length() - 2) == "ly")   res = res.substr(0, res.length() - 2);
    }
    return res;
}

std::string Normalize (const std::string& str)
{
    if (IsAlpha (str) == true)
    {
        std::string res = Stem (str);
        res = ToUpper (res);
        return res;
    }
    return str;
}

