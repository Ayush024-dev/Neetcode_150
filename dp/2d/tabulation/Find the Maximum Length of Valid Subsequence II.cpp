// leetcode link: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/description/?envType=daily-question&envId=2025-07-17

/*
You are given an integer array nums and a positive integer k.
A subsequence sub of nums with length x is called valid if it satisfies:

(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
Return the length of the longest valid subsequence of nums.
 
*/

// So here we have k reminders and one of those reminders will form the longest subsequence. Here it's a classic npick pick dp as we have choice which one pick or not
// Clearly for all types of dp subsequence problems. 
// But here it's a slight catch? -> k->0-k-1 and in normal recursion dp we would fix k and try to get the maximum length of subsequce where the remider is fixed. But 
// in our dp we'll have 2 states-> i and last, to figure out (arr[i]+arr[last])%k== fixed red or not, helps in picking. And remember we are calling this whole recursion
// function for all the k values -> TC = O(n2 * k) -> TLE.

// Now in these type of problems where we have to get the longest length of subsequence and you are not able to solve it via recursion approach, try this approach ones.
// It's a similar question to calculating lis. 
// Here we know that red -> 0-k-1 and combination of one number with other mod k will return one of these reds, right. So Suppose you are at index i and combining your
// number at i with a number at j where j<i %k gives a red. Now if we know the number of elements till j which when combined in pairs consecutively %k results in red, can 
// we say the number of elements till i with red = no_till_j+1 (Given nums[j] is the first one to the left of nums[i] where (nums[j] + nums[i]) %k =red. That means 
// All these numbers can form a subsequence, whose length you know now.
// Similarly you can combine nums[i] with other j's where j<i. You can store it in a 2d dp -> dp[red][i] -> total number of elements where pairs has reminder = red.

// This approach is similar to the approach we use to print lis. Only difference is here we aren't printing the longest subsequcnce here. TC: O(k*n) and SC: O(k*n)
// check code:-
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        
        int n=nums.size();

        vector<vector<int>> dp(k, vector<int> (n,1)); // initially all have length = 1

        int maxi=0;

        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++){
                int rem=(nums[i]+nums[j])%k;

                if(dp[rem][j]+1 > dp[rem][i]){
                    dp[rem][i]=dp[rem][j]+1; // including the nums[i] with nums[j] where reminder = rem

                    maxi=max(maxi, dp[rem][i]); // comaparing the length of maximum subsequcne
                }
            }
        }

        return maxi;
    }
};
