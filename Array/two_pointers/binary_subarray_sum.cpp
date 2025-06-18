// leetcode link: https://leetcode.com/problems/binary-subarrays-with-sum/description/

// Okay difficult to hai but only understanding me...and it's not difficult, it's just hard to think. Anyways see we are given binary array of 0s and 1s and a goal, need
// to find the number of subarrays with sum=goal. So a simple sliding window approach would come into our minds. 
// Keep adding the right pointer value and increase right pointer till sum<=goal. When sum>goal keep removing  and finally if sum=goal count++;

// So what's wrong here? This approach would definately work when the numbers are positive and non zero. What's the problem with zero. The problem is if at the edge of
// the window to be slided is =0, sum won't change even after shirnking the window. So what? So this that we won't shink it then.

// What sliding window does? while loop shirks the array till the sum>goal, then we record our answer right. Now suppose you got that i->j sum=2, Now what is the next 
// step? move j ahead. 
// But what if sum nums[i+1] =0? Then if you think sum(i+1 -> j) is also = goal, you never counted it. 


// Now sum might say, we will keep >= condition in the while loop and everytime the sum==goal, we will record it, okay fine....so suppose one of sum=goal you found out
// is from i->j, now as per your logic after recording this, you will shirk the array because of the while loop (sum>=goal) right
// But sir what if nums[j+1] =0

// Then not hus i->j is equal to goal but now i->j+1 is also equal to goal and you won't record that right....

// So what to do then? See there is a method for such cases when the sum remains constant even after shirking or expanding the window

// record the number of subarray <=goal (easy right) 
// record the number of subarray <=(goal-1)

// Take difference of both the sum....this is your answer.

// check code:-

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int n=nums.size();

        int n1=0;

        int i=0, j=0;
        int sum=0;

        while(j<n){
            sum+=nums[j];

            while(j>i && sum>goal-1){
                sum-=nums[i];

                i++;
            }

            if(sum<=goal-1) n1+=(j-i+1); // if the current subarray sum<=goal, then subaray b4 that and then b4 that is also <=goal, hence just add size of window.

            j++;
        }

        i=0,j=0,sum=0;
        int n2=0;

        while(j<n){
            sum+=nums[j];

            while(sum>goal){
                sum-=nums[i];

                i++;
            }

            if(sum<=goal) n2+=(j-i+1);

            j++;
        }

        return abs(n2-n1); // difference of both the count;
    }
};
