// Problem linK: https://cses.fi/problemset/task/1681/

// This is a cses problem -> game routes. 
/*
A game has n levels, connected by m teleporters, and your task is to get from level 1 to level n. The game has been designed so that there are no directed cycles in the underlying graph. In how many ways can you complete the game?
Input
The first input line has two integers n and m: the number of levels and teleporters. The levels are numbered 1,2,\dots,n.
After this, there are m lines describing the teleporters. Each line has two integers a and b: there is a teleporter from level a to level b.
*/

// So just by looking we know it's a graph traversal problem. But what kind of graph is used here? If you see this line -> "there is a teleporter from level a to level b" -> 
// this suggested that edge must be from lvl a to lvl b => a->b ( a directed graph edge ). Also it was mentioned that no directed cycles are present. This also shows that with directed graph, no cycles are present. Hence we will consider directed graph for this problem.
// So now this problem is basically asking us to find the number of unique paths in a DAG. 

// Simple DFS + DP (because constrains are high) 
// Check code: -
#define MOD 1000000007
#include<bits/stdc++.h>
using namespace std;
int dfs(int node, vector<vector<int>> &graph, vector<int> &vis, vector<int> &dp){
    int n=graph.size();
    if(node==n-1){
        
        return 1;
    }

    if(dp[node]!=-1) return dp[node];

    vis[node]=1;

    int ans=0;

    for(auto it: graph[node]){
        if(vis[it]==1) continue;

        ans=(ans+dfs(it, graph, vis,dp))%MOD;
    }

    vis[node]=0;

    return dp[node] = ans;
}
int main()
{
    int n, m;
    cin>>n>>m;

    vector<vector<int>> edges;


    for(int i=0; i<m; i++){
        int a,b;
        cin>>a>>b;

        edges.push_back({a,b});
    }

    vector<vector<int>> graph(n);

    for(auto it: edges){
        int u=it[0]-1, v=it[1]-1;

        graph[u].push_back(v);
    }

    
    vector<int> vis(n,0);
    

    vector<int> dp(n, -1);

    cout<<(dfs(0, graph, vis, dp)%MOD)<<endl;

    return 0;
}
