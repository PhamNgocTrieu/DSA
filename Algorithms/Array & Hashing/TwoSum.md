# LeetCode Problem: NO.1 Two Sum

## Solution

- Use a hashmap to store the elements as keys and their indices as values
- Iterate through the array and for each element, check if its complement (target minus the current element) exists in the hashmap
- If it does, we return the indices of both numbers. If not, we add the current element and its index to the hashmap 
- Repeat the process of checking for the complement of each element until either finding the solution or reaching the end of the input array.

## Complexity Analysis

- Time Complexity: O(n)
- Space Complexity: O(n)

## Coding

```cpp
/* C++ */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        unordered_map<int, int> hash; 
        int len = numbers.size();
        for (int i = 0; i < len; i++)
        {
            int find = target - numbers[i];
            if ( hash.find(find) != hash.end() )
                return {i, hash[find]};
            hash[numbers[i]] = i;    
        }
        return {};
    }
};
```

```c
/* C */
#define maxsize 50000

int hash(int key) {
    int r = key % maxsize;
    return r < 0 ? r + maxsize : r;
}

void insert(int *akey, int *aval, int key, int value) {
    int index = hash(key);
    while (aval[index]) 
    {
        index = (index + 1) % maxsize;
    }
    akey[index] = key;
    aval[index] = value;
}

int find(int *akey, int *aval, int key) {
    int index = hash(key);
    while (aval[index])
    {
        if (akey[index] == key) 
        {
            return aval[index];
        }
        index = (index + 1) % maxsize;
    }
    return 0;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    *returnSize = 2;
    int *result = (int *) malloc(sizeof(int) * (*returnSize));
    int akey[maxsize];
    int aval[maxsize] = {0};
    for (int i = 0; i < numsSize; i++) 
    {
        int num2find = target - nums[i];
        int search = find(akey, aval, num2find);
        if (search) 
        {
            result[0] = search - 1;
            result[1] = i;
            return result;
        }
        insert(akey, aval, nums[i], i + 1);
    }
    return NULL;
}