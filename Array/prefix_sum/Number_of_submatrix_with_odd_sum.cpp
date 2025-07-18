// leetcode link: https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/submissions/1702640944/
/*
Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
*/

// This problem is similar to Subaray sum to target, just a 2d version of it. Now To calculate sum of elements in 2d array in O(n) where n is no of rows in between the
// array-> we use prefix sum. First take individual prefix sum of each row and then if suppose you need to calculate the sum of elements from 0,0 -> 2,2 ->
// Aggregate the values of the last col of this matrix for(i->(0,n): sum+=(matrix[i][2]), this will give the sum of all the elements of the matrix.

// So now we can get the sum of any matrix is o(n). So we will use this to get the matrix with sum=target. We will iterate to each col and apply the same principal as
// subarray sum to target for each col starting from the start col-> in this way we will be able to scan all types of matrix and find our answer.

// Check code:-
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int n=matrix.size(); int m=matrix[0].size();

        for(int i=0; i<n; i++){
            for(int j=1; j<m; j++) matrix[i][j]+=matrix[i][j-1]; // Calculating the prefix sum for each row. 
        }

        int res=0;

        for(int startCol=0; startCol<m; startCol++){ // Finding target in all the matrix where starting column = startCol
            for(int currCol=startCol; currCol<m; currCol++){ // Iterating from startCol -> last to get all set of matrix possible with start column = startCol.

                unordered_map<int,int> mp; // Approach of Subarray sum equal to target

                mp[0]=1;
                int sum=0;
                for(int i=0; i<n; i++){

                    if(startCol>0) sum+=(matrix[i][currCol]-matrix[i][startCol-1]);
                    else sum+=(matrix[i][currCol]);

                    if(mp.find(sum-target)!=mp.end()) res+=mp[sum-target];


                    mp[sum]++;
                }
            }
        }

        return res;
    }
};
