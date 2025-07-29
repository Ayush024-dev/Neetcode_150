// leetcode link: https://leetcode.com/problems/bitwise-ors-of-subarrays/description/

// Given an integer array nums, you need to find the distinct number of ORs of all the subarrays of nums.
// At first it sounds like the only way to do it is brute force. 
// You generate all the subarrays and for each subarray, calculate the OR of it's elements and add in some hash set to 
// maintain the distinct behavior. Return hash set size. But obviously, we can do better than that. But how?

// So new number can only come up if any unset bit becomes set. Now there are 32 bits, so the number of ways of generating a new value out of
// there are only log n different values possible.

// So we can do brute force but smarter. We can store the OR till index -1 in a set. Now for the current index, the new values will be nothing but
// ORing nums[index] with previous values. Check code you will understand

class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        
        unordered_set<int> total, prev; // Here total will store all the distinct OR values. Prev stores all the distinct OR
                                        // values for the subarrays ending at the prev index. Initially both are empty.
        int n=arr.size();
        for(int i=0; i<n; i++){
            unordered_set<int> curr;   // To store the distinct OR values for subarrays ending at current index
            
            for(auto it: prev){ // For all the subarrays ending at previous index, you just have to extend it to the right to include current index
                                // So We can just OR the OR values of previous index with nums[index] to get all the current values.
                int res=it | arr[i];

                curr.insert(res); // Inserting distint values into both
                total.insert(res);
            }

            curr.insert(arr[i]); // for subarray [nums[index]]
            total.insert(arr[i]);

            prev=curr; // So that the next index can use this result.
        }

        return total.size();
    }
};
