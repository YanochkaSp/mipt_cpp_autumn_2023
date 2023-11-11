#include "stemmer.hpp"

int main (int argc, char* argv[])
{
    std::string str;
    std::cin >> str;
    std::string StemString = Normalize (str); 
    std::cout << StemString;
}