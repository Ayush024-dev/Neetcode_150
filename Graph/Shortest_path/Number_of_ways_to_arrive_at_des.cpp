// leetcode link: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/?envType=problem-list-v2&envId=graph

// So Here we are given a graph with edges weights or time in question's language. We need to count the total number of ways to react from 0 -> n-1 in the shortest 
// path possible. 

// so folks, We are required to calculate the no of shortest ways, for which we need to calculate the shortest way and there is an algo which can help us doing that,
// especially when there are weights on edges -> Dijstra. But How to calcuate the number of shortest distance? Simple count how many times
// is the shortest distance coming across right? ....Think guys? is it? 
// See if there are suppose 3 different paths connecting the des Node (n-1) and all of them are the giving the shortest distance, so ans must be 3 right?....
//.....
// No actually, I mean can be cannot be? But why? Why to make a life a little complex huh? Well here it is
// Agreed there are 3 paths, so 3 final edges connecting the des Node. But suppose one of those 3 edges or should I say 3 nodes has 2 or more ways to reach.
// Like this :=       
//                   n1 --- n3 --- des Node
//                   n2 ---/   
// So what can be seen here? to reach n3, there are actually 2 ways, one from n1 and other from n2, so Number of ways to reach the des Node via n3 will also
// be 2, --> one from n1->n3->des and other n2->n3->des. So the total ways actually becomes 4 to reach des Node.

// So what to keep in mind? We need to number of ways to reach those nodes via which we are reaching our current node, in order to calcualte the total number
// of ways. So that's why we will be maintaining a ways array storing the number of ways to reach a particular node through the shortest path.

// Here is the code: 

#define MOD 1000000007
#define ll long long
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        
        vector<vector<pair<int,int>>> graph(n);

        for(auto it: roads){
            graph[it[0]].push_back({it[1], it[2]});

            graph[it[1]].push_back({it[0], it[2]});
        }

        vector<ll> res(n, 1e18);

        vector<ll> ways(n, 0); // To calculate the number of ways for each node

        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;

        res[0]=(ll)0;
        pq.push({(ll)0, 0});

        ways[0]=(ll)1;
        while(!pq.empty()){
            ll time=pq.top().first; int node=pq.top().second;

            pq.pop();

            

            for(auto it: graph[node]){
                int currNode=it.first;
                ll currTime=(ll)it.second;

                if(time+currTime<res[currNode]){
                    res[currNode]=time+currTime;

                    pq.push({res[currNode], currNode});

                    ways[currNode]=ways[node]; // If there is a new path, the number of ways for that path will be the number of ways the previous node got 
                                                // visited by the shortest path. 
                }
                else if(time+currTime==res[currNode]){
                    ways[currNode]=(ways[currNode]+ways[node])%MOD; // if there is a different node giving same shortest dis, add it's ways as well.
                } 
            }
        }

        return ways[n-1]%MOD;
    }
};
