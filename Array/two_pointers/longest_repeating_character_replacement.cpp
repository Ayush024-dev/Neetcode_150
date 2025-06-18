// leetcode link: https://leetcode.com/problems/longest-repeating-character-replacement/description/

// So Here we can convert any alphabet to any other alphabet character. We can do this k times and using this we need to get the length of the maximum frequency.
// Our approach is to keep a record of the maximum frequecy of a character in the current window and the number of characters to be replaced will be :

// j-i+1-maxFrequecy. If this is >k, Remove the ith character and recheck. Check the max length afterwards.

// code:-
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n=s.length();

        vector<int> freq(26, 0);

        int maxFrq=0;

        int i=0, j=0;
        int maxi=0;
        while(j<n){
            freq[s[j]-'A']++;
            maxFrq=max(maxFrq, freq[s[j]-'A']);

            while(j-i+1-maxFrq>k){
                freq[s[i]-'A']--;

                i++;
                for(auto it: freq) maxFrq=max(maxFrq, it); // Getting the maximum frequency again.
            }

            maxi=max(maxi,j-i+1);
            j++;
        }

        return maxi;
    }
};
