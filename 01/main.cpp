#include "PhoneticAlg.h"

int main (int argc, char* argv[])
{
    std::string string1;
    std::string string2;
    std::cin >> string1 >> string2;

    if (isSimilar(string1, string2))
        printf("The strings are phonetically similar");
    else
        printf("The strings are not phonetically similar");
}