// https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/description/

// We need to calculate the maximum length possible with maximum AND of a subarray.

/*
To understand this problem, we first need to understand what a bitwise AND operation is. In simple terms, a 
bitwise AND operation takes two binary representations of an integer and performs the logical AND operation on 
each pair of the corresponding bits. If both bits are 1, the result is 1; otherwise, it's 0.

For example, take the numbers 12 (which is 1100 in binary) and 7 (0111 in binary). The answer will be 0100 -> 4

Now, let’s look at the problem. We're given an array, and the goal is to find a subarray where the bitwise 
AND of all the numbers is as large as possible. A subarray is a continuous portion of the array, and we want 
to return the length of the subarray that has the highest bitwise AND value.

The maximum possible bitwise AND of a subarray would be the maximum number in the array itself. 
This is because the bitwise AND operation with a larger number and a smaller number would always result in a 
number less than or equal to the smaller number. Therefore, the maximum possible bitwise AND of a subarray 
can only be achieved when all the numbers in the subarray are equal to the maximum number in the array.

largest bitwise AND can only be achieved when all the elements in the subarray are equal to the maximum number. 
So, the task is to find the longest subarray where all the numbers are the maximum value in the array.
*/
// check code: -
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int maxVal = 0, ans = 0, currentStreak = 0;

        for (int num : nums) {
            if (maxVal < num) {
                maxVal = num;
                ans = currentStreak = 0;
            }

            if (maxVal == num) {
                currentStreak++;
            } else {
                currentStreak = 0;
            }

            ans = max(ans, currentStreak);
        }
        return ans;
    }
};

// Our brute force. 
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n=nums.size();

        vector<vector<int>> ones(n, vector<int> (32, 0)); // we precompute the number of consecutive 1s in a bit position. This is done to find out the longest length
      // a particular 1 in a bit position can travel to without getting 0.

        for(int i=n-1; i>=0; i--){

            for(int j=0; j<32; j++){

                if((nums[i] & (1<<j))==0) continue; // 0 can't set

                if(i+1<n) ones[i][j]=ones[i+1][j]+1; // going from n-1 to 0, to build the consecutive 1s subarray from right to left. It will help us to find the number
                  // of consecutive ones for a particular bit position for a particular element from left to right.

                else ones[i][j]=1;
            }
        }

        int currMax=0, currMaxLen=n;

        for(int i=0; i<n; i++){
            int value=0, maxlen=n;
            for(int j=0; j<32; j++){

                if((nums[i] & (1<<j))==0) continue;

                value+=(1<<j);

                maxlen=min(maxlen, ones[i][j]); // minimizing because that's the max this 1 can go and beyond that the value will lose the presence of this one.
            }

            if(value>currMax){
                currMax=value;

                currMaxLen=maxlen;
            }
            else if(value==currMax) currMaxLen=max(currMaxLen, maxlen);
        }

        return currMaxLen;
    }
};
