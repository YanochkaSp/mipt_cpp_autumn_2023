#include <iostream>

#include <gtest/gtest.h>

#include "stemmer.hpp"

TEST (StemmerTest, IsAlpha)
{
    EXPECT_TRUE  (IsAlpha ("cat"));
    EXPECT_FALSE (IsAlpha ("d0g"));
    EXPECT_FALSE (IsAlpha ("2023"));
}

TEST (StemmerTest, ToUpper)
{
    EXPECT_EQ (ToUpper ("cat"),          "CAT");
    EXPECT_EQ (ToUpper ("hello world!"), "HELLO WORLD!");
}

TEST (StemmerTest, Stem)
{
    EXPECT_EQ (Stem ("painting"), "paint");
    EXPECT_EQ (Stem ("cats"),     "cat");
    EXPECT_EQ (Stem ("jumped"),   "jump");
    EXPECT_EQ (Stem ("firstly"),  "first");
}

TEST (StemmerTest, Normalize)
{
    EXPECT_EQ (Normalize ("cat"), "CAT");
    EXPECT_EQ (Normalize ("d0g"), "d0g");
    EXPECT_EQ (Normalize ("2023"), "2023");
    EXPECT_EQ (Normalize ("painting"), "PAINT");
    EXPECT_EQ (Normalize ("cats"), "CAT");
}

int main (int argc, char* argv[])
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}

