class DisJointSet{
    
    vector<int> rank, parent;
    
    public:
    
    DisJointSet(int sz){
        rank.resize(sz+1,0);
        
        parent.resize(sz+1);
        
        for(int i=0; i<sz; i++){
            parent[i]=i;
        }
    }
    
    int findParent(int node){
        
        if(parent[node]==node) return node;
        
        return parent[node]=findParent(parent[node]);
    }
    
    void unionByRank(int u, int v){
        
        int utP_u=findParent(u);
        int utP_v=findParent(v);
        
        if(utP_u==utP_v) return;
        
        if(rank[utP_u]>rank[utP_v]){
            parent[utP_v]=utP_u;
        }
        
        else if(rank[utP_v]>rank[utP_u]){
            parent[utP_u]=utP_v;
        }
        
        else {
            parent[utP_v]=utP_u;
            
            rank[utP_u]++;
        }
    }
    
};

class Solution {
  public:
    int kruskalsMST(int V, vector<vector<int>> &edges) {
        // code here
        sort(edges.begin(), edges.end(),[](vector<int> &a, vector<int> &b){
            return a[2]<b[2];
        });
        
        int sum=0;
        vector<pair<int,int>> mst;
        
        DisJointSet ds(V);
        
        for(auto it: edges){
            // cout<<it.size()<<endl;
            int wt=it[2], u=it[0], v=it[1];
            
            int utP_u=ds.findParent(u);
            int utP_v=ds.findParent(v);
            
            if(utP_u==utP_v) continue; // If same parent, already part of mst, and as we sorted the edges beforehand by weight we will always get the edges with lower
                                        // weight.
            
            sum+=wt;
            
            mst.push_back({u,v});
            
            ds.unionByRank(u,v); // Here by unionByRank or (size) we will join the node u and v and both of them will have a single ultimate parent.
        }
        
        return sum;
    }
};
