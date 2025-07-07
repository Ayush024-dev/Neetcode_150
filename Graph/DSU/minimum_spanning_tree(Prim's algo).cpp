// Minimum Spanning Tree: If a graph has N nodes then the tree with all the N node and N-1 edges where all the nodes are reachable from each other is called spanning tree
// and the tree the minimum weight sum is called minimum spanning tree.

// This is using Prim's Algorithm 
class Solution {
  public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // code here
        priority_queue<vector<int>, vector<vector<int>> , greater<vector<int>>> pq;
        
        vector<int> vis(V);
        
        pq.push({0,0,-1});
        
        int sum=0;
        
        vector<pair<int,int>> mst;
        
        while(!pq.empty()){
            int wt=pq.top()[0], node=pq.top()[1], parent=pq.top()[2];
            
            pq.pop();
            
            if(vis[node]==1) continue;
            
            vis[node]=1;
            
            sum+=wt;
            
            if(parent!=-1) mst.push_back({parent, node});
            
            for(auto it: adj[node]){
                int adjnode=it[0];
                int cwt=it[1];
                
                pq.push({cwt, adjnode, node});
            }
        }
        
        for(auto it: mst){
            cout<<"("<<it.first<<","<<it.second<<")"<<endl;
        }
        
        return sum;
    }
};
// TC: O(ElogE) E for iteration into each edge and logE is for storing and sorting into pq. E is the number of edges.
// SC: O(E)
