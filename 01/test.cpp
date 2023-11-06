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
};

TEST_F(TestPhoneticArg, isSimilar)
{
    {
        int expected{-1};
        int received = isSimilar("kjbkr", "wt");
        ASSERT_EQ(expected, received);
    }
}

int main (int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}