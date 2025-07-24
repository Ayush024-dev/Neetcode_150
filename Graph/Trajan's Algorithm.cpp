// leetcode link:: https://leetcode.com/problems/critical-connections-in-a-network/submissions/1710170781/

/*Problem: Critical Connections in a Network (Leetcode 1192)
You are given a connected undirected graph with n nodes and edges. A critical connection (bridge) is an edge that, if removed, increases the 
number of connected components.
*/

/*
✅ Approach: Tarjan’s Algorithm (DFS + Low Time)
Use DFS to assign:

time[node]: Discovery time of node during DFS

low[node]: Earliest visited node reachable from node or its subtree (including back edges)

A connection is critical if:

css
Copy
Edit
low[child] > time[parent]
❌ Mistakes in Your Code:
No Parent Check in DFS:

In undirected graphs, child nodes contain parent in their adjacency list.

You treated parent edges as back edges.

➤ Fix: if (it == parent) continue;

Wrong Placement of Bridge Condition:

You placed:

cpp
Copy
Edit
if (low[node] < low[it]) ...
outside the recursive call.

Correct condition is:

cpp
Copy
Edit
if (low[it] > time[node])
and it must be inside the else block after the recursive DFS.

Low Time Update for Back Edges:

You wrote:

cpp
Copy
Edit
low[node] = min(low[node], low[it]);
But for back edges, it should be:

cpp
Copy
Edit
low[node] = min(low[node], time[it]);
🧠 Fixed Snippet Inside DFS:
cpp
Copy
Edit
for (auto it : graph[node]) {
    if (it == parent) continue; // mistake 1 fix

    if (!vis[it]) {
        dfs(it, graph, time, lowTime, vis, currTime + 1, node);
        lowTime[node] = min(lowTime[node], lowTime[it]);

        if (lowTime[it] > time[node])  // mistake 2 fix
            ans.push_back({node, it});
    } else {
        lowTime[node] = min(lowTime[node], time[it]); // mistake 3 fix
    }
}
*/


class Solution {
public:
    vector<vector<int>> ans;
    
    void dfs(int node, int parent, vector<vector<int>> &graph, vector<int> &time, vector<int> &lowTime, vector<int> &vis, int &timer) {
        vis[node] = 1;
        time[node] = lowTime[node] = timer++;
        
        for (auto it : graph[node]) {
            if (it == parent) continue; // Skip the edge to the parent node
            
            if (!vis[it]) {
                dfs(it, node, graph, time, lowTime, vis, timer);
                
                // After returning from DFS
                lowTime[node] = min(lowTime[node], lowTime[it]);
                
                // Check if it's a bridge
                if (lowTime[it] > time[node]) {
                    ans.push_back({node, it});
                }
            } else {
                // Back edge
                lowTime[node] = min(lowTime[node], lowTime[it]);
            }
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (auto& it : edges) {
            graph[it[0]].push_back(it[1]);
            graph[it[1]].push_back(it[0]);
        }

        vector<int> time(n, -1), lowTime(n, -1), vis(n, 0);
        int timer = 0;

        dfs(0, -1, graph, time, lowTime, vis, timer);

        return ans;
    }
};
