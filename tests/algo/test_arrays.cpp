#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Funciones de algoritmos/patrones para testing
// ============================================================================

inline vector<int> twoSumSorted(const vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return {-1, -1};
}

inline int maxSumK(const vector<int>& arr, int k) {
    int n = static_cast<int>(arr.size());
    if (n < k || k <= 0) return 0;

    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }

    int maxSum = windowSum;
    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}

inline vector<int> buildPrefixSum(const vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    return prefix;
}

inline int rangeSum(const vector<int>& prefix, int L, int R) {
    return prefix[R + 1] - prefix[L];
}

inline int maxSubarraySum(const vector<int>& nums) {
    if (nums.empty()) return 0;
    int maxSoFar = nums[0];
    int maxEndingHere = nums[0];
    for (size_t i = 1; i < nums.size(); i++) {
        maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

inline int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int writeIdx = 1;
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[i - 1]) {
            nums[writeIdx++] = nums[i];
        }
    }
    return writeIdx;
}

// ============================================================================
// Two Sum (sorted array)
// ============================================================================

TEST(ArraysTest, TwoSumSorted_Found) {
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    int target = 12;
    auto result = twoSumSorted(nums, target);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(result[0], -1);
    EXPECT_NE(result[1], -1);
    EXPECT_EQ(nums[result[0]] + nums[result[1]], target);
}

TEST(ArraysTest, TwoSumSorted_NotFound) {
    vector<int> nums = {1, 2, 3, 4};
    int target = 100;
    auto result = twoSumSorted(nums, target);
    
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], -1);
}

TEST(ArraysTest, TwoSumSorted_EmptyArray) {
    vector<int> nums = {};
    int target = 5;
    auto result = twoSumSorted(nums, target);
    
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], -1);
}

// ============================================================================
// Sliding Window (max sum of k consecutive)
// ============================================================================

TEST(ArraysTest, MaxSumK_NormalCase) {
    vector<int> arr = {2, 1, 5, 1, 3, 2};
    int k = 3;
    int result = maxSumK(arr, k);
    
    EXPECT_EQ(result, 9); // [5, 1, 3]
}

TEST(ArraysTest, MaxSumK_KEqualsN) {
    vector<int> arr = {1, 2, 3, 4};
    int k = 4;
    int result = maxSumK(arr, k);
    
    EXPECT_EQ(result, 10);
}

TEST(ArraysTest, MaxSumK_KGreaterThanN) {
    vector<int> arr = {1, 2, 3};
    int k = 5;
    int result = maxSumK(arr, k);
    
    EXPECT_EQ(result, 0); // Invalid case
}

TEST(ArraysTest, MaxSumK_SingleElement) {
    vector<int> arr = {42};
    int k = 1;
    int result = maxSumK(arr, k);
    
    EXPECT_EQ(result, 42);
}

// ============================================================================
// Prefix Sum
// ============================================================================

TEST(ArraysTest, PrefixSum_Build) {
    vector<int> arr = {1, 2, 3, 4};
    auto prefix = buildPrefixSum(arr);
    
    vector<int> expected = {0, 1, 3, 6, 10};
    EXPECT_EQ(prefix, expected);
}

TEST(ArraysTest, PrefixSum_RangeQuery) {
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    auto prefix = buildPrefixSum(arr);
    
    // Sum from index 2 to 5 (inclusive): 4 + 1 + 5 + 9 = 19
    int sum = rangeSum(prefix, 2, 5);
    EXPECT_EQ(sum, 19);
}

TEST(ArraysTest, PrefixSum_SingleElement) {
    vector<int> arr = {7};
    auto prefix = buildPrefixSum(arr);
    
    int sum = rangeSum(prefix, 0, 0);
    EXPECT_EQ(sum, 7);
}

// ============================================================================
// Kadane's Algorithm (max subarray sum)
// ============================================================================

TEST(ArraysTest, MaxSubarraySum_MixedNumbers) {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int result = maxSubarraySum(nums);
    
    EXPECT_EQ(result, 6); // subarray [4, -1, 2, 1]
}

TEST(ArraysTest, MaxSubarraySum_AllNegative) {
    vector<int> nums = {-5, -2, -8, -1};
    int result = maxSubarraySum(nums);
    
    EXPECT_EQ(result, -1); // best is single element -1
}

TEST(ArraysTest, MaxSubarraySum_AllPositive) {
    vector<int> nums = {1, 2, 3, 4, 5};
    int result = maxSubarraySum(nums);
    
    EXPECT_EQ(result, 15); // entire array
}

TEST(ArraysTest, MaxSubarraySum_SingleElement) {
    vector<int> nums = {10};
    int result = maxSubarraySum(nums);
    
    EXPECT_EQ(result, 10);
}

// ============================================================================
// Remove Duplicates (in-place)
// ============================================================================

TEST(ArraysTest, RemoveDuplicates_WithDuplicates) {
    vector<int> nums = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    int newLen = removeDuplicates(nums);
    
    EXPECT_EQ(newLen, 5);
    nums.resize(newLen);
    
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(nums, expected);
}

TEST(ArraysTest, RemoveDuplicates_NoDuplicates) {
    vector<int> nums = {1, 2, 3, 4};
    int newLen = removeDuplicates(nums);
    
    EXPECT_EQ(newLen, 4);
}

TEST(ArraysTest, RemoveDuplicates_AllSame) {
    vector<int> nums = {7, 7, 7, 7};
    int newLen = removeDuplicates(nums);
    
    EXPECT_EQ(newLen, 1);
    EXPECT_EQ(nums[0], 7);
}

TEST(ArraysTest, RemoveDuplicates_EmptyArray) {
    vector<int> nums = {};
    int newLen = removeDuplicates(nums);
    
    EXPECT_EQ(newLen, 0);
}
