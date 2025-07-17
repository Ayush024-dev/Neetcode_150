// leetcode link: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/description/

/*
We are given an array of integers. We have to count the number of subarray whose sum is odd. 
*/

// Here before solving the problem, see these properties-> odd+odd=even, even+odd=odd.
// so if till a particular index i sum[0-i] is even and all the sums where sum[0-k] is odd where k<i -> it is sure that sum[k+1-i-1] or sum[k-i] is odd (odd+odd=even)

// Similarly if the sum[0-i] is odd, and all the sums where sum[0-k] is even -> it is sure that the sum[k-i] is always odd -> (even + odd) = even

// The problem is basically very similar to count subarrays with sum=k, or sum%k. We will store sums in a hashmap. Now if we encounter an odd sum and if there are even 
// sums stored in our hashmap, we can track all the odd sums in between.
// Similarly if we encounter an even and if there are odd sums stored in a our hashmap, we can track all the odd sums in between.

// IN subarray counting questions where negative integers are also involved or a case where you can't take any decision to shrink or expand your map-> Try this hashmap 
// related approach. Think if you can break the problem's requirement into 2 parts where you can track the presence of one part using the another.

// Here is the code: -
#define MOD 1000000007
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        unordered_map<int,int> mp;
        int sum=0;
        int count=0;
        int n=arr.size();
        mp[0]=1; // This is for all the odd sums from 0-i. If sum (0-i} is odd so only even sum in that case will be 0, thus it will be easy to track this odd sum
      // As this will be the only even sum in that case because 0-i is odd so no even sum recorded and hence mp[0]=1 so that we can count this type of odd sum. 
        for(int i=0; i<n; i++){
            sum+=arr[i];

            if(sum%2==0){

                if(mp.find(1)!=mp.end()) count=(count+mp[1])%MOD;
            }

            else if(sum%2!=0){
                if(mp.find(0)!=mp.end()) count=(count+mp[0])%MOD;
            }

            mp[sum%2]++;
        }

        return count;
    }
};
