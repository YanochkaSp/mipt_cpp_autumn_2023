#include <gtest/gtest.h>
#include "vector.hpp"

TEST(VectorTest, DefaultConstructor) 
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeConstructor) 
{
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
    EXPECT_FALSE(v.empty());
    for (int i = 0; i < v.size(); i++) 
    {
        EXPECT_EQ(v[i], 0);
    }
}

TEST(VectorTest, SizeValueConstructor) 
{
    Vector<int> v(5, 10);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
    EXPECT_FALSE(v.empty());
    for (int i = 0; i < v.size(); i++) 
    {
        EXPECT_EQ(v[i], 10);
    }
}

TEST(VectorTest, CopyConstructor) 
{
    Vector<int> v1(5, 10);
    Vector<int> v2(v1);
    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2.capacity(), v1.capacity());
    for (int i = 0; i < v2.size(); i++) 
    {
        EXPECT_EQ(v2[i], v1[i]);
    }
}

TEST(VectorTest, MoveConstructor) 
{
    Vector<int> v1(5, 10);
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.capacity(), 5);
    for (int i = 0; i < v2.size(); i++) 
    {
        EXPECT_EQ(v2[i], 10);
    }
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 0);
    EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, AssignmentOperator) 
{
    Vector<int> v1(5, 10);
    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2.capacity(), v1.capacity());
    for (int i = 0; i < v2.size(); i++) 
    {
        EXPECT_EQ(v2[i], v1[i]);
    }
}

TEST(VectorTest, MoveAssignmentOperator) 
{
    Vector<int> v1(5, 10);
    Vector<int> v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.capacity(), 5);
    for (int i = 0; i < v2.size(); i++) 
    {
        EXPECT_EQ(v2[i], 10);
    }
    EXPECT_EQ(v1.size(), 0);
    EXPECT_EQ(v1.capacity(), 0);
    EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, IndexOperator) 
{
    Vector<int> v(5);
    for (int i = 0; i < v.size(); i++) 
    {
        v[i] = i;
    }
    for (int i = 0; i < v.size(); i++) 
    {
        EXPECT_EQ(v[i], i);
    }
}

TEST(VectorTest, Front) 
{
    Vector<int> v(5);
    v[0] = 10;
    EXPECT_EQ(v.front(), 10);
}

TEST(VectorTest, Back) 
{
    Vector<int> v(5);
    v[v.size() - 1] = 20;
    EXPECT_EQ(v.back(), 20);
}

TEST(VectorTest, Data) 
{
    Vector<int> v(5);
    for (int i = 0; i < v.size(); i++) 
    {
        v[i] = i;
    }
    int* data = v.data();
    for (int i = 0; i < v.size(); i++) 
    {
        EXPECT_EQ(data[i], i);
    }
}

TEST(VectorTest, Empty) 
{
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    v.push_back(10);
    EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size) 
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    v.push_back(10);
    EXPECT_EQ(v.size(), 1);
}

TEST(VectorTest, MaxSize) 
{
    Vector<int> v;
    EXPECT_EQ(v.max_size(), std::numeric_limits<unsigned int>::max());
}

TEST(VectorTest, Reserve) 
{
    Vector<int> v;
    v.reserve(10);
    EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorTest, ShrinkToFit) 
{
    Vector<int> v(10);
    v.resize(5);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorTest, PushBack) 
{
    Vector<int> v;
    v.push_back(10);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, PopBack) 
{
    Vector<int> v;
    v.push_back(10);
    v.pop_back();
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, Insert) 
{
    Vector<int> v(5, 10);
    v.insert(20, 2);
    EXPECT_EQ(v.size(), 6);
    EXPECT_EQ(v[2], 20);
    EXPECT_EQ(v[3], 10);
    EXPECT_EQ(v[4], 10);
}

TEST(VectorTest, Emplace) 
{
    Vector<int> v(5, 10);
    v.emplace(2, 20);
    EXPECT_EQ(v.size(), 6);
    EXPECT_EQ(v[2], 20);
    EXPECT_EQ(v[3], 10);
    EXPECT_EQ(v[4], 10);
}

TEST(VectorTest, Resize) 
{
    Vector<int> v(5, 10);
    v.resize(3);
    EXPECT_EQ(v.size(), 3);
    for (int i = 0; i < v.size(); i++) 
    {
        EXPECT_EQ(v[i], 10);
    }
    v.resize(7);
    EXPECT_EQ(v.size(), 7);
    for (int i = 0; i < v.size(); i++) 
    {
        if (i < 3) 
        {
            EXPECT_EQ(v[i], 10);
        } 
        else 
        {
            EXPECT_EQ(v[i], 0);
        }
    }
}

TEST(VectorTest, Erase) 
{
    Vector<int> v(5, 10);
    v.erase(2);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[2], 10);
    EXPECT_EQ(v[3], 10);
    EXPECT_EQ(v[4], 10);
}

TEST(VectorTest, Clear) 
{
    Vector<int> v(5, 10);
    v.clear();
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 5);
    EXPECT_TRUE(v.empty());
}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}