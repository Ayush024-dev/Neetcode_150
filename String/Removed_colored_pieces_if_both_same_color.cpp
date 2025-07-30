// leetcode link: https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/description/

/*
There are n pieces arranged in a line, and each piece is colored either by 'A' or by 'B'. You are given a string colors of length n where colors[i] is the color 
of the ith piece.

Alice and Bob are playing a game where they take alternating turns removing pieces from the line. In this game, Alice moves first.

Alice is only allowed to remove a piece colored 'A' if both its neighbors are also colored 'A'. She is not allowed to remove pieces that are colored 'B'.
Bob is only allowed to remove a piece colored 'B' if both its neighbors are also colored 'B'. He is not allowed to remove pieces that are colored 'A'.
Alice and Bob cannot remove pieces from the edge of the line.
If a player cannot make a move on their turn, that player loses and the other player wins.
Assuming Alice and Bob play optimally, return true if Alice wins, or return false if Bob wins. 
*/

// So we are given a string of colores and there are two distinct values: A and B. Now alice can only remove a pile if current pile color is A and both the
// neighbours must also have A -> a set of "AAA", then Alice can reomove the mid A, on which she is currently. Similarly Bob can remove a mid 'B' from a set of "BBB"


// So we just need to count the different pairs of "AAA" and "BBB" and if in someone's turn (whether Alice or Bob), he/she isn't able to pick up and remove any pile, he/she loses.
// Now ( This hint helped me btw ) how many As can Alice remove if the string is "AAAAAA" ? she can remove -> (AAA){index 0-2) or {index 1-3} or {index 2-4} or 
// {index 3-5} any more no....so 4 As she can remove. What if there are 5 As stacked together then? Then she could remove 3 As...
// Similarly we will notice that if there are n A's stacked together, then Alice can remove n-2 As or showing she can play for n-2 more times.

//Similarly if there are n Bs stacked together -> Bob can remove n-2 of that or Bob can play of n-2 more times. So this is what we need to count.

// We will store the count of number of As and Bs removable. Now as per turn both the players will start removing the characters. If someone is not able to, he/she loses. Simple.
// Check code: _|
class Solution {
public:
    bool winnerOfGame(string colors) {
        vector<int> count(2, 0);
        int curr=0;
        int n=colors.size();
        for(int i=0; i<n; i++){

            if(i==0 || colors[i]!=colors[i-1]){

                if(curr>=3){
                    
                    if(i>0){
                        if(colors[i-1]=='A') count[0]+=(curr-2);
                        else count[1]+=(curr-2);
                    }
                }

                curr=1;
            }
            else if(i>0 && colors[i]==colors[i-1]){
                curr++;
            }
        }

        if(curr>=3){
            if(colors[n-1]=='A') count[0]+=(curr-2);
            else count[1]+=(curr-2);
        }


        bool win=false;

        while(true){
            
            if(!win){
                if(count[0]==0) return win;

                count[0]--;
                win=true; 
            }
            else{
                if(count[1]==0) return win;

                count[1]--;
                win=false;
            }

        }

        return win;
    }
};


