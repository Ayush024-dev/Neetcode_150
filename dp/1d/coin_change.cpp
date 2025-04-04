// qp link: https://neetcode.io/problems/coin-change
// This is a basic dp on subsequence approach, whether you want to take the particular denomination value or not. What is the case where this isn't possible? When the amount
// becomes negative after any operation. If the amount becomes negative we return INT_MAX or 1e9. Now when we are returning such high values to a variable, we must
// never add anything to it as it would lead to overflow and INT_MIN can take it's place. Instead check whether res is valid and if yes, add 1 to res while comparing with
// mini. Here is the code: -
class Solution {
public:
    int solve(vector<int>& coins, int amt, vector<int>& dp){
        if(amt == 0) return 0;
        if(amt < 0) return INT_MAX;

        if(dp[amt] != -1) return dp[amt];

        int mini = INT_MAX;

        for(int coin : coins){
            int res = 1+solve(coins, amt - coin, dp);
            if(res != INT_MAX){
                mini = min(mini, res);
            }
        }

        return dp[amt] = mini;
    }

    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        vector<int> dp(amount + 1, -1);

        int ans = solve(coins, amount, dp);
        return (ans == INT_MAX ? -1 : ans);
    }
};
