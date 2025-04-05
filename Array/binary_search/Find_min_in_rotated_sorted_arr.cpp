/* You are given an array of length n which was originally sorted in ascending order. It has now been rotated between 1 and n times. For example, the array nums = [1,2,3,4,5,6] might become:

[3,4,5,6,1,2] if it was rotated 4 times.
[1,2,3,4,5,6] if it was rotated 6 times.
Notice that rotating the array 4 times moves the last four elements of the array to the beginning. Rotating the array 6 times produces the original array.

Assuming all elements in the rotated sorted array nums are unique, return the minimum element of this array.

A solution that runs in O(n) time is trivial, can you write an algorithm that runs in O(log n) time?*/ 
// In short, we need to find the minimum value in a rotated sorted array. So we need to apply bs over here, but how to do it? See here array is not fully sorted, it is sorted upto a point, then it dips and is sorted 
// again. That means the dip value is our min value. So during bs, when we calculate the mid, if the nums[mid]>=s and >nums[e] as well, that means the point is before the dip point, so move s beyond mid -> s=mid+1;
// Now if the nums[mid] actually becomes < nums[e], then ? e=mid-1, No...why?
// See if (nums[mid]<nums[e]) means the point is after the dip point, so what if the point is currently standing at the dip point, then? if we do e=mid-1, we will miss the dip point, and report wrong or no answer, 
// so it's better to shift e=mid, so that even if curr point is actually the dip point, we'll still be recording that. Also both s and e will converge in the dip point. Consider it like valley point in between two 
// mountain and both the pointer will eventually meet at that point. Hence when nums[mid] is equal to both nums[s] and nums[e], return nums[mid]. Also if somewhere I have used s in place of nums[s], so do not confuse
// s, e and mid are set of indicies and not actuall elements of the array. Now see the code: -
class Solution {
public:
    int findMin(vector<int> &nums) {
        int n=nums.size();

        int s=0, e=n-1;

        while(s<=e){
            int mid=s+(e-s)/2;

            if(mid==s && mid==e) return nums[mid];

            else if(nums[mid]>=nums[s] && nums[mid]>nums[e]) s=mid+1;
            else if(nums[mid]<nums[e]) e=mid;

            
        }

        return -1;
    }
};
