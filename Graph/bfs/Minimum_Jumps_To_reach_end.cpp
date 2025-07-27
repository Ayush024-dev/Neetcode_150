//leetcode link: https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/description/

/*
you are at index 0 and you need to find minimum number of steps required to react index n-1. From an index I you can go to index i+1 or i-1 or if nums[I] 
is a prime number p, then you can go to an index j where nums[j]%p=0 and j!=i in one step. 
*/

// Here we need to find the minimum number of steps to react from 0->n-1. We can go i+1, or i-1 or j if nums[j]%p ==0 and nums[i]=p where p is a prime number. 

// We will be using bfs-> similar problem to jump game 4 (I have solved that in the same folder). But here the main issue is how to store prime number divisible index
// So the best approach for that is prime factorization of every number in nums. We will do prime factorization of each number and store the index of these numbers 
// as values into mp with key as their prime factor. 
// Check code: -
class Solution {
public:
    int maxi;
    //store the max element(max_ele) in nums array


//use sieve for marking primes:) 
    vector<bool>sieve(){


        vector<bool>is_Prime(maxi,true);
        is_Prime[0]=false;
        is_Prime[1]=false;

        for(int i=2;i*i<maxi;i++){

            if(is_Prime[i]){

                for(int j=i*i;j<maxi;j=j+i){

                    is_Prime[j]=false;
                }
            }
        }



        return is_Prime;
    }

    vector<int>primefactors(int x,vector<bool>&is_Prime){

        vector<int>ans;

    
        for(int i=2;i*i<=x;i++){

            if(x%i==0 && is_Prime[i]){

                ans.push_back(i);
                while(x%i==0)x=x/i;
            }
        }
        if(x>1)ans.push_back(x);
        return ans;
    }
    int minJumps(vector<int>& nums) {


        int n=nums.size();

        vector<int>vis(n,false);

//store number of steps, current_index
        queue<pair<int,int>>q;

//map to store the corresonding relation for each index:

//prime number p->all indexes j in nums array such that nums[j] has p as a prime factor 
        unordered_map<int,vector<int>>mp;


        
        maxi=*max_element(nums.begin(),nums.end())+1;


        vector<bool>is_Prime=sieve();
        

        for(int i=0;i<n;i++){
            vector<int>c=primefactors(nums[i],is_Prime);
            for(int p:c){

                mp[p].push_back(i);
            }
        }
        q.push({0,0});
       
        vis[0]=true;//mark start as visitee
        while(!q.empty()){
          
            auto [steps,i]=q.front();
            
            q.pop();
              if(i==n-1) return steps;
            if(i+1<n && !vis[i+1]){
                vis[i+1]=true;
                q.push({steps+1,i+1});
            }

            if(i-1>=0 && !vis[i-1]){
               vis[i-1]=true;
                q.push({steps+1,i-1});
            }

//if prime TELEPORT🥶
            if(is_Prime[nums[i]]){

                int x=nums[i];
                if(mp.count(x)){
                for(auto it:mp[x]){
                   
//visit all indexs it in nums which have x as prime factor and mark them as visited

                    if(!vis[it]){
                        vis[it]=true;
                        q.push({steps+1,it});
                    }
                }
                //x is now done and marked, no longer needed

                mp.erase(x);
                }
                   
                    
                
                
            }
        }


        return -1;
        //dummy return 
        
    }
};
