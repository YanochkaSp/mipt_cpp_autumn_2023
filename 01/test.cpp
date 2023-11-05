#include <iostream>

#include <gtest/gtest.h>

#include "PhoneticAlg.h"

class TestPhoneticArg : public ::testing::Test
{
    void SetUp()
    {
        std::cout << "Set up" << std::endl;
    }

    void TearDown()
    {
        std::cout << "Tear down" << std::endl;
    }
}

TEST_F(TestPhoneticArg, isSimilar)
{
    {
        std::string expected{"The strings are not phonetically similar"};
        ASSERT_EQ(expected, isSimilar("kjbkr", "wt"));
    }
}

int main (int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}