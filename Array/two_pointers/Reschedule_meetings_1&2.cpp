// leetcode link for part 1: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/description/?envType=daily-question&envId=2025-07-09
// leetcode link for part 2: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/?envType=daily-question&envId=2025-07-10

// So both of these problems are very similar. We are given a 2d array where each array element is a vector of size 2 -> [start_i, end_i] => start time and
// end time of the ith meeting👀
// We have to rescedule the meeting such that we can maximize the free time between any two meetings. 
// Till this both of the questions are identical in nature. Then what is the change huh?....
// The change is that in part 1-> you have to maintain the relative order, but in part 2-> you can change the order
// Rescheduling in part 1 means -> you can shift the start time of at most k meeting maintaining the duration, relative order and non-overlapping
// characterstic of the meetings.
// In part 2 -> you have to reschdule only 1 meeting and you are allowed to change the order, but still the meetings must be non-overlapping in nature.
// And obviously, all the meetings must start and end with the eventTime. So this is all about the 2 problems.


// How do we proceed-> 
// For part 1, as we have to maintain the relative order, the best we could do is try to make a cluster of meetings together, so that max time can be seen. Try to keep 
// all or atleast maximum meetings together so that you can maximize the free time. Now here you can only reschedule k meetings
// So make a window of k meetings, starting from the first meeting, and then compare the free time we can have between kth meeting rescheduled and next meeting (k+1th).
// so it would be window(0-(k-1)) and then kth index or k+1th meeting. Repeat this for each index from i->n-k+1 (n-(k+1)).

// check code: -
class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        int n=startTime.size();

        vector<int> duration(n);

        for(int i=0; i<n; i++) duration[i]=endTime[i]-startTime[i];

        for(int i=1; i<n; i++) duration[i]+=(duration[i-1]); // calculating duration, because we
                                            // have to shift time variable accordingly
                                            // after 2 meeting come together, the time= time+ duration of both the meeting yaar...smajaha
                                            // kyuki time aage badega na bhai....

        int time=0;

        int maxi=0;

        for(int i=0; i<n-k+1; i++){
            maxi=max(maxi, startTime[i]-time);

            int netDuration=0;

            if(i==0){
                netDuration=duration[i+k-1];
            }
            else netDuration=duration[i+k-1]-duration[i-1];

            time+=(netDuration);

            if(i+k<n) maxi=max(maxi, startTime[i+k]-time);
            else maxi=max(maxi, eventTime-time);

            time=endTime[i];
        }

        return maxi;
    }
};

// For part 2: We can reschedule only one meeting, now let's suppose I am in meeting M1...M2...M3, 
// Currently free time = M2-M1, but if somehow, M2 is removed, free time can go up to M3-M1
// But how to remove M2? Simple boy-> Reschudle it, either keep it behind M1 if there is a space to accomadate it
// else keep it after M3 if there is a space after M3 to accomodate M2. 
// But if there is no space, then push M2 as much as possible and what's possible? to make M2 just before M3
// then the free time will be M3-M2-M1. Try doing it with all the meeting and compare the free time.

// To find out whether there is a space to accomodate a particular meeting behind or after a meeting, I calcuated the max left and right free space 
// for each meeting using which I easily understood, if there is a space or not.
// check code:-
class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int n=startTime.size();
        int time=0;
        vector<pair<int,int>> spaces(n); // to store the max free time to the left and right of each meeting.
        int maxi=0;
        
      
        for(int i=0; i<n; i++){

            if(i==0) maxi=max(maxi, startTime[i]);
            else maxi=max(maxi, startTime[i]-endTime[i-1]);
            

            spaces[i].first=maxi;
        }
        maxi=0;
        for(int i=n-1; i>=0; i--){

            if(i==n-1) maxi=max(maxi, eventTime-endTime[i]);
            else maxi=max(maxi, startTime[i+1]-endTime[i]);
            

            spaces[i].second=maxi;
        }

        maxi=0;

        for(int i=0; i<n-1; i++){
            maxi=max(maxi, startTime[i]-time);

            if(i==0){
                if(spaces[i+1].second>=(endTime[i]-startTime[i])){
                    maxi=max(maxi, startTime[i+1]-time);
                }
                else{
                    maxi=max(maxi, startTime[i+1]-(endTime[i]-startTime[i])-time);
                }
            }
            else{
                int leftmaxi=spaces[i-1].first;
                int rightmaxi=spaces[i+1].second;
                int duration=(endTime[i]-startTime[i]);
                if((duration<=leftmaxi) || (duration<=rightmaxi)){
                    maxi=max(maxi, startTime[i+1]-time);
                }
                else{
                    maxi=max(maxi, startTime[i+1]-(endTime[i]-startTime[i])-time);
                }
            }

            time=endTime[i];
        }

        int leftmaxi=spaces[n-2].first;

        if(leftmaxi>=(endTime[n-1]-startTime[n-1])) maxi=max(maxi, eventTime-time);
        else maxi=max(maxi, eventTime-(endTime[n-1]-startTime[n-1])-time);

        return maxi;
    }
};
