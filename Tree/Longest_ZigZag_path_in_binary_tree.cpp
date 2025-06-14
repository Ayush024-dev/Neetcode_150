// leetcode link: https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/description/?envType=problem-list-v2&envId=tree


// Approach 1, For each node and each direction, compute maximum zigzag path using the getmax function. Use memoization to avoid repeated computation
// TC: O(N) and SC: O(N)
// code: -
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    map<pair<TreeNode*, bool>, int> dp;

    int getMax(TreeNode* root, bool left){

        if(!root) return 0;

        if(dp.find({root, left})!=dp.end()) return dp[{root,left}];

        if(left) return dp[{root,left}]= 1+getMax(root->left, false);
        else return dp[{root,left}]= 1+getMax(root->right, true);
    }
    int longestZigZag(TreeNode* root) {
        if(!root) return 0;

        int maxi=0;

        if(root->left) maxi=max(maxi,getMax(root, true)-1);

        if(root->right) maxi=max(maxi, getMax(root, false)-1);


        
        return max(maxi, max(longestZigZag(root->left), longestZigZag(root->right)));


    }
};

// Approach 2: Start with root node, direction and steps (which is initially 0). Use dfs and if going in the direction intended steps=steps+1 else initialize 
//             steps to 1. get the max steps. That's your answer.

// TC: O(N) and SC: O(H) where H is the height of the binary tree.

// code: -
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxlen=0;
    void solve(TreeNode* root, bool left, int steps){
        
        if(!root) return;

        maxlen=max(maxlen, steps);

        if(left){
            solve(root->left, false, steps+1);
            solve(root->right, true, 1);
        }
        else if(!left){
            solve(root->right, true, steps+1);
            solve(root->left, false, 1);
        }
    }
    int longestZigZag(TreeNode* root) {
        
        

        solve(root, true, 0);

        solve(root, false, 0);

        return maxlen;
    }
};
