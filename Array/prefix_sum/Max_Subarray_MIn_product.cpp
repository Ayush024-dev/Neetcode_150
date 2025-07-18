// leetcode link: https://leetcode.com/problems/maximum-subarray-min-product/

/*
Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.

*/

// So Here we need to find the max(min(subarray)*sum(subarray)) throughout nums. Now here 2 things are changing simultanously-> the minimum value and sum. In such cases
// Try to fix one value and using that compute for another. But which one to fix here? Can we fix sum? HMM no because for a range sum there can only be one minimum value
// So you in worst case have to find all the subarrays and their minimum value to get the answer. This is brute force as well.

// So can we fix minimum value? Yes we can. See here we need to maximize sum and minimum value both. But if we keep minimum value fix, the only thing we need to increase
// is sum. The maximum sum that can have this minimum value. And all the integers here are positive, so the maximum sum will be the one that's longest, right. 

// So the longest array for which we can have that fix minimum value. How? If we find out the number of values >= current value to the left and right of the current value 
// for each value in nums, we can get the maximum length of array for each value of nums for which they are minimum. Then only thing we have to do is comparison.

// check code:-
#define ll long long
#define MOD 1000000007
class Solution {
public:
    void getleft(vector<pair<int,int>> &arr, vector<int> &nums){
        stack<pair<int,int>> st;

        int n=nums.size();

        for(int i=0; i<n; i++){
            int count=0;
            while(!st.empty() && st.top().first>=nums[i]){
                count+=(st.top().second+1);

                st.pop();
            }

            st.push({nums[i],count});

            arr[i].first=count;
        }
    }

        void getRight(vector<pair<int,int>> &arr, vector<int> &nums){
        stack<pair<int,int>> st;

        int n=nums.size();

        for(int i=n-1; i>=0; i--){
            int count=0;
            while(!st.empty() && st.top().first>=nums[i]){
                count+=(st.top().second+1);

                st.pop();
            }

            st.push({nums[i],count});

            arr[i].second=count;
        }
    }
    int maxSumMinProduct(vector<int>& nums) {
        int n=nums.size();
        vector<pair<int,int>> arr(n);

        getleft(arr,nums);
        getRight(arr,nums);

        // for(auto it: arr) cout<<it.first<<" "<<it.second<<endl;

        vector<ll> prefix(n);
        prefix[0]=nums[0];

        for(int i=1; i<n; i++) prefix[i]+=(prefix[i-1]+nums[i]);
        ll maxi=0;
        for(int i=0; i<n; i++){
            int leftidx=max(i-arr[i].first, 0);
            int rightidx=min(i+arr[i].second, n-1);
            ll sum=0;
            if(leftidx==0) sum=prefix[rightidx];
            else sum=(prefix[rightidx]-prefix[leftidx-1]);

            maxi=max(maxi, (1LL*nums[i]*sum));
        }


        return maxi%MOD;
    }
};
