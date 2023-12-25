#include "allocator.hpp"

#include <gtest/gtest.h>

TEST (AllocatorTest, AllocateMemory)
{
    Allocator* alloc = init_allocator(100);

    char* ptr1 = alloc(10);
    ASSERT_NE(ptr1, nullptr);

    char* ptr2 = alloc(20);
    ASSERT_NE(ptr2, nullptr);

    char* ptr3 = alloc(71);
    ASSERT_EQ(ptr3, nullptr);

    reset(alloc);
    char* ptr4 = alloc(30);
    ASSERT_NE(ptr4, nullptr);

    clear(alloc);
}

TEST (AllocatorTest, ResetAllocator)
{
    Allocator* alloc = init_allocator(100);

    char* ptr1 = alloc(10);
    ASSERT_NE(ptr1, nullptr);

    char* ptr2 = alloc(20);
    ASSERT_NE(ptr2, nullptr);

    reset(alloc);

    char* ptr3 = alloc(71);
    ASSERT_NE(ptr3, nullptr);

    clear(alloc);
}

int main (int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}