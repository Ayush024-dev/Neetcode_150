// leetcode link: https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/description/?envType=daily-question&envId=2025-09-06
/*
You are given a 2D array queries, where queries[i] is of the form [l, r]. Each queries[i] defines an array of integers nums consisting of elements ranging from l to r, both inclusive.

In one operation, you can:

Select two integers a and b from the array.
Replace them with floor(a / 4) and floor(b / 4).
Your task is to determine the minimum number of operations required to reduce all elements of the array to zero for each query. Return the sum of the results for all queries.
*/

#define ll long long
class Solution {
public:
    ll getSteps(int l, int r){

        int L=1;
        int R=3;
        ll step=0;
        ll currStep=1;

        while(true){

            if(max(l,L)>min(r,R)){
                currStep++;
                L=R+1;
                R=4*L-1;
            }
            else{
                int len=min(r,R)-max(l,L)+1;

                step+=(1LL*len*currStep);

                if(min(r,R)==r) break;

                currStep++;
                L=R+1;
                R=4*L-1;
            }
        }

        return step;
    }
    long long minOperations(vector<vector<int>>& q) {
        int n=q.size();

        ll steps=0LL;

        for(int i=0; i<n; i++){
            int l=q[i][0];
            int r=q[i][1];
            steps+=(getSteps(l,r)+1)/2;
        }

        return steps;
    }
};
