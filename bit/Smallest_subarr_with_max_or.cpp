// https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/description/?envType=daily-question&envId=2025-07-29
// So Today's Problem is a "BIT" challenging, I'll agree but such problems can be solved using a hidden pattern behind them. First let's understand the problem. We need to find the length of largest subarray from a 
// particular index i for each i were BIT OR is equal to maximum one. So we need to return an array or a list of size equal to nums and each element must be equal to the minimum length of the subarray
// from that particular index i and BIT OR of it's elements = max(OR).

// So How do we approach it and what is the pattern I was refering to at the start of this editorial? So for that first we need to 
// understand the brute force. It's simple for each index i, keep ORing and recording the minimum index for maximum OR. Then we can 
// calculate the length easily. The approach is a brute force one, but it does give a hint on solving it optimally.

// Why did we want the minimum index with maxOR? well that's our end goal to maximize OR value and how is a value maximized? 
// One way is -> to turn all it's unset bits to set bits. So for example you can maximize 1 -> 3, 7, ... by setting all it's 0 values
// So to maximize a particular number we need to set the unset bits, and closest to the current integer we can do it, that amount of min length
// answer we can get right. 

// Let's suppose this example : nums=[1,0,2,1,3]. Now for the index =0, I want the minimum index that that I have to traverse to get
// the max OR, or minimum index that I have to traverse to get all or most of it's bit set as per current example context. Like after 
// that last index, no other OR operation can set any other unset bits. So we will get the answer.

// So for our particular number nums[0], if I analyse all it's 32 bits, checking from my current index (0 in this case), what is that
// last index after which no new unset bit will be set (Read that again)....NO NEW UNSET BIT WILL BE SET, what's that last index? 
// mini_len=last_Idx-current_idx +1. 

// Like for nums[0]=1 -> 0000...001 (32 bits) -> Traversal start-> index    bit set from unset
//                                                                  0             no bit (because bit 0 is already set)
//                                                                  1             no bit (it is zero, all bits are unset)
//                                                                  2             1st bit (2-> 10 so nums[0] | nums[2] = 1 | 2 = 11 or 3)
//                                                                  3             no new bit (0th bit already set)
//                                                                  4             no new bit (0th and 1st bit already set)

// Traversal over. What we found? for nums[0]=1, 0th bit already set, and 1st bit was set by index 2 = 2. After this no new bit was set
// So the last index after which no new unset bit was set is index 2 for index 0. So the minimum length would be? 2-0+1 = 3. Add this to 
// the answer array. 
// So this is the pattern -> in such questions where bit is innvoled, contrainsts are high and you can't think of any solution better than 
// brute force, or can't think of any solution -> try to see the changes done bit wise. How is every bit changing or will change or must change
// as you try to apply the particular operation question is demanding. This is the pattern. Analyse every bit 


// But folks questions is not done yet. How are you planning to find the last index quickly? You can't just traverse the whole array again for each index to see which
// index is that last one. We have store something. 

// See if a|b and one of it is 1 then answer will be 1, no matter other is either 0 or 1. So A number can only set those bits, which
// are already set in it's binary representation. For example 3 = 011 so 3 can only set bit 1 and 0, by itself. It cannot set any other bit.

// So we will be using this property. We will form an unordered_map or hash map with key as the bit index and vector of nums's index which can 
// set that bit index. We will be going from 0-> n-1 and for each nums[i] if a particular bit is set, we will push i into that bit index's vector in map.

// In this way we will have all the nums's index that will set a particular bit. Now to find that last index, we can use binary search on the nums's index 
// for a particular bit we will find the first index > current index and setting the value. 
// We will repeat it for each bit and maximize our result to find that last bit we intend to find. Thus we get our answer. Check code for clarity
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        unordered_map<int, vector<int>> idx;
        int n=nums.size();

        for(int i=0; i<n; i++){

            for(int j=0; j<32; j++){

                if((nums[i] & (1<<j))!=0) {
                    idx[j].push_back(i); // storing all the nums's index which can set a particular bit index, it will already sorted as we are moving from 0->n-1
                }
            }
        }

        // for(auto it: idx){
        //     cout<<it.first<<" -> ";

        //     for(auto ele : it.second) cout<<ele<<" ";

        //     cout<<endl;
        // }

        vector<int> ans;

        for(int i=0; i<n; i++){

            int maxbitIdx=i; // to store that last index.

            for(int j=0; j<32; j++){

                if(idx.find(j)==idx.end()) continue; // This bit can't be set by any of the numbers in nums.

                auto temp=lower_bound(idx[j].begin(), idx[j].end(), i); // To find the first index that can set the current bit.

                if(temp==idx[j].end()) continue; // No index can set this bit.

                int settingidx=*temp;

                maxbitIdx=max(maxbitIdx, settingidx); // find the last index we need to go for.
            }

            ans.push_back(maxbitIdx-i+1); 
        }

        return ans;
    }
};
// Time complexity: O(N*32) 
// Space complexity: O(N*32)
