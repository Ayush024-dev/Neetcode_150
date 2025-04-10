//Here we are given two different types of string s and p, where s contains all the lowercase english letter but p contains 2 types of special characters apart from the
//the lowercase eng letters. The 2 types of characters are '*' and '.'. Now the rule is that '.' can be replaced by any english character and '*' this is interesting...
// '*' can repeat the preceading element 0 or more times till infinity. So the question is whether the string s and p matches with each other keeping in mind the rule..

// let's see the approach. Now say s=nnn and p=n* are they matching? in first look ...Helll no❌❌...but remember friends we have got some rules to follow. But b4 that
// let's understand the meaning of '*'-> repeats preceding character 0 or more times? What this means? This means that if we have a star just after a character, we can
// either remove that character (0 times repeatition) or just repeat it once or twice or thrice...so on till infinity. 
// So now if you understood the meaning of '*' then let's move forward...
// So s="nnn" and p="n*" But first we need to check whether the next character of p is a '*' and yes it is. So current character can be repeated 0 or more times.

// Let's say we make a temporary string temp to create real string out of pattern p. So now if I decide not to use the star or repeat my current character 0 times, so
// temp = "" and s=nnn, -> so it doesn't matches and now if I am not using '*', I can move my current pointer just after '*' j+2 (if j is my current pointer) and i to
// stay the same (if i is my pointer to s) because still the s[i] hasn't matched with any character of p. so if I decide to have 0 repeatation or not using '*' my state
// will become solve(i, j+2).
// Now there must be a question in some of your minds, that how 0 repeatition means not taking '*' so simply understand that '*' repeats a character and if we are going
// with 0 repeatition, it means already the previous character to '*' is not matching with s[i], so why to repeat it more times...just repeat it 0 times and move ahead...

// But what if it s[i]==p[j] then we will go on with the repeatition-> solve(i+1, j) So here s[i]==p[j] therefore we run solve(i+1, j). Now if you check again s[i]=p[j]
// repeat again the same and see again it matches and repeat again and now...i==n where n is the size of s. But where is j, still stuck on the index b4 that '*'. 
// Even though we now know that the string s and patter p has matched but on paper it looks like they haven't why? ...i==n but j still <m...So how to deal with it? ...
// See Every time we have a choice to either stop repeating or keep repeating. What if we would have stopped repeated p[j] when i==n-1 and it matched with p[j], in
// that case i->i+1 but j->j+2 and what is j+2 if j=0 remember the p="n*" j now becomes =2 that is = m so now i=n and j=m meaning the string s and p matched...
// So the gist is we always have the option to stop or keep repeating the p[j]... so after every repeatition we will check whether we should repeat it again or bs ho gya
// yaar...age badoo... Okay...if this is clear then code will also be super clear...

class Solution {
public:
    bool solve(int i, int j, string &s, string &p, int n, int m, vector<vector<int>> &dp){

        if(i>=n){
            if(j>=m) return true;

            return false;
        }

        if(dp[i][j]!=-1) return dp[i][j];

        if(j+1<m && p[j+1]=='*'){

            bool npick=solve(i, j+2, s, p, n, m, dp); // we stop repeating without checking whether it matches with the s[i] or not...

            bool pick=false;

            if(s[i]==p[j] || p[j]=='.'){
                pick=solve(i+1, j, s, p, n, m, dp) | solve(i+1, j+2, s, p, n, m, dp); // whether to keeping repeating or stop
            }

            return dp[i][j]=(npick | pick);
        }
        else{
            if(s[i]==p[j] || p[j]=='.') return dp[i][j]= solve(i+1, j+1, s, p, n, m,dp);

            else return dp[i][j]= false;
        }
    }
    bool isMatch(string s, string p) {
        int n=s.length(), m=p.length();

        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

        return solve(0, 0, s, p, n, m, dp);
    }
};
