// leetcode link: https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/?envType=daily-question&envId=2025-06-18
// So Here we need to divide array into group of arrays of size 3

// Simple approach would be to just sort the array and collect 3 numbers if they satisfy the condition and that is, the difference between any two numbers must be <=k
// In simple languague abs(mini_number_in_array-curr_number)<=k (as this will ensure that all the pair formed with the array elements have difference <=k)

// if you can't collect current number because of the constraint, return {};

// Time complexity here would be O(nlogn) and space would be O(1)

// But's there's a way to get this in linear time -> counting sort.
// Now for knowledge: count sort is a sorting algorithm where you first storing the freq of each number in an array of size max_no_of_array. Then iterate through the
// count_array and position them accordingly.

// We will use the similar approach, first counting and storing the frequecy of each number in the count_array. Then iterating through count array and picking 3 elements
// Now count array is already sorted because the original numbers are it's index. 
// so we just have to store it. If the current index-min_val_in_curr_array >k then return {} because this is the least difference that could be achieved as the numbers
// are sorted in index form. 
// Check the code: -
class Solution {
public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        
        int n=nums.size();

        if(n<3) return {}; // if size < 3 return {} here only

        int maxi=0;

        for(auto it: nums) maxi=max(maxi, it); // get the maximum number

        vector<int> count(maxi+1,0); // One basic mistake, many do is that they will form vector of size maxi, remember maxi will also be one of index, so size must
                                    // be maxi+1;

        for(auto it: nums) count[it]++;

        vector<vector<int>> ans;
        vector<int> curr; // Current_array everytime to store 3 elements
        int mini=1e9; // minimum no in current array.
        for(int i=1; i<=maxi; i++){
            if(count[i]==0) continue; // If the count[i] is =0 that means the number wasn't there in the original array so do what your crush does to you, Ignore💀

            while(count[i]>0 && curr.size()<3){ 
                
                if(curr.empty()){ 
                    mini=i; // if the current array is empty so the first number to be in it will be the minimum number of the array, till it gets a number less than it.
                    curr.push_back(i);
                    count[i]--;
                }
                else{
                    mini=min(mini, i); // compare

                    if(abs(i-mini)<=k){ // matching the condn...nothing else
                        curr.push_back(i);
                        count[i]--;
                    }
                    else return {}; // If current index i, can't fit into your current array then forthcoming indecies will also not fill in, because difference between
                                  // them and your current mini will keep on increasing, hence return {} here only.
                }
                
            }

            if(curr.size()==3){
                ans.push_back(curr);
                curr.clear();
                mini=1e9;
            }

            if(count[i]!=0) i--; // if count[i] is not =0 means still some of i is left to push, so be at i, 
                                // going one step back to leap one forward in the next iteration...sounding like a motivation quote but anyways you got the point I hope.
        }

        

        return ans; // Have a nice day 😊
    }
};
