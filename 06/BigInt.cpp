#include "BigInt.hpp"

int main() 
{
    BigInt a("1234567890");
    BigInt b("9876543210");

    BigInt c = a + b;
    std::cout << c << std::endl;

    BigInt d = a * b;
    std::cout << d << std::endl;

    BigInt e = a - b;
    std::cout << e << std::endl;

    BigInt f = -a;
    std::cout << f << std::endl;

    return 0;
}