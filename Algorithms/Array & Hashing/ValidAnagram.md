# LeetCode Problem: NO.242 Valid Anagram

## Problem Description

Check whether two input strings s and t are anagrams of each other
Ex: "iceman" and "cinema"

## Solution

Hash Table (Using Array):
-

## Complexity Analysis

- Time Complexity: O(n)
- Space Complexity: O(1) (Since the size of the count arrays is constant and does not depend on the input size)

## Coding

```c
/* C */
bool isAnagram(char * s, char * t){
    // Initialize arrays to store the count of each character
    int check_s[27] = {0,}; // Array to store the count of characters in string s
    int check_t[27] = {0,}; // Array to store the count of characters in string t

    // Check if the lengths of the two strings are different
    if (strlen(s) != strlen(t))
        return false; // If lengths are different, they cannot be anagrams

    // Count the occurrences of each character in both strings
    for (int i = 0; i < strlen(s); i++)
    {
        // Increment the count for the character at index i in string s
        check_s[s[i] - 'a']++;
        // Increment the count for the character at index i in string t
        check_t[t[i] - 'a']++;
    }

    // Compare the counts of each character in both strings
    for(int i = 0; i < 27; i++)
    {
        // If a character occurs in one string but not in the other, they are not anagrams
        if (check_s[i])
        {
            if (check_s[i] != check_t[i])
                return false;
        }
    }
    // If all characters occur the same number of times in both strings, they are anagrams
    return true;
}
