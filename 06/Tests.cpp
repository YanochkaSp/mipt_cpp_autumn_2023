#include <gtest/gtest.h>
#include "BigInt.hpp"

TEST(BigIntTest, DefaultConstructor) 
{
    BigInt number;
    EXPECT_EQ(number, 0);
}

TEST(BigIntTest, StringConstructorPositive) 
{
    BigInt number("12345");
    EXPECT_EQ(number, 12345);
}

TEST(BigIntTest, StringConstructorNegative) 
{
    BigInt number("-12345");
    EXPECT_EQ(number, -12345);
}

TEST(BigIntTest, IntConstructorPositive) 
{
    BigInt number(12345);
    EXPECT_EQ(number, 12345);
}

TEST(BigIntTest, IntConstructorNegative) 
{
    BigInt number(-12345);
    EXPECT_EQ(number, -12345);
}

TEST(BigIntTest, CopyConstructor) 
{
    BigInt number1(12345);
    BigInt number2(number1);
    EXPECT_EQ(number2, 12345);
}

TEST(BigIntTest, MoveConstructor) 
{
    BigInt number1(12345);
    BigInt number2(std::move(number1));
    EXPECT_EQ(number2, 12345);
    EXPECT_EQ(number1, 0);
}

TEST(BigIntTest, CopyAssignmentOperator) 
{
    BigInt number1(12345);
    BigInt number2;
    number2 = number1;
    EXPECT_EQ(number2, 12345);
}

TEST(BigIntTest, MoveAssignmentOperator) 
{
    BigInt number1(12345);
    BigInt number2;
    number2 = std::move(number1);
    EXPECT_EQ(number2, 12345);
    EXPECT_EQ(number1, 0);
}

TEST(BigIntTest, Addition) 
{
    BigInt number1(12345);
    BigInt number2(54321);
    BigInt sum = number1 + number2;
    EXPECT_EQ(sum, 66666);
}

TEST(BigIntTest, Subtraction) 
{
    BigInt number1(54321);
    BigInt number2(12345);
    BigInt difference = number1 - number2;
    EXPECT_EQ(difference, 41976);
}

TEST(BigIntTest, Multiplication) 
{
    BigInt number1("1234567890");
    BigInt number2("9876543210");
    BigInt product = number1 * number2;
    EXPECT_EQ(product, "12193263111263526900");
}

TEST(BigIntTest, UnaryMinus) 
{
    BigInt number(12345);
    BigInt negativeNumber = -number;
    EXPECT_EQ(negativeNumber, -12345);
}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
