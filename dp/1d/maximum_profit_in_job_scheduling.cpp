// leetcode link: https://leetcode.com/problems/maximum-profit-in-job-scheduling/description/

/*We are given three arrays denoting a particular thing about a job-> startTime array to view the startTime of a job, endTime to view the end Time and profit to show
the profit from the job. We need to maximum problem by doing one job at a time. We can't do overlapping jobs*/

/*🧠 Key Patterns & Concepts:
Weighted Interval Scheduling:
Classic DP problem where we must select intervals with maximum weight (profit) and no overlaps.

DP State Definition:
Let dp[i] = max profit achievable starting from job i.

Transition:
For each job at index i, we have two choices:

Skip the job → dp[i] = dp[i + 1]

Take the job → dp[i] = profit[i] + dp[next_non_conflicting_job]

*/

/* 🔍 Core Optimization Pattern:
When a DP state transition depends on a future/next state that satisfies a condition (like startTime[j] >= endTime[i]), we can optimize using binary search.

Here, to find next_non_conflicting_job, we use:
lower_bound(startTimes.begin(), startTimes.end(), jobs[i].end)

This converts O(n^2) recursion into O(n log n) using:

Sorted state space

Binary search for transitions */

/*✅ When to Use This Pattern:
You're solving a DP problem with:

Decisions: pick/not-pick (like subset problems)

Constraints: time-based, interval-based

State transitions that require locating the next/previous valid state according to a condition (e.g. "next job that starts after current ends")

Common in:

Job Scheduling Problems

Weighted Activity Selection

Longest Chain Problems

Events with deadlines or cooldowns*/

class Solution {
public:
    int solve(int i, vector<vector<int>> &jobs, vector<int> &starts, vector<int> &dp){

        int n=jobs.size();

        if(i==n) return 0;
        
        if(dp[i]!=-1) return dp[i];

        int npick=solve(i+1, jobs, starts, dp);

        int pick=0;

        int idx=lower_bound(starts.begin(), starts.end(), jobs[i][1])-starts.begin();

        pick=jobs[i][2] + solve(idx, jobs, starts, dp);

        return dp[i] = max(npick, pick);
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<vector<int>> jobs;

        int n=startTime.size();

        vector<int> starts;

        for(int i=0; i<n; i++){
            jobs.push_back({startTime[i], endTime[i], profit[i]});

            starts.push_back(startTime[i]);
        }

        sort(jobs.begin(), jobs.end());

        sort(starts.begin(), starts.end());

        vector<int> dp(n,-1);

        return solve(0, jobs, starts, dp);
    }
};
