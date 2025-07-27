// leetcode link: https://leetcode.com/problems/maximum-number-of-subsequences-after-one-inserting/description/

/*
You are given a string s consisting of uppercase English letters.

You are allowed to insert at most one uppercase English letter at any position (including the beginning or end) of the string.

Return the maximum number of "LCT" subsequences that can be formed in the resulting string after at most one insertion.

A subsequence is a non-empty string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
*/

// So here we have to insert 'L' or 'C' or 'T' and maximize the number of LCT subsequence out of a string. So if we just had to insert L, where would we insert? at the
// beginning right...because that would increase the number of L and hence LCT number would also increase.

// If we just had to insert T, similarly we would insert it at the back for the same reason. 

// But where could we insert C? anywhere in between. We would pre compute the number of Ls till a particular index and number of Ts from a particular index to the end
// string. How would this help us? well inserting C, we must know the number of Ls till the index we are inserting C into and the number of Ts from this index till end.

// Now adding C to different index will have different difference. We will get the max difference. 
// However for L and T, since we are adding them to only one position -> start or end, we have to cummlate the difference it causes when we take the total. 

// Now how to take the total? Simple -> we will only consider the letter 'C' to take the total, because with C we are certain of this order LCT. We will find the number of
// subsequence formed with the particular C at the centre and we will sum this for all Cs. In this way we will be able to find out the total number of LCT subsequnce in 
// the string. 
// We will also sum the difference caused in this total each time with the insertion of L and T. At the end we just have to take the maximum of all the three, that's 
// our max diff. Add to total and that's your answer.

// Check code; -
#define ll long long
class Solution {
public:
    long long numOfSubsequences(string s) {
        int n=s.length();

        ll total=0, maxDiff=0;

        vector<vector<int>> mp(n, vector<int> (2,0)); // To store the number of L, T till and from for every index

        int countL=0;

        for(int i=0; i<n; i++){
            if(s[i]=='L') countL++;

            mp[i][0]=(countL);
        }

        int countT=0;
        for(int i=n-1; i>=0; i--){
            if(s[i]=='T') countT++;

            mp[i][1]=(countT);
        }


        
        ll sumL=0, maxC=0, sumT=0; // sumL = total difference caused if L inserted in the front of string.
                                  // sumT = total difference caused if T inserted in the end of string.
                                  // maxC = maximum difference of all the difference when  C is inserted for all index
        for(int i=0; i<n; i++){

            if(s[i]!='C') { // if s[i] is not equal to C, we will not calculate total as we won't be sure about the order, what if there are some Ts before L and we are
              // counting them as well. Hence we will only check for maxC in this case.
                int l=0;
                if(i>0) l=mp[i-1][0];
                int t=mp[i][1];

                ll possible=1LL*l*1*t;

                maxC=max(maxC, possible);
            }

            else{            // Here we will do everything, check for difference caused by L and T, maxC and the total, because we can define the order here as C is present.
                int l=mp[i][0];
                int t=mp[i][1];

                total+=(1LL*l*1*t);

                sumL+=(1LL*1*1*t); // All the subsequecne from the new L , particular C and every T after that
                sumT+=(1LL*l*1*1); // All the subsequence from the new T, parituclar C and every L before it.
                maxC=max(maxC, 1LL*l*1*t); // all L before * all T after * particular new C insertion. 
            }


        }

        maxDiff=max(sumL, max(sumT, maxC)); // comparison because we will be doing one of those. Smajaha yaar..asan hai yahi to sawal hai...confuse mt hona isme

        return total + maxDiff;
    }
};
