// qp link: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/description/
/* You are given a palindromic string s and an integer k.

Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.

Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.

 */
/*
Intuition
To find the k-th lexicographically smallest palindromic permutation of a given string, we must recognize that a palindrome is symmetric around its center. Therefore, the task reduces to generating all unique permutations of the first half of the palindrome, then mirroring it.

However, instead of generating all permutations (which would be too slow), we use combinatorics—specifically, multinomial coefficients—to efficiently count how many permutations are possible with the current character frequencies and use this to determine which character to pick at each step for the half-string.

Approach
Frequency Count:

Count the frequency of each character in the input string s using an array freq of size 26 (for lowercase English letters).
Half Frequency and Middle Character:

For a string to form a palindrome:
At most one character can have an odd frequency (this will be the middle character).
The rest of the characters must have even frequencies.
Construct a halfFreq array where each value is freq[i] / 2 and also store the middle character (if any).
Check Validity using Multinomial Coefficient:

Compute the total number of unique permutations possible using the characters in halfFreq.
If k is greater than this number, return "" as it's not possible to find the k-th permutation.
Build Left Half of Palindrome:

For each position in the left half of the palindrome:
Try placing each character (from 'a' to 'z') that is available in halfFreq.
Temporarily reduce its count and calculate how many permutations are possible with the remaining characters.
If the number of permutations is ≥ k, this character is correct for this position.
Otherwise, subtract that permutation count from k and backtrack by restoring the count.
Construct the Final Palindrome:

Concatenate the left half, the middle character (if exists), and the reverse of the left half to get the final palindrome.
Multinomial Coefficient Formula
For a multiset of items where:

total elements = n
counts of individual types = k1, k2, ..., kr
The total number of unique permutations is given by:

n! / (k1! * k2! * ... * kr!)

Alternatively, it can be calculated as a product of binomials:

C(n, k1) * C(n - k1, k2) * C(n - k1 - k2, k3) * ...

Binomial Coefficient Formula
To calculate C(n, k) (number of ways to choose k items from n):

C(n, k) = n! / (k! * (n - k)!)

This can be computed efficiently using:

C(n, k) = (n * (n - 1) * ... * (n - k + 1)) / (1 * 2 * ... * k)

Complexity
Time complexity:

Worst case per step: O(26 * 26) for 26 characters and checking permutations using multinomial → O(26^2 * n)
For n/2 positions in half of the palindrome → overall time complexity is approximately O(n * 26^2).
Space complexity:

We use frequency arrays of size 26 → O(1) (constant space).
*/
//step 1: find the freq array 
//step 2: find the half freq array if there is any odd freq then store it in middle variable 
//step 3: check if k > total permutation possible, if yes then return ""
//step 4: take the char one by one and find the multinominal coef of remaining
//step 5: if coef >= k take that char else skip that 
//step 6: ans is left + middle + rev(left)
class Solution {
public:
    typedef long long ll;
    int maxK = 1e6 + 1;

    //this is same as nCk formula 
    // we know nCk is n! / (k! * (n - k)!)
    // can be written as (n * (n - 1) * (n - 2) * ....... * (n - k + 1)) / (1 * 2 * 3 * ..... * k) 
    ll binomial(int n, int k){
        if(k > n) return 0;
        if(k > n - k) k = n - k;

        ll res = 1;
        for(int i = 1; i <= k; i++){
            res = res * (n - i + 1) / i;
            if(res >= maxK) return maxK;
        }
        return res;
    }

    // multinomial is n! / (k1! * k2! * k3!)
    // can we written as nCk1 * (n - k1)Ck2 * (n - k1 - k2)Ck3
    ll multinomial(vector<int>& halfFreq){
        int total = accumulate(halfFreq.begin(), halfFreq.end(), 0);

        ll res = 1;
        for(int i = 0; i < 26; i++){
            int cnt = halfFreq[i];
            res *= binomial(total, cnt);
            if(res >= maxK) return maxK;
            total -= cnt;
        }

        return res;
    }
    string smallestPalindrome(string s, int k) {
        // step1 storing freq
        vector<int> freq(26, 0);
        for(char c : s){
            freq[c - 'a']++;
        }

        // step 2 storing half and findng middle 
        string left = "", middle = "";
        vector<int> halfFreq(26, 0);
        int halfLen = 0;
        for(int i = 0; i < 26; i++){
            if(freq[i] % 2 == 1){
                middle = i + 'a';
            }
            halfFreq[i] = freq[i] / 2;
            halfLen += halfFreq[i];
        }

        //step 3: checking if k > total permutation -> if yes then no ans -> return ""
        ll totalPermutation = multinomial(halfFreq);
        if(k > totalPermutation) return "";

        // step 4: take one char at a time
        for(int i = 0; i < halfLen; i++){
            for(int j = 0; j < 26; j++){
                if(halfFreq[j]){
                    halfFreq[j]--;
                    ll permutation = multinomial(halfFreq);

                    //step 5
                    if(permutation >= k){
                        left += (j + 'a');
                        break;
                    }
                    else{
                        k -= permutation;
                        halfFreq[j]++;
                    }
                }
            }
        }

        //step 6
        string right = left;
        reverse(right.begin(), right.end());
        return left + middle + right;
    }
};
