// we are given a string s, and we need to calculate the longest palindromic substring for this string. Now this is a good question and such questions are mostly solved using dp!!! But how to tackle this one?...
// Okay so whenever I get such complex questions where I am not able to proceed further with the regular way, (for me it's recursion in dp questions) I tend to go to smallest unit of that question. So here what is the
// smallest unit? To check palindrome right?...
// Checking palindrome is the easiest thing I suppose, after adding two numbers maybe😂...Anyways for me the smallest unit here is to check whether the string is palindrome or not. How do we check if a string is a 
// palindrome? we take two pointers i and j at two extremes of the string. If s[i]==s[j], then do we say s is palindrome? No...instead we check for the smaller string then the current for palindrome, i.e. s[i+1] && s[j-1]
// We continue this till i<=j and if we don't get any ambiguity, we return true. Now did you observe anything? ...think...read the para above again...
// After checking s[i]==s[j], we check for i+1 and j-1. But what if we know that s from i+1 -> j-1 is already a palindrome, then after checking for s[i] and s[j], we can declare ourselves that the entire string is palindrome.
// So what if we check for palindrome from the smallest length 1 (all strings from length=1 are palindrome). Then we check for all the strings of length 2 (if both the character of the string are equal, palindrome).
// Obviously we need to store this information, for which we will maintain a 2d dp of nXn where n is the size of the string. Why 2d, because we have two parameters, starting index and the max length of the palindromic
// substring. So all dp[i][i]=1 and if (s[i]==s[i+1]) dp[i][i+1]=1.
// Now we will start checking from len=3 till n, and if(s[i]==s[i+len-1] && dp[i+1][i+len-2]==1) dp[i][i+len-1]=1. In this way we will store the max length of the palindromic substring. Check code: -
class Solution {
public:
    string longestPalindrome(string s) {
        int n=s.length();

        if(n==1) return s;

        vector<vector<int>> dp(n, vector<int> (n, 0));

        int max_i=0, maxi=1;
        for(int i=0; i<n; i++) {
            dp[i][i]=1; //setting all the substring of length 1 as palindrome
        }

        for(int i=0; i<n-1; i++){
            if(s[i]==s[i+1]){
                dp[i][i+1]=1; // setting all the palindromic substring of length 2 as palindrome in the dp array.
                if(maxi==1) max_i=i;

                maxi=2;
            }
        }
        for(int len=3; len<=n; len++){ // checking for further length.
            
            for(int i=0; i<=n-len; i++){
                if(s[i]==s[i+len-1] && dp[i+1][i+len-2]==1){
                    dp[i][i+len-1]=1;
                    if(len>maxi) max_i=i;
                    maxi=len;
                }
            }
        }

        return s.substr(max_i, maxi);

    }
};
