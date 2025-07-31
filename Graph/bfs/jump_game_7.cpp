// leetcode: https://leetcode.com/problems/jump-game-vii/

/*
You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you are standing at index 0, which is equal to '0'. You can move from index i to index j if the following conditions are fulfilled:

i + minJump <= j <= min(i + maxJump, s.length - 1), and
s[j] == '0'.
Return true if you can reach index s.length - 1 in s, or false otherwise.
*/

// Same as jump game 4 but here we have a range of values to go for. Jump can range from (i+minJump, min(i + maxJump, s.length - 1)). So if we apply normal bfs, the time
// complexity will be O(n*J) where n is the length of the string and J is the Jump range length.
// So how to remove or reduce that J. See if there is a range, most of the elements will be overlapping ranges, but if we have already visited some range then why to visit
// them again? Hence we will maintain a variable called farthest which will store the farthest index we visited till now. So that we do not repeat the range. Check code:

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        
        int n=s.length();
        if(s[n-1]=='1') return false;
        queue<int> q;

        vector<int> vis(n,0);
        int farthest=0; // to store the farthest index we have been to, reduces redundent iteration.
        q.push(0);

        vis[0]=1;

        while(!q.empty()){
            int sz=q.size();

            while(sz--){
                int node=q.front();
                q.pop();

                if(node==n-1) return true;

                int mini=node+minJump;
                int maxi=min(node+maxJump, n-1);

                int start=max(farthest, mini); // start is the new value from where we will be starting our iteration. 
                if(start>maxi) return false; // If start itself > maxi, then we can't do any iteration.

                if(maxi==n-1) return true; // if maxi is last index, just return true;

                

                for(int i=start; i<=maxi; i++){

                    if(s[i]=='1') continue;

                    if(vis[i]==1) continue;

                    vis[i]=1;
                    q.push(i);
                }

                farthest=max(farthest, maxi);
            }
        }

        return false;
    }
};
