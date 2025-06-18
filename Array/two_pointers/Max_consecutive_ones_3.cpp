// leetcode link: https://leetcode.com/problems/max-consecutive-ones-iii/

// Here we are given binary array of 0s and 1s and we can filp k 0s to 1. Max no of sequence with 1s after filp 0s <=k times. So one approach is to zeros index and 
// maintain the relative index and relative size. Here relative size is the size of the zero array from the relative index onwards. This is give the number of zeros
// currently in my zeros array had I been removing the zeros from the beginning. If the relative size = k, shift relative index one step forward, to virtually remove 
// the first zero and set i=relative index. This will make sure that I am not recording any 0s making sz>k. 
// Add the new zeros index in the zero array. Compare the new size j-i+1;

// code: -
class Solution 
{
    public:
    int longestOnes(vector<int>& nums, int k) 
    {
        int left=0,right=0,ans=0;
        int onesFq=0;
        while(right<nums.size())
        {
            if(nums[right]==1)  
            onesFq++;
            while(right-left+1-onesFq>k)
            {
                if(nums[left]==1)
                onesFq--;
                ++left;
            }
            ans=max(ans,right-left+1);
            ++right;
        }
        return ans;
    }
};

// Approach 2
// Record the count of one and then if the count of zero till current index >k keep increasing i. So if ones count= one so zeros count = j-i+1-one;

// code: -
class Solution 
{
    public:
    int longestOnes(vector<int>& nums, int k) 
    {
        int left=0,right=0,ans=0;
        int onesFq=0;
        while(right<nums.size())
        {
            if(nums[right]==1)  
            onesFq++;
            while(right-left+1-onesFq>k)
            {
                if(nums[left]==1)
                onesFq--;
                ++left;
            }
            ans=max(ans,right-left+1);
            ++right;
        }
        return ans;
    }
};
