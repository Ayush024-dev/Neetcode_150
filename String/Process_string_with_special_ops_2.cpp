// leetcode link: https://leetcode.com/problems/process-string-with-special-operations-ii/description/

// Problem description: We are given a string with some set of character in it. These characters have some rules which we have to follow to create a new string.
// Now if the character in the given string is a letter -> append it into original string
// if the character  is '*' -> remove the last character if new_string.length() > 0
// if the character is '%' -> reverse the new string
// else if character is '#' -> append the new_string to itself.
// We are also given k and we need to return the kth index character from the final string.

// This is a simulation problem and if the constrains are managable, just perform the simulation and get the answer. However here that's not the case. K can go upto
// 1e15 and there's no way we can store 1e15 characters or even compute those characters. So how to do it. 
// So in such type of simulation problem, rather than performing the simulation, we try to chase the target and the target in this case is kth index. 

// So first we will see if it's possible to get the kth index or not. We will calculate the size of the final new_string by performing the size changes due to 
// each operation. If we get '*' sz-- else if '%' no change in sz else if '#' sz*=2 else sz++ (for letter appending)

// After we get and store the size of the final string in a variable say sz, if(k>=sz) return '.' (not possible) Here k is in 0 index form and sz is size.

// If that's not the case, then I thought of 2 ways. One is see when the size of the final_string > k and from that point try to backtract to final the particular
// character. But I realized that won't help me because this type of approach helps when you are sure the once kth character hits, it will stay the same. No further operation
// can change it. True for problem where we just keep appending original string or reverse string to itself where we get new set of characters and inner characters remain safe.
// But not here, because here previous characters can change based on further operations -> reverse can change positions, and remove might remove the character we are trying to track.

// So I took the second and more realible approach -> is the backtrack from the very end, after all the operations are done. For this I started the sz (size of final_string)
// k.
// Base case was if(sz-k==1) // means I am stading at the kth index of the final string and if s[i] is a letter, I return that letter because that letter was pushed at that position.
// else I keep reversing the operations and maintaining the relative changes in values of sz and k. In this way I was able to return the correct value. Check code :-

#define ll long long
class Solution {
public:
    char processStr(string s, long long k) {
        ll sz=0; // To store the length of the final string

        for(char ch: s){

            if(ch=='*'){
                if(sz>0) sz--;
            }
            else if(ch=='#') sz*=2;
            else if(ch=='%') continue;
            else sz++;
        }

        if(k>=sz) return '.'; // if final string doesn't have kth index 

        int n=s.length();

        for(int i=n-1; i>=0; i--){
            if(sz-k==1){ // if I am standing at the kth index of the final string
                if(s[i]!='*' && s[i]!='#' && s[i]!='%') return s[i]; // and s[i] is a letter, return that letter
            }
            // simple manipulation and operation reverse. 
            if(s[i]=='*') sz++; 

            else if(s[i]=='%') k=sz-k-1;

            else if(s[i]=='#'){

                if(k>=sz/2) k-=(sz/2);

                sz/=2;
            }

            else sz--;
        }

        return '.';
    }
};
