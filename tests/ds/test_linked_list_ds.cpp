#include<gtest/gtest.h>
#include "ds/LinkedList.hpp"

using namespace ds;

TEST(LinkedListDSTest, PushBackAndSize) {
    LinkedList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3);
}