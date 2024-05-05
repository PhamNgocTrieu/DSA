# LeetCode Problem: NO.217 Contains Duplicate

## Problem Description

Given an integer array `nums`, return true if any value appears at least twice in the array, and return false if every element is distinct
Ex. nums = [1,2,3,1] -> true, nums = [1,2,3,4] -> false

## Solution

Use an unordered set to keep track of seen elements. It iterates through the array and checks if the current element is already in the set

## Complexity Analysis

- Time Complexity: O(n)
- Space Complexity: O(n)

```cpp
/* C++ */
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> container;
            
            for (int i = 0; i < nums.size(); i++) {
                if (container.find(nums[i]) != container.end()) {
                    return true;
                }
                container.insert(nums[i]);
            }
            
            return false;
    }
};