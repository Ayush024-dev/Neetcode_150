// leetcode link: https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/description/?envType=daily-question&envId=2025-09-05
/*
You are given two integers num1 and num2.

In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.

Return the integer denoting the minimum number of operations needed to make num1 equal to 0.

If it is impossible to make num1 equal to 0, return -1.
*/

#define ll long long
class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        
        int t=1;

        while(true){

            ll curr=num1-(1LL*t*num2); 

            if(curr<0) return -1;

            if(__builtin_popcountll(curr)<=t && t<=curr) return t;

            t++;
        }

        return t;
        
    }
};
