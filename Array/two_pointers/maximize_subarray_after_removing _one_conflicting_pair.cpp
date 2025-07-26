// leetcode link: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/description/?envType=daily-question&envId=2025-07-26

/*
You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.

Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].

Return the maximum number of subarrays possible after removing exactly one conflicting pair.

*/

// So here we are given restrictions on numbers. These numbers cannot be together in a subarray. So what can be done? So how many subarray if none is removed?
// Read this: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/solutions/7005546/beginner-friendly-explanation-an-intuitive-single-pass-solution-python-c-java/?envType=daily-question&envId=2025-07-26

// check code: 0
#define ll long long
class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        ll ans=0;

        vector<ll> bonus(n+1);

        vector<vector<int>> lefts(n+1);

        for(auto it: conflictingPairs){
            int a=min(it[0], it[1]);
            int b=max(it[0], it[1]);

            lefts[b].push_back(a);
        }
        ll top1=0, top2=0;
        for(int i=0; i<=n; i++){

            int b=i;
            
            for(auto a: lefts[b]){
                
                if(a>top1){
                    top2=top1;
                    top1=a;
                }
                else if(a>top2){
                    top2=a;
                }
            }

            ans+=(b-top1);

            if(top1>0){
                bonus[top1]+=(top1-top2);
            }
        }
        ll maxi=0;
        for(auto it: bonus){
            // cout<<it<<" ";
            maxi=max(maxi, it);
        }
        // cout<<endl;
        // cout<<ans<<endl;
        // cout<<maxi<<endl;

        return ans+maxi;
    }
};
