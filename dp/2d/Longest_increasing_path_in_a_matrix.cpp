// Here we need to find the longest increasing path in a matrix, (initially I thought it to be like LIS problem, that is to find a longest set of numbers, from the entire matrix) that's why reading question carefully
// is importent. Anyways, so we can only travel horizontly or vertically in 4 directions. So the longest path will start from a particular cell and go on continuesly either vertically or horizatlly till no other cell
// can be added to the path. So the approach is to go to each cell and find out the maximum path length from that cell and then compare it with global maximum length. Also each cell in itself is a path of length 1, so
// minimum ans or the initial value of ans must be 1. Okay, othervise we will miss the last cell length. Why? Because when we are at a cell and if it's possible to move on to another cell, we will obvisouly include
// our current cell length as 1 + solve(newx, newy) in the ans. But what if we cannot move anywhere? and the initial value of ans=0, then we will just report ans=0 from the current cell and which is wrong, because the
// we missed the current cell itself, it also contributes a length 1 to our answer. Okay?...Now here is the code: -
class Solution {
public:
    vector<pair<int,int>> dirs={{-1,0},{0,-1},{0,1},{1,0}};
    int solve(int i, int j, vector<vector<int>> &matrix, vector<vector<int>> &dp){
        if(dp[i][j]!=-1) return dp[i][j];
        int n=matrix.size(), m=matrix[0].size();

        int ans=1;

        for(auto dir: dirs){
            int newx=i+dir.first;
            int newy=j+dir.second;

            if(newx<0 || newx>=n || newy<0 || newy>=m || matrix[newx][newy]<=matrix[i][j]) continue;

            ans=max(ans, 1+solve(newx, newy, matrix,dp));
        }

        return dp[i][j]= ans;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n=matrix.size(), m=matrix[0].size();

        int maxi=1;

        vector<vector<int>> dp(n, vector<int> (m,-1));

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                maxi=max(maxi, solve(i, j,matrix,dp));
            }
        }

        return maxi;
    }
};
