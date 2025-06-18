// Leetcode link: https://leetcode.com/problems/next-permutation/description/

// Here we need to find the next permuation lexiographically, of the current sequence. Now, I don't have any clue on how to start
// Now what next lexiographical permutation would typically mean? just next right?...Yes
// So All the starting index must be same till some particular index? Like for example, suppose you have an english word say "Rat" and 
// How are we sure that the word "Rax" will come after "Rat" ? 
// Because most of the character match and we try to base the order between the two based on the characters not matching. 

// In the same way, the just next sequence of the current, might have some of the number matching from index 0 till some i, then obviously
// the new sequence will have a larger number than the number at the particular index, which defined their order.
// So now approach would be to match maximum elements and try to order based on elements not matched, Let's see how: 


// Algorithm
// Suppore arr={1,2,3,6,5}, now what will be the next permutation? Now if the next permuation sequence has same characters till the last 
// index, it doesn't make any sence, because no new character. 
// If the elements are matching till index = 2, meaning nxt_sq={1,2,3,_,_} -> Can we do something? The answer is No, because 5<6 and swapping
// them would reduce the order rather than increasing it.

// What if matching is done it idx=1 -> nxt_sq={1,2,_,_,_} ? Now something can be done, since 3<5 we can arrange the sequence 3,6 and 5 in way
// to get new next sequence. 
// So one thing is clear, to generate a sequence greater than the current one, 3 must be replaced by someone greater, also to keep the increase
// at lexiographically minimum, the replacing number must be as small as possible. Hence **We would store the elements after 3 in a separte array**
// Sort it and find the upper_bound of 3, to replace with 3
// Sort it again so as to keep remaining character at the lowest.

// So elements after 3-> 6,5 or 5,6 in sorted way and replacing number = 5 after upper_bound with 3
// so the sequence becomes -> {1,2,5,_,_}, to be filled with 3 and 6. Sort the sequence again and now place it
// in the original sequence -> {1,2,5,3,6} -> well this is our answer.


// check the code for better clarity

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n=nums.size();

        int idx=n;

        for(int i=n-2; i>=0; i--){
            if(nums[i]<nums[i+1]){ // Here trying to find the number which can be swapped, remember only the number 
                                  // smaller than the next number can be swapped kyuki muze bda sequence chahiye...plz isme confuse mt hona, it's very embarrasing
                idx=i; // storing that number and breaking from the loop.
                break;
            }
        }

        if(idx==n) sort(nums.begin(), nums.end()); // if no number can be swapped, sort the array.

        else{
            vector<int> temp;

            for(int i=idx+1; i<n; i++) temp.push_back(nums[i]); // storing the elements after idx, so as to find the number > nums[idx] and smallest among the lot.

            sort(temp.begin(), temp.end()); // sorting for upper_bound purpose

            int new_i=upper_bound(temp.begin(), temp.end(), nums[idx])-temp.begin(); // find the index of the number > nums[idx] and smallest to do so.

            swap(nums[idx], temp[new_i]); 

            sort(temp.begin(), temp.end()); // sorting again, in case the order got distrubed after swapping

            for(int i=idx+1; i<n; i++) nums[i]=temp[i-(idx+1)]; //storing it back to nums
        }
    }
};
