/* You are given an integer array piles where piles[i] is the number of bananas in the ith pile. You are also given an integer h, which represents the number of hours you have to eat all the bananas.

You may decide your bananas-per-hour eating rate of k. Each hour, you may choose a pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, you may finish eating the pile but you can not eat from another pile in the same hour.

Return the minimum integer k such that you can eat all the bananas within h hours. */

// Here we need to eat all the bananas in h hours where in each hours we can only eat fixed k number of bananas. We need to minimize this k right...
// Now suppose in place of piles of bananas, we had only one pile with total number of bananas, and we are allowed to eat k bananas every hour for h hours right? So total number of bananas consumed=k*h and this should
// be greater than or equal to total number of bananas in one pile, if we consider it equal then k approx would be total/h, but that's not the case, infact k will be greater than or equal to total/h. Why?...
// If you notice in the question, we are not allowed to eat bananas out of two piles in one hour, so if the number of bananas in a pile is >=k then we will eat k bananas but if it is < k, then we will be eating all the
// bananas in that pile and then wait for the hour to complete. Means we are wasting the time here. But one things's sure, that the minimum value of k = total/h . 

// So one approach is to continue from k=total/h till you satify the condition but this will take a lot time if the number of piles are just too much. So what can be done? If I know the max value of k, then we can 
// binary search the appropiate value of k. So what will be the max value? max of the piles, why? because that's the max value, every value is less than that. What is the condition? Calculate the ceil value of the 
// hours required to eat from each pile when we have some value of k from mid of bs. Add the number of hours and if it's <=h return true else false. Also take care of type casting-> ceil in 
// long long hours += (piles[i] + mid - 1LL) / mid; // equivalent to ceil(piles[i] / mid). So main thing is start value of k will be total/h and max will be max(piles[i]). Now here is the code: -
class Solution {
public:
    bool isPossible(long long mid, vector<int> &piles, int h){
        int n=piles.size();

        long long hours = 0;
for (int i = 0; i < n; i++) {
    hours += (piles[i] + mid - 1LL) / mid; // equivalent to ceil(piles[i] / mid)

    if(hours> h) return false;
}


        return (hours<=h);
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int n=piles.size();

        long long e=0, total=0;

        for(int i=0; i<n; i++){
            e=max(e, (long long)piles[i]);
            total+=((long long)piles[i]);
        }

        long long s=(total/h);

        if(s==0) s++; // should be atleast 1 right...You can't each bananas in 0 time

        while(s<=e){
            long long mid=s+(e-s)/2;
            if(isPossible(mid, piles, h)) e=mid-1;

            else s=mid+1;
        }

        return (int)s;
    }
};
