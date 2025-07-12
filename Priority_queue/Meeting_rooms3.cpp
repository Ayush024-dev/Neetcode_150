// leetcode link: https://leetcode.com/problems/meeting-rooms-iii/?envType=daily-question&envId=2025-07-11

/*
Given n meeting rooms and some meetings with their start and end duration, in half closed interval fashion -> [) 
We need to host each meeting in a room with smallest available room number. After we are done hosting all the meets, we must return the room number that has hosted 
most of the meetings. In case of mulitple outputs, return the smallest room number.
*/
// Here if we think properly, we have two variables that define the problem, the room number and start of new meeting and end time of previous meeting.
// Now there can be two cases 1. We have rooms available to host the meeting. In this case pick the room with smallest room number of all the other available rooms and host meeting there.
//                            2. We do not have rooms available to host the meeting. In this case, wait for the first room to get free, then host meeting in that.
// IN both of these cases, we have to increment the count of the room number hosted the particular meeting.
// Here as we require min room number and min endTime, we will maintain two min heap pq for the purpose. One pq will store information about free rooms to host meetings
// The other pq will hold information about the busy rooms which might get free when the next meeting starts.
// When a meeting starts, first we will see the new rooms which just got available. For this pop all the rooms from busy room pq which have endtime <= startTime of the new meeting okay.
// Push the room numbers of those newly free rooms into free room pq. Now we can get the minimum room number in a second from free room pq. In case that's empty, pop the busy room top and add 
// duration of this meeting into it's endtime and push it again

// check code:-
#define ll long long
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        priority_queue<int,vector<int>, greater<int>> roomPq; // Free room pq
        priority_queue<pair<ll,int>,vector<pair<ll,int>>, greater<pair<ll,int>>> timePq; // busy room pq -> {endTime_of_prev_meet, room_number}


        for(int i=0; i<n; i++) roomPq.push(i); // It will hold room numbers of all the rooms that are free/empty. Initially all rooms are empty

        unordered_map<int,int> mp; // storing the number of meets hosted by each room

        sort(meetings.begin(), meetings.end()); // sorting to start scheduling room squencially 

        for(auto it: meetings){
            int start=it[0], end=it[1];

            while(!timePq.empty() && timePq.top().first<=1LL*start){
                roomPq.push(timePq.top().second); // making all those rooms free, whose endTime <=startTime

                timePq.pop();
            }

            if(!roomPq.empty()){

                timePq.push({1LL*end, roomPq.top()});
                
                mp[roomPq.top()]++;
                roomPq.pop();
            }
            else{
                ll currEnd=timePq.top().first; int idx=timePq.top().second;
                timePq.pop();
                ll duration = 1LL*(end-start);
                ll endtime=currEnd+duration;
                timePq.push({endtime, idx});

                mp[idx]++;
            }
        }

        int maxi=0, minidx=n;

        for(auto it: mp){
            if(it.second>maxi){
                maxi=it.second; 
                minidx=it.first;
            }
            else if(it.second==maxi){
                minidx=min(minidx, it.first);
            }

            // cout<<it.first<<" -> "<<it.second<<endl;
        }

        return minidx;
    }
};
