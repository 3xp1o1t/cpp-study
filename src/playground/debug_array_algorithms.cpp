#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Algoritmos y patrones comunes con arrays
// ============================================================================

/**
 * @brief Two Sum con array ordenado (two pointers)
 */
vector<int> twoSumSorted(const vector<int>& nums, int target) {
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

/**
 * @brief Suma máxima de k elementos consecutivos (sliding window)
 */
int maxSumK(const vector<int>& arr, int k) {
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

/**
 * @brief Construye un array de prefix sum
 */
vector<int> buildPrefixSum(const vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    return prefix;
}

/**
 * @brief Calcula suma de elementos desde arr[L] hasta arr[R] (inclusive)
 */
int rangeSum(const vector<int>& prefix, int L, int R) {
    return prefix[R + 1] - prefix[L];
}

/**
 * @brief Algoritmo de Kadane: subarray de suma máxima
 */
int maxSubarraySum(const vector<int>& nums) {
    if (nums.empty()) return 0;
    int maxSoFar = nums[0];
    int maxEndingHere = nums[0];
    for (size_t i = 1; i < nums.size(); i++) {
        maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

/**
 * @brief Remueve duplicados de un array ordenado in-place
 */
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int writeIdx = 1;
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[i - 1]) {
            nums[writeIdx++] = nums[i];
        }
    }
    return writeIdx;
}

/**
 * @brief Utility: imprime un vector en consola
 */
template <typename T>
void printVector(const vector<T>& vec, const string& label = "") {
    if (!label.empty()) {
        cout << label << ": ";
    }
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i + 1 < vec.size()) cout << ", ";
    }
    cout << "]\n";
}

int main() {
    cout << "=== Array Algorithms - Patrones comunes ===\n\n";

    // 1. Two Sum (sorted array)
    {
        cout << "1. Two Sum (sorted array)\n";
        vector<int> nums = {1, 3, 5, 7, 9, 11};
        int target = 12;
        printVector(nums, "nums");
        cout << "target: " << target << "\n";
        
        auto result = twoSumSorted(nums, target);
        cout << "Indices: [" << result[0] << ", " << result[1] << "]";
        if (result[0] != -1) {
            cout << " -> values: " << nums[result[0]] << " + " << nums[result[1]] << " = " << target;
        }
        cout << "\n\n";
    }

    // 2. Max sum of k consecutive elements (sliding window)
    {
        cout << "2. Sliding Window - Max sum of k consecutive\n";
        vector<int> arr = {2, 1, 5, 1, 3, 2};
        int k = 3;
        printVector(arr, "arr");
        cout << "k: " << k << "\n";
        
        int maxSum = maxSumK(arr, k);
        cout << "Max sum of " << k << " consecutive: " << maxSum << "\n\n";
    }

    // 3. Prefix sum & range query
    {
        cout << "3. Prefix Sum - Range Query\n";
        vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
        printVector(arr, "arr");
        
        auto prefix = buildPrefixSum(arr);
        printVector(prefix, "prefix sum");
        
        int L = 2, R = 5;
        int sum = rangeSum(prefix, L, R);
        cout << "Sum from index " << L << " to " << R << ": " << sum << "\n";
        cout << "Verification: arr[2..5] = 4 + 1 + 5 + 9 = 19\n\n";
    }

    // 4. Kadane's Algorithm (max subarray sum)
    {
        cout << "4. Kadane's Algorithm - Max Subarray Sum\n";
        vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        printVector(nums, "nums");
        
        int maxSum = maxSubarraySum(nums);
        cout << "Max subarray sum: " << maxSum << "\n";
        cout << "Subarray: [4, -1, 2, 1]\n\n";
    }

    // 5. Remove duplicates (in-place)
    {
        cout << "5. In-place - Remove Duplicates\n";
        vector<int> nums = {1, 1, 2, 2, 2, 3, 4, 4, 5};
        printVector(nums, "original");
        
        int newLen = removeDuplicates(nums);
        nums.resize(newLen);
        printVector(nums, "after removing duplicates");
        cout << "New length: " << newLen << "\n\n";
    }

    cout << "=== Fin del playground ===\n";
    return 0;
}
