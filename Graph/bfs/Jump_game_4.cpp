// leetcode link: https://leetcode.com/problems/jump-game-iv/description/

// So we are given an array of integers. In one step we can either go to i+1th index or i-1 th index or to any other index where i!=j and arr[i]= arr[j]
// We need to find the minimum number of steps to get to the last index;

// Now at first it looks like a dp problem -> options are given. But see options here can be large in number as everytime we'll have "look like" 3 option but suppose
// we are at index i and number of values = arr[i] is 16, if you see properly we have 1 -> (i+1) 1-> (i-1) and 16 for same value -> 18 options and some might have
// even more. So when the constrains are high and multiple redundent options are there, we must ignore dp eventhough the problem says options. If we'll use DP -> 
// we will have large number of nodes inside our stack space -> Runtime error.

// So if not DP then perhaps we could consider them all of them as graph nodes and apply dfs. Here we will keep a visited array to automatically prune the redundent 
// cases. So fine? No, because DP goes to the depth of a node -> to its leaf node. That's the reason dfs is not considered ideal for calculating minimum steps type
// questions. 

// For minimum type questions we must have two approaches in our head-> BFS and dijastra. Dijastra is used when the graph has weights. If the graph is not having any 
// weights then we can safely proceed with BFS. Now dijastra and bfs approach level wise hence they can explore many node concurrently unline dfs which process one node 
// at a time. 

// Here we will store indecies of each arr[i] inside a map for easy retrival. Once we are done processing all the nodes of a particular number, we will clear the map value
// of that number. This is help us to reduce space and avoid mle. 
// Suppose you are processing index 1 -> 0 (already visited), 2 (not visited put into queue) and 16 other numbers. So you will iterate on mp[arr[index]] and visit
// all of them which are not visited. Now all of them are visited and are inside queue. So we don't really need them. Also this will save space. Hence we will remove 
// or clear mp[arr[index]] after the iteration. Now check the code.

// Also one more thing: BFS is always level order. Now it's on us how we want to process? level by level together or each level separate. Anyone we choose, we need to
// change a bit in our calcuations and all remains the same. For example in this problem if we choose level by level, then we will process elements from different
// level togther. So Technically for each level we need to store the number of steps separetely. We store it as a pair along with node values.

// Now if we choose to process one level completely, for each value in a level, the number of steps to reach is same. Hence after process all the elements of a same
// level, increase the steps seperately. Over that's it, that 's the only difference. No change in answer and all. Only change in processing values. 

// Okay check code: -
class Solution {
public:
    int minJumps(vector<int>& arr) {
        unordered_map<int, vector<int>> idx;

        for(int i=0; i<arr.size(); i++) idx[arr[i]].push_back(i);

        int n=arr.size();

        queue<pair<int,int>> q;

        vector<int> vis(n);

        q.push({0,0});

        vis[0]=1;

        while(!q.empty()){

           
                int node=q.front().first;
                int steps=q.front().second;

                q.pop();

                if(node==n-1) return steps;

                if(node+1<n && vis[node+1]==0){
                    vis[node+1]=1;
                    q.push({node+1, steps+1});
                }

                if(node-1>=0 && vis[node-1]==0){
                    vis[node-1]=1;
                    q.push({node-1, steps+1});
                }

                for(auto it: idx[arr[node]]){

                    if(vis[it]==1 || it==node) continue;

                    vis[it]=1;
                    q.push({it, steps+1});
                }

                idx[arr[node]].clear();

        }

        return -1;
    }
};
// I recommend checking the other solution to see second type of bfs in action as well. Check karliyo smjha. Abhi jab kr rha tha, bohot confuse kiya is cheez ne
