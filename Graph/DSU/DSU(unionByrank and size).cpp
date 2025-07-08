using namespace std;

class DisJointSet{
    vector<int> rank,parent,size;
    
    public:
        DisJointSet(int n){
            rank.resize(n+1,0);
            size.resize(n+1,1);
            parent.resize(n+1);
            
            for(int i=0; i<n; i++){
                parent[i]=i;
            }
        }
    
        int findPar(int u){
            if(u==parent[u]) return u;
            
            return parent[u]=findPar(parent[u]); //Path compression
        }
    
        void unionbyRank(int u, int v){
            int u_par=findPar(u);
            int v_par=findPar(v);
            
            if(u_par==v_par) return;
            
            if(rank[u_par]>rank[v_par]){
                parent[v_par]=u_par;
            }
            else if(rank[v_par]>rank[u_par]){
                parent[u_par]=v_par;
            }
            else{
                parent[v_par]=u_par;
                rank[u_par]++;
            }
        }
    
        void unionbySize(int u, int v){
            int u_par=findPar(u);
            int v_par=findPar(v);
            
            if(u_par==v_par) return;
            
            if(size[u_par]>size[v_par]){
                parent[v_par]=u_par;
                size[u_par]+=size[v_par];
            }
            else if(size[v_par]>size[u_par]){
                parent[u_par]=v_par;
                size[v_par]+=size[u_par];
            }
            else{
                parent[v_par]=u_par;
                size[u_par]+=size[v_par];
            }
        }
};

int main() {
    DisJointSet ds(7);
    // ds.unionbyRank(1,2);
    // ds.unionbyRank(2,3);
    // ds.unionbyRank(4,5);
    // ds.unionbyRank(6,7);
    // ds.unionbyRank(5,6);
    
    ds.unionbySize(1,2);
    ds.unionbySize(2,3);
    ds.unionbySize(4,5);
    ds.unionbySize(6,7);
    ds.unionbySize(5,6);
    
    //if 3 and 7 in the same path or not
    if(ds.findPar(3) == ds.findPar(7)) cout<<"Same"<<endl;
    else cout<<"Not same\n";
        
    ds.unionbySize(3,7);
    if(ds.findPar(3) == ds.findPar(7)) cout<<"Same"<<endl;
    else cout<<"Not same\n";
        
    return 0;
}
