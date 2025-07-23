// leetcode link: https://leetcode.com/problems/smallest-string-with-swaps/description/

// Here we are given a string of size n and a 2d vector pairs which contains pair of indecies whose characters can be swapped. We can swap them multiple times
// We need to find out the lexiographically smallest string after doing these swaps multiple times. 

// So what can be the approach. Well to make a string lexiographically small, we must place every character closest to it's index if the string would have been sorted.
// So let's sort the string, but sort after combining each char with it's index. 

// Now while iterating for each char, we need to place it to lowest index possible as per it's original index. Now we are given this pairs array and due to this we know
// that only certain indexes can be swapped with each other. For example if pairs= [[0,1],[0,2],[1,3],[4,5]] 
// So looking at this array we know that [0,1,2,3] can directly or indirectly swap with each other why? 1 <-> 3 right and 0 <-> 1 right so if I swap 3 with 1 and then
// 1 with 0, I indirectly swapped 3->0 right. That's how we know these indexes can be swapped directly or indirectly.Similar case is [4,5]. 

// So can we these are two different sets where in each set the indexes can mutually swap with each other Right. Now the original index of each belong to either one 
// of the set and when it's turn comes while iterating into the sorted string, I can find out the lowest index in the particular set where it belongs and we will place
// our character to that lowest index right.

// Read again slowly -> the original index is surely a part of one of sets and as we know that we sorted the string, by placing the current character into the lowest
// free index in that set we will ensure the lexiographically minimum string, because each character will have smallest possible index, right. 

// so now the only thing remain is that how do we form these sets? What is the efficient way of group these numbers together. So if we consider them as graph nodes, then
// the same pairs array will get converted into edges array. And to quickly form a group-> union operation of DSU right. This will easily form our group.

// Now for each character find out it's parent and check in the parent set, the lowest free index available and hurray you're done.
// Check code:-
class DSU{
    
    vector<int> rank, parent;
    
    public:
    
    DSU(int sz){
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
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        DSU ds(n);
        string ans(n,'*'); // initialising ans
        for(auto &it : pairs) ds.unionByRank(it[0], it[1]); // doing union of pairs to form a group
        unordered_map<int,vector<int>> mp; // To store the group by parent as key
        for(int i=0;i<n;i++){
            mp[ds.findParent(i)].push_back(i); 
        }
        for(auto &it : mp){
            string temp = ""; // Here we are storing the characters in temp which are part of a group
            for(int ind : it.second) temp += s[ind];
            sort(temp.begin(), temp.end()); // Now we can rearrange them in any way possible hence rearranging them in their correct sorted order
            int i=0;
            for(int ind : it.second) ans[ind] = temp[i++]; // Remember the it.second holds the original index of a group, and by sorting temp, we know the original 
            // order, so place all the char of the group in this order. Never ever think that there might be other characters in other group who can come to these
            // indexes because it.second for a it.first contains all the indexes of a group hence no way others are gonna occupy those pos. They will have their own.
        }
        return ans;
    }
    
};
// also a suggestion -> do go to the link and look at your own first solution, you will see how bad you were in answering them in quick time and less space. cheers
