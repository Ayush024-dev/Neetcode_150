// leetcode link: https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/description/
// Youtube link: https://www.youtube.com/watch?v=9biz4kxyVh8
/*
Fruits are available at some positions on an infinite x-axis. You are given a 2D integer array fruits where fruits[i] = [positioni, amounti] depicts amounti fruits at the position positioni. 
fruits is already sorted by positioni in ascending order, and each positioni is unique.

You are also given an integer startPos and an integer k. Initially, you are at the position startPos. From any position, you can either walk to the left or right. It takes one step to 
move one unit on the x-axis, and you can walk at most k steps in total. For every position you reach, you harvest all the fruits at that position, and the fruits will disappear from that position.

Return the maximum total number of fruits you can harvest.
*/

// So we have start from the startPos and any time we can go right or left from any position. We use one step each time we walk one unit and we are only allowed to take k steps. So what's more optimal, just common 
// sence and nothing else-> You deside to go either of the direction, say left. You walk some distance there, then you turn to right walk some distance there and now you are again turning to left trying to find more
// fruits to harvest. What you did here? Left-> Right -> Left, you clearly retracted your path twice. If you had turned more times, you would have retracted your path multiple times. This is not optimal use of K right

// So what is then? What if you continue to go in one direction and then turn only one and try to go to other direction as much as possible. Here retraction is done only once and you were able to cover maximum number of
// fruits. Now there are two test cases:
// 1. left -> right 
// 2. right -> left

// Case 1 left -> right
// -> Here if you decided to walk d distance in left then left range to start pos (p) p-d
// then you will be retracting the same d length again as you are going right now. You reached p again. Now how much more can you go? k-2*d (right, as you already walked 2*d distance). So right = p+(k-2d) 
// Get the sum using prefix sum and compare. Check code:- 
// Same way is for case 2 right -> left

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& nums, int startPos, int k) {
        int n = nums.size();
        vector<int> position(n), prefix(n);

        for (int i = 0; i < n; i++) {
            position[i] = nums[i][0];
            prefix[i] = nums[i][1] + (i > 0 ? prefix[i - 1] : 0);
        }

        int res = 0, p = startPos;

        for (int d = 0; d <= k / 2; d++) {
            // Case 1: Go left, then right
            int i = p - d;
            int j = p + (k - 2 * d);

            int left = lower_bound(position.begin(), position.end(), i) - position.begin();
            int right = upper_bound(position.begin(), position.end(), j) - position.begin() - 1;

            if (right >= left && right >= 0 && left < n) {
                int currsum = prefix[right];
                if (left > 0) currsum -= prefix[left - 1];
                res = max(res, currsum);
            }

            // Case 2: Go right, then left
            j = p + d;
            i = p - (k - 2 * d);

            left = lower_bound(position.begin(), position.end(), i) - position.begin();
            right = upper_bound(position.begin(), position.end(), j) - position.begin() - 1;

            if (right >= left && right >= 0 && left < n) {
                int currsum = prefix[right];
                if (left > 0) currsum -= prefix[left - 1];
                res = max(res, currsum);
            }
        }

        return res;
    }
};


