// leetcode link: https://leetcode.com/problems/find-the-most-competitive-subsequence/description/

// From a given array of integers, we need to find the most competitive subsequence of nums. Now what is meant by competitive? If there are two subsequences a and b of nums and the firt number that differs in both 
// the arrays is smaller in subsequence a, then a is more competitive than. God knows for what reason😂...just some stupid comparison but it's the question we can't really do anything about it.

// Anyways so the most competitive means that subsequence whose elements when differ from elements of other subsequence for the very first time, must be the smaller of the two. Also lenght of the subequence is fixed. 
// it's k. How do we go about this one? For a particular index, where elements of two subsequence in comparison is different, our ans will have the smaller number. That means for each index we need the best possible
// smallest number in order so when in a particular index, the number differs, we make sure that our ans subsequence has the smallest one.

// So For each index, we have to place the smallest number possible for that index. Okay go through an example. Suppose nums=[2,4,3,1,5,4,1,6] and k=4. Let the answer array be ans=[] (currently empty)
// Now we go on inserting and if we find something better we'll keep replacing. You'll see->

// i=0 ans is empty, just insert it -> ans[2].
// i=1 4 > 2, so 2 is still best for index 0, we'll insert 4 in our current available index =1 so ans=[2,4]
// i=2, nums[i]=3, Okay 3 < 4 for ans[1] right. 3 should be there in place of 4 in index 1, but can we replace it based on this fact only? ...No friends-> See you need a subsequence of size k, but what if this 3 removes
// more numbers than the numbers behind it (n-i-1 where n is the size of nums and i is the current index in nums). In that we won't be able to complete our subsequence because all the numbers would be used...
// So a number can only remove a number in answer if it's smaller that number in answer and requirement to complete the subsequence of size k <= total numbers behind the current nums[i]..

// IN our current case that's possible, since we require 2 more numbers to complete our subsequence (remember k=4) and there are 5 numbers behind nums[2], so it's possible, we remove 4 and add 3 in it's place 
// ans=[2,3] , can 3 remove anymore no..2<3 already best. Let's go to next index.

// i=3 => nums[i]=1 (again same logic as above) 1<3 and requirement of subsequence completion is 2 and total number behine nums[3] is 4, replace -> ans=[2,1], 
// Look 1 is smaller than 2, if we remove 2, requirement will be 3, and we have 4 number behind, so yea can be replaced => ans=[1], now cannot replace anyone, cause no one's left. 

// i=4 => nums[i]=5, cannot replace anyone, just append it ans=[1,5] (remember to maintain relative order)
// i=5 => nums[i]=4, can replace 5 in ans -> requirement is 2 and numbers behind is 2 so yea can be done -> ans=[1,4] obviously cannot replace 1 in ans...next index.

// i=6 => nums[i]=1, can it replace 4 in answer? requirement is 2 and number behine is just 1...So not possible else we won't be able to complete our subsequence. Just append it. ans=[1,4,1] 
// i=7 (last index folks) => nums[i]=6, , cannot replace any -> just append it => ans=[1,4,1,6] and we are done...

// So every time we are removing some and adding one current number we are at in nums iteration. Typical behavior of a stack, Hence this ans is a stack and later on you can replace it with an array. 

// If we see the time complexity: We are iterating through the nums array only once -> O(n) 
// Space complexity => O(n) (because of stack)
// Hope so you understood and liked the solution. If so, please upvote. Thank you and congratulations for reaching the end of the solution. 🥳🙌 Thank you..

// Check code: -
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        stack<int> st; // to store elements and apply operations.
        int n=nums.size();

        for(int i=0; i<n; i++){
            
            int count=0;
            int sz=st.size();
            while(!st.empty() && st.top()>nums[i]){

                if(k-sz+count<=(n-i-1)){ // if requirements for k sized subsequence is less than total number of elements behind current index in nums, you are good to remove.
                    st.pop();
                    count++;
                }
                else break;  // else you can't, just break.
            }

            if(st.size()+1<=k) st.push(nums[i]); // Remember the size of stack can be max be k, so don't go beyond that.
        }

        vector<int> ans;

        while(!st.empty()){
            ans.push_back(st.top());
            st.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};
