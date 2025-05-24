// leetcode link: https://leetcode.com/problems/find-the-maximum-sum-of-node-values/description/?envType=daily-question&envId=2025-05-23
// check video if req: https://www.youtube.com/watch?v=bnBp6_b4GCw&t=828s
/* There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 0-indexed 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree. You are also given a positive integer k, and a 0-indexed array of non-negative integers nums of length n, where nums[i] represents the value of the node numbered i.

Alice wants the sum of values of tree nodes to be maximum, for which Alice can perform the following operation any number of times (including zero) on the tree:

Choose any edge [u, v] connecting the nodes u and v, and update their values as follows:
nums[u] = nums[u] XOR k
nums[v] = nums[v] XOR k
Return the maximum possible sum of the values Alice can achieve by performing the operation any number of times. */

// Okay guys so here, we need to maximize the sum of node values by XORing the nodes connecting an edge with k. 
// We are given an undirected tree: No cycle and each and every node is directly or indirectly connected.
// Also We can xor two nodes with k if they are connect directly via an edge. 
// Now suppose the tree is   1
                            /  \
 //                        2    1
// So currently the sum is 2+1+1=4. I want to increase the sum if possible by XORing, so I will only XOR those nodes values
// where the values increases post XOR op. so 1->1^k (by the way k=3) = 2 (increases) and 2->2^k=1 decreases. Hence I will choose
// the edge with both 1s, make them 2 and hence now the total sum becomes 2+2+2=6, which is our answer. Nice But let's suppose the tree
// is like this: value_arr=[1,2,1], (value_arr is the array containing the values of node in order). Now if I take Xor with k (just to check
// whether value increases or decreases) 1 increases to 2 but 2 decreses. So can we again pick 1 and 1? We can't pick them directly as no direct node
// is there. But  2    if I pick edge 2->1, it will be 2^k , 1^k and then if I pick 2^k->1 edge then->
//               / \   (2^k)^k , 1^k. So now the value becomes 2^k^k (=2), 1^k and 1^k = 2+2+2=6. 
//              1   1
// So what we observed? if two nodes are directly/indirectly connected, we can choose these two nodes and xor them, because all the nodes between
// them will not get affected with XOR cancelling each other. So now the problem becomes, picking a pair of two nodes together and XOR them, and to maximize the sum
// we must those values giving highest differences (postive). For which, I calculated the difference array storing difference b/w nums[i]^k and nums[i]
// sort the diff array backwards and now start picking up 2 values at a time. Remember to pick 2 values at a time, a 2 nodes will be selected at once for XORing.
// Check code: 
#define ll long long
class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n=nums.size();

        vector<int> diff(n);
        ll total=0;
        for(int i=0; i<n; i++){
            diff[i]=((nums[i]^k)-nums[i]);

            total+=(ll)nums[i];
        }
        // cout<<total<<endl;
        sort(diff.rbegin(), diff.rend());
    

        int i=0;

        while(i<n-1){
            ll addfactor=(ll)diff[i] +(ll)diff[i+1];

            if(addfactor>0) total+=addfactor;

            i+=2;
        }
        return total;
    }
};
// TC: O(nlog(n)) due to sorting + O(2n) iterations
// SC: O(n) due to diff array.
