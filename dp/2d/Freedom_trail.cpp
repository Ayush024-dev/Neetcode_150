// qp link: https://leetcode.com/problems/freedom-trail/description/?envType=problem-list-v2&envId=dynamic-programming
// Here in the first glance, we can see we have kind of two options in this problem. If the current character of the ring matches with key, fine we can move the key pointer
// ahead while keeping the ring pointer at the same position. Else we have two options, either to go clockwise or anticlockwise. Let's say the pointer pointing ring is i
// and the pointer pointing key is j. So for anticlockwise -> solve((i+1)%n, j) and for clockwise -> solve((i-1+n)%n, j). Apply dp memoization and you are done right? ...
// Sorry but no...why?
// Think the string ring is in a circular format, so if the key matches with ring fine, but if not, then we will either go clockwise or anticlockwise and one of these two
// steps will take us back to the position from where we actually came from. It's similar to not us visited array will traversing a graph only to find ourselves stuck in
// an infinite loop. This would give a runtime error-> stack overflow error. 
// First if you want you can check this code as well below: - >
class Solution {
public:
    int min_steps_to_get_key(int i, int j, int n, int m, string &ring, string &key, vector<vector<int>> &dp) {
        if(j == m) return 0;
        if(dp[i][j] != -1) return dp[i][j];

        if(ring[i] == key[j])
            return dp[i][j] = 1 + min_steps_to_get_key(i, j + 1, n, m, ring, key, dp);
        else {
            int go_anticlockwise = 1 + min_steps_to_get_key((i + 1) % n, j, n, m, ring, key, dp);
            int go_clockwise = 1 + min_steps_to_get_key(((i - 1 + n) % n), j, n, m, ring, key, dp);
            return dp[i][j] = min(go_anticlockwise, go_clockwise);
        }
    }

    int findRotateSteps(string ring, string key) {
        int n = ring.length(), m = key.length();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return min_steps_to_get_key(0, 0, n, m, ring, key, dp);
    }
};
// Now how to tackle this problem? So we know that for each character in key, there may be 1 or more character in ring, right. So what if we just find out which position to
// choose and then continue our jourey. In this way we won't be in an infinite loop. For example if key is ab, and ring is aabbxx, so I know for a in key we have 2 a's 
// in ring, so two options to choose from. Similarly for b also 2 opt to choose from. So here for each character we have finite number of choices. Check the code:-
class Solution {
public:
    unordered_map<char, vector<int>> charPos;
    vector<vector<int>> dp;
    int minSteps(int i, int j, string &ring, string &key){
        int m=key.size(), n=ring.size();

        if(j==m) return 0;

        if(dp[i][j]!=-1) return dp[i][j];

        int mini=INT_MAX;
        char target=key[j];
        for(auto it: charPos[target]){
            int pos=abs(i-it);  // getting the dis for each available character matching
            int dist=min(pos, n-pos);

            int steps=dist+1+minSteps(it, j+1, ring, key);
            mini=min(mini, steps);
        }

        return dp[i][j]= mini;
    }
    int findRotateSteps(string ring, string key) {
        int n=ring.length();
        for(int i=0; i<n; i++){
            charPos[ring[i]].push_back(i); // storing all the position for current character. 
        }
        dp.resize(n, vector<int> (key.length(),-1)); 
        return minSteps(0,0,ring,key);
    }
};
