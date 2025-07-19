// leetcode link: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/?envType=daily-question&envId=2025-07-18

/* We are given an array of 3n size and we are asked to remove any n element in order (subsequence of size n). Now after removal store the sum of first n numbers in 
Sumf and the last n numbers in SumS. Take the difference. Well you have to minimize this difference, choosing appropiate character for removal.
*/


// So we have to minimize the diff=Sumf-SumS. So clearly we have to minimize Sumf and maximize SumS. Hence while building Sumf, if the no of elements > n, we will remove
// the max of those numbers and similary for Sumf -> we will remove the minimum of those number if they are > n

// So what can be the combination? keep first n number -> first set and rest 2n numbers in the second set. Remove that subsequece from the second set and compare with
// minimum. Now increase the size of first set and decrease the size of second set by pushing the first number in second set to the first set. Again remove number according
// from both sets till they have n numbers each. Get the sum and compare. We will try for all the combinations-> i=n-1 (left has n elements and right has 2n elements)
// to i=2n-1 (left has 2n elements and right has n elements). 

// Now before we do this, we need to do some pre computation? Since we require sum at each index after certain number removal (max numbers for left and min for right),
// let's precompute this so that at the time of operation we can get this info in O(1). 
// So add nums[i] to sum and if the numbers involved > n remove the numberes and adjust the sum. 

// SEE code:-
#define ll long long
class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int m=nums.size();
        int n=m/3;
        vector<ll> left(2*n), right; // precoumputing sums for left and right sets.
        ll sum=0;
        priority_queue<int> maxH; // to remove the maximum element
        priority_queue<int, vector<int> ,greater<int>> minH; // to remove the minimum element
        for(int i=0; i<2*n; i++){
            maxH.push(nums[i]);
            sum+=nums[i];

            if(maxH.size()>n){ // if the number involved in sum > n (it will only become n+1 at max before we remove the number)
                sum-=maxH.top();
                maxH.pop();
            }

            left[i]=sum;
        }
        sum=0;
        for(int i=3*n-1; i>=n; i--){
            minH.push(nums[i]);
            sum+=nums[i];

            if(minH.size()>n){
                sum-=minH.top();
                minH.pop();
            }

            right.push_back(sum);
        }

        ll mini=LLONG_MAX;
        int j=2*n-1; // when i=n , j-> 2n and so on...
        for(int i=n-1; i<=2*n-1; i++){
            ll Sumf=left[i];
            ll SumS=right[j];

            mini=min(mini, Sumf-SumS);

            j--;

            
        }

        return mini;
    }
};
