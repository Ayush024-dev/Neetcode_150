// leetcode link: https://leetcode.com/problems/largest-submatrix-with-rearrangements/description/
/*
There are n flights that are labeled from 1 to n.

You are given an array of flight bookings bookings, where bookings[i] = [firsti, lasti, seatsi] represents a booking for flights firsti through lasti (inclusive) with seatsi seats reserved for each flight in the range.

Return an array answer of length n, where answer[i] is the total number of seats reserved for flight i.
*/

// Here as per the range, we need to add the seats number to the range of flights, basically the question is this-> you are given 3 numbers where first 2 are ranges and
// the third is the additive number. Add this number to the of index [first-1, second-1]. After all the operations return the answer array.

// So in this type of questions where we have to add a number to different ranges multiple times, we use a concept called difference array to get the accumalated array.
// Here suppose we need to add n to [l,r] so we create a difference array and add n to diff[l] and subtract n from diff[r+1]. This ensures that the effect of n is over
// after index r. After all the operations, take the prefix sum of difference array. 

// This is the exact way you need to do to solve this problem. See code:-
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        int sz=bookings.size();

        vector<int> diff(n);

        for(int i=0; i<sz; i++){
            int st=bookings[i][0], end=bookings[i][1], price=bookings[i][2];

            diff[st-1]+=price;

            if(end<n) diff[end]-=price; 
        }

        for(int i=1; i<n; i++) diff[i]+=diff[i-1];

        return diff;
    }
};
