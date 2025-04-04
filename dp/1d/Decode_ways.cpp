// qp link: https://neetcode.io/problems/decode-ways
// Initially I wanted to partition this string based on two options:- Whether I want to partition the substring or do not want to partition. By looking at the problem 
// statement I understood that this is a partition dp problem, as the question is asking to make different legit combinations and this can only mean one thing: make 
// partition. So what was the problem with my first approach? Well everything was fine i guess with the recursion. I had two conditions: I can only make a partition if
// the current partition string is empty and second the partition string.length<=2 and the number in the string <=26 and first character of partition shouldn't be '0', 
// because that's not any alphabet. 
// Also I was popping_out the character after the npick method so as to feed the same string of that particular recursion to the pick method. Simple...
// But then what went wrong, My dp states: I took index as one state and length of the curr partition as other state, which is wrong why? because two different string
// of same size will represent same state and will eventually return same answer. Here is the code for recursion method. I can use a map with key as {i,curr} as dp in this method
// but main thing is, this method is complex. I needed to think a lot of conditions right?...Here is the code: -
class Solution {
public:
    int solve(int idx, string &s, string curr){
        int n=s.length();

        if(idx==n){
            if(!curr.empty()){
                if(curr[0]=='0') return 0;
                

                if(curr.length()>=3) return 0;

                if(stoi(curr)>26) return 0;
            }

            return 1;
        }

        if(!curr.empty()){
                if(curr[0]=='0') return 0;
                

                if(curr.length()>=3) return 0;

                if(stoi(curr)>26) return 0;
            }

        // if(dp[idx][curr.length()]!=-1) return dp[idx][curr.length()];
        int npick=0;

        curr.push_back(s[idx]);

        npick=solve(idx+1, s, curr);

        curr.pop_back();

        int pick=0;

        if(!curr.empty()){
            curr="";
            curr.push_back(s[idx]);
            pick=solve(idx+1, s, curr);
        }

        return (npick+pick);
    }
    int numDecodings(string s) {
        string curr="";
        // vector<vector<int>> dp(s.length(), vector<int> (s.length(), -1));
        return solve(0, s, curr);
    }
};

/*----------------------------------------------------------DP code (Simple version)-----------------------------------------------------------------------------*/

// Now Here if we notice, our curr string can either be of size 1 or 2 why? because they represent index of our alphabet. So instead of deciding whether to make parti
// tions or not, why not decide whether my current partition will be of size 1 or 2. OR if I repharse that, whether I should pick one or two element at a time and make
// a partition out of it. This simplifies a lot of condition. 
// Now the conditions for one pick is that the pick should not be '0' or s[i]!='0'
// condition for two pick is that, i+1<n && s[i]!='0' (01 shouldn't be a partition) && stoi(s.substr(i,2))<=26 (to ensure that the partition is always a valid index of
// alphabet. Here as curr partition string doesn't exist, so I just need index as a state of dp. Here is the code: -
class Solution {
public:
    int solve(int i, string &s, vector<int> &dp){
        int n=s.length();

        if(i==n){
            return 1;
        }

        if(dp[i]!=-1) return dp[i];

        int two=0;

        if(i+1<n && s[i]!='0' && stoi(s.substr(i,2))<=26) two=solve(i+2, s,dp);

        int one=0;

        if(s[i]!='0') one=solve(i+1, s, dp);

        return dp[i]= (two+one);
    }
    int numDecodings(string s) {

        if(s[0]=='0') return 0;
        int n=s.length();
        vector<int> dp(n, -1);
        
        return solve(0, s, dp);
    }
};
