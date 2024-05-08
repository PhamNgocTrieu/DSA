# LeetCode Problem: NO.49 Group Anagrams

## Problem Description
Given an array of strings strs, group the anagrams together. You can return the answer in any order.
```
Example:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

## Solution

Unordered Map

## Complexity Analysis

- Time Complexity: O(nklogk)
    - Sorting each string takes O(klogk) time, where k is the length of the longest string.
    - Iterating through the input vector and the map takes O(n) time, where n is the number of strings in the input.

- Space Complexity: O(n * m) - n is the number of strings in the input and m is the average length of the strings.

## Coding

```c
/* C++ */
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) 
    {
        // Create an unordered map to store groups of anagrams
        unordered_map<string, vector<string>> MyMap;

        // Iterate through each string in the input vector
        for (auto& s : strs)
        {
            // Create a copy of the string and sort it
            string tmp = s;
            sort(tmp.begin(), tmp.end());

            // Add the sorted string to the map along with the original string
            MyMap[tmp].push_back(s);
        }

        // Prepare the result vector
        vector<vector<string>> ans;
        // Iterate through the map and push each group of anagrams to the result
        for (auto& i : MyMap)
        {
            ans.push_back(i.second);
        }

        return ans;
    }
};