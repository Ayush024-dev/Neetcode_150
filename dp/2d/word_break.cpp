/* qp: Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of dictionary words.

You are allowed to reuse words in the dictionary an unlimited number of times. You may assume all dictionary words are unique. */
// This time shall also pass...
// Okay so we have to partition the string such that all the partitions are present in the wordDict array and if it's not possible then return false;
// So now we need to partition right? so let's do partition: word is leetcode and wordDict=["leet", "code"];
/*                                        
          leetcode-> l (eetcode) or le (etcode) or lee (tcode) or leet(code)...and continue
          except leet(code)...not other partition in wordDict right... so we will discard other partition and only check (code) now, as leet is already been varified

          so solve(i+4)=solve(4) as i =0 
          4 is the length of leet, and after leet is done, we are moving to the next index after leet...

          leetc(ode) or leetco(de) or leetcod(e) or leetcode - > if we see properly...only code present in wordDict...so other partitions will be discarded

          only "code" will be accepted so now code is also checked and so we move i+4 = 8 

          now we will notice that 8 is last idx, so if we are reaching last index we return true;

          Here is the code: -
          
*/
class Solution {
public:
    bool solve(int idx, string &s, unordered_set<string> &st, int n, vector<vector<int>> &dp){
        if(idx==n){
            return true;
        }
        if(dp[idx][s.length()]!=-1) return dp[idx][s.length()];
        for(int l=1; l<=n; l++){
            string temp=s.substr(idx, l);

            if(st.find(temp)!=st.end() && solve(idx+l, s, st, n, dp)) return true;
        }

        return dp[idx][s.length()] = false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        int n=s.length();

        unordered_set<string> st(wordDict.begin(), wordDict.end());
        vector<vector<int>> dp(n, vector<int> (n+1, -1));
        return solve(0, s, st, n, dp);
    }
};
