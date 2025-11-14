/**
 * LeetCode #1: Two Sum
 * Difficulty: Easy
 * 
 * Given an array of integers nums and an integer target, return indices of 
 * the two numbers such that they add up to target.
 * 
 * Constraints:
 * - Each input would have exactly one solution
 * - You may not use the same element twice
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include "ds/Array.hpp"

using namespace std;
using namespace ds;

class Solution {
public:
    /**
     * @brief Solución usando hash map - O(n) tiempo, O(n) espacio
     */
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        
        for (int i = 0; i < static_cast<int>(nums.size()); i++) {
            int complement = target - nums[i];
            
            if (seen.count(complement)) {
                return {seen[complement], i};
            }
            
            seen[nums[i]] = i;
        }
        
        return {};
    }
    
    /**
     * @brief Solución usando nuestra estructura Array
     */
    vector<int> twoSumWithArray(Array<int>& arr, int target) {
        unordered_map<int, int> seen;
        
        for (size_t i = 0; i < arr.size(); i++) {
            int complement = target - arr[i];
            
            if (seen.count(complement)) {
                return {seen[complement], static_cast<int>(i)};
            }
            
            seen[arr[i]] = static_cast<int>(i);
        }
        
        return {};
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    {
        cout << "Test case 1:\n";
        vector<int> nums = {2, 7, 11, 15};
        int target = 9;
        
        auto result = sol.twoSum(nums, target);
        cout << "Input: nums = [2, 7, 11, 15], target = " << target << "\n";
        cout << "Output: [" << result[0] << ", " << result[1] << "]\n";
        cout << "Explanation: nums[" << result[0] << "] + nums[" << result[1] 
             << "] = " << nums[result[0]] << " + " << nums[result[1]] << " = " << target << "\n\n";
    }
    
    // Test case 2 - usando nuestra estructura Array
    {
        cout << "Test case 2 (usando ds::Array):\n";
        Array<int> arr = {3, 2, 4};
        int target = 6;
        
        arr.print("Input");
        cout << "target = " << target << "\n";
        
        auto result = sol.twoSumWithArray(arr, target);
        cout << "Output: [" << result[0] << ", " << result[1] << "]\n\n";
    }
    
    // Test case 3
    {
        cout << "Test case 3:\n";
        Array<int> arr = {3, 3};
        int target = 6;
        
        arr.print("Input");
        cout << "target = " << target << "\n";
        
        auto result = sol.twoSumWithArray(arr, target);
        cout << "Output: [" << result[0] << ", " << result[1] << "]\n";
    }
    
    return 0;
}
