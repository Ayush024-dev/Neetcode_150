// How to print lcs? 
// we need to use the tabulation method to print lcs. But before that we need to understand the tabulation method. Code for tabulation: -
int longestCommonSubsequence(string text1, string text2) {
        int n=text1.length(), m=text2.length();
        vector<vector<int>> dp(text1.length()+1, vector<int> (text2.length()+1, 0));

        for(int i=n-1; i>=0; i--){
            for(int j=m-1; j>=0; j--){

                if(text1[i]==text2[j]) dp[i][j]=1+dp[i+1][j+1];

                else dp[i][j]=max(dp[i+1][j], dp[i][j+1]);
            }
        }

        
        return dp[0][0];
    }

// After running this code: this it the dp array:->
/* 
3 2 1 0 
2 2 1 0 
2 2 1 0 
1 1 1 0 
1 1 1 0 
0 0 0 0 
Here the vector is a 2d vector right and n is the size of the text1="crabt"
m of text2="cat"
so n=5 and m=3 vector size of n+1 and m+1 to include index n and m as well. 
Here each col index represent the index of text2 and row index represent index of text1. So dp[4][2] means length of  lcs text2 from index 4 is compared with text1 from index 2
Just look at the tabulation code:- Whenever text1[i]==text2[j] we incremented the length of lcs and moved diagonally then. Else we moved to either down or right based
on which ones max. So just repeat this, start from 0,0=> whenever text1[i]==text2[j], push_back that character into lcs and move diagonally else move either right or
down based on which ones max... Now check the code: -
string lcs="";
        int i=0, j=0;

        while(i<n && j<m){
            if(text1[i]==text2[j]){
                lcs.push_back(text1[i]);

                i++;
                j++;
            }
            else if(dp[i][j]==dp[i+1][j]) i++;
            else j++;
        }

        cout<<lcs<<endl; 
*/
