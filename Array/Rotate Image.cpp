// leetcode link: https://leetcode.com/problems/rotate-image/description/

/*
90 = transpose + reverse row
180 = reverse row + reverse column
270 = transpose + reverse col
*/

// code

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        
        int n=matrix.size();

        for(int i=0; i<n; i++){
            for(int j=i; j<n; j++){
                swap(matrix[i][j], matrix[j][i]); // Code for transpose, j starts from i, remember that.
            }
        }

        for(int i=0; i<n; i++){
            reverse(matrix[i].begin(), matrix[i].end()); // for 90deg rotate
        }
    }
};
