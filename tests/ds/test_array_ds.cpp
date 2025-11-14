#include <gtest/gtest.h>
#include "ds/Array.hpp"

using namespace ds;

// ============================================================================
// Construcción y acceso
// ============================================================================

TEST(ArrayDSTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayDSTest, SizeConstructor) {
    Array<int> arr(5);
    EXPECT_EQ(arr.size(), 5);
    EXPECT_FALSE(arr.empty());
}

TEST(ArrayDSTest, SizeValueConstructor) {
    Array<int> arr(3, 42);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 42);
    EXPECT_EQ(arr[1], 42);
    EXPECT_EQ(arr[2], 42);
}

TEST(ArrayDSTest, InitializerListConstructor) {
    Array<int> arr = {1, 2, 3, 4, 5};
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[4], 5);
}

TEST(ArrayDSTest, AccessOperators) {
    Array<int> arr = {10, 20, 30};
    
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    
    arr[1] = 99;
    EXPECT_EQ(arr[1], 99);
}

TEST(ArrayDSTest, AtMethod_Valid) {
    Array<int> arr = {1, 2, 3};
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(2), 3);
}

TEST(ArrayDSTest, AtMethod_OutOfRange) {
    Array<int> arr = {1, 2, 3};
    EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayDSTest, FrontBack) {
    Array<int> arr = {10, 20, 30};
    EXPECT_EQ(arr.front(), 10);
    EXPECT_EQ(arr.back(), 30);
}

// ============================================================================
// Modificadores
// ============================================================================

TEST(ArrayDSTest, PushBack) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayDSTest, PopBack) {
    Array<int> arr = {1, 2, 3};
    arr.pop_back();
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayDSTest, Insert) {
    Array<int> arr = {1, 2, 4, 5};
    arr.insert(2, 3);
    
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
}

TEST(ArrayDSTest, Erase) {
    Array<int> arr = {10, 20, 30, 40};
    arr.erase(1);
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);
}

TEST(ArrayDSTest, Clear) {
    Array<int> arr = {1, 2, 3};
    arr.clear();
    
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayDSTest, Resize) {
    Array<int> arr = {1, 2, 3};
    arr.resize(5);
    
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1);
}

// ============================================================================
// Utilidades
// ============================================================================

TEST(ArrayDSTest, Fill) {
    Array<int> arr(5);
    arr.fill(42);
    
    for (size_t i = 0; i < arr.size(); i++) {
        EXPECT_EQ(arr[i], 42);
    }
}

TEST(ArrayDSTest, Reverse) {
    Array<int> arr = {1, 2, 3, 4, 5};
    arr.reverse();
    
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 2);
    EXPECT_EQ(arr[4], 1);
}

TEST(ArrayDSTest, Sort) {
    Array<int> arr = {5, 2, 8, 1, 9};
    arr.sort();
    
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 5);
    EXPECT_EQ(arr[3], 8);
    EXPECT_EQ(arr[4], 9);
}

TEST(ArrayDSTest, Find_Found) {
    Array<int> arr = {10, 20, 30, 40};
    int idx = arr.find(30);
    
    EXPECT_EQ(idx, 2);
}

TEST(ArrayDSTest, Find_NotFound) {
    Array<int> arr = {10, 20, 30};
    int idx = arr.find(99);
    
    EXPECT_EQ(idx, -1);
}

TEST(ArrayDSTest, Count) {
    Array<int> arr = {1, 2, 3, 2, 4, 2};
    size_t cnt = arr.count(2);
    
    EXPECT_EQ(cnt, 3);
}

// ============================================================================
// Iteradores
// ============================================================================

TEST(ArrayDSTest, RangeBasedFor) {
    Array<int> arr = {1, 2, 3};
    int sum = 0;
    
    for (const auto& val : arr) {
        sum += val;
    }
    
    EXPECT_EQ(sum, 6);
}

TEST(ArrayDSTest, ToString) {
    Array<int> arr = {1, 2, 3};
    std::string str = arr.toString();
    
    EXPECT_EQ(str, "[1, 2, 3]");
}
