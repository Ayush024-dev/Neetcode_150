// leetcode link: https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/description/?envType=daily-question&envId=2025-07-04
// We are given a starting string st="a", ops array (binary) and ll k
// We have to construct the full string using the types of ops defined by ops array and return the kth character or st[k-1]. 

// One approach is to do as the question says, but look at the constraint bitch...it's 1e14 for k, so basically iteration types simulation sol is not possible, I mean
// won't give us answer. It is possible, but...Ghada majdoori hogi voh..

//Toh what is the optimal approach? In such cases when the strings or arrays are very long, we are usually asked about some parts rather than generating the whole fucking
// array or string, which in this case is finding kth character rather than generating that string, so we must focus and follow kth character

// Now if ops[i]=0 -> we have to merge the same string to itself but if ops[i]=1, we have to move every character to it's next and then merge this new
// string to original string. For example if st="c" and ops[i]=1, new st= "cd", where d comes after c. 

// So despite the ops, one thing is sure, after every ops the length is getting twice. So If I take an example here k=10 and ops=[0,1,0,1]
// So st="a", len=1 and then ops[0]-> now st="aa" and len=2
// Then ops[1]=1, so new st="aabb" -> len=4, then ops[2]=0 (same st merging) = "aabbaabb" len=8 and finally ops[3]=1 (next char st merging)
// st="aabbaabbbbccbbcc" len=16...So did you see, length gets doubled after each ops

// len-> 1----2--------4--------------8----------10--------------16
// ops ->  0       1          0                     1
// Here kth character will be either a power of 2 or a number between these nos, for example in our case k=10, which comes in between 8-16, as every 
// next part of the string is either same of one character ahead of the previous half set, we can easily map characters to the right of the boundary
// with the left of the boundary. The boundary nos here are power of 2. So 10th character comes after boundary 8 and will match (10-8)th or 2nd character

// Now as 2 is a power of 2, to match it, just half it-> so it becomes 1
// Now 1st character = 'a' so return it.

// Now every char will either be equal to +1 to the character it came from, so we will also send the ops type with the k, to know
// whether we want same or +1 of the current character. It will be either 0 or 1. 
// Also take care of 'z' as 'z'+1 is not defined but in the question next character to 'z' is 'a'

// Here is the code: -
#define ll long long
class Solution {
public:
    int HighestBit(ll n){
        ll temp=n;

        int highestBit=0;
        int bitItr=0;
        

        while(temp){
            if((temp&1LL)){
                highestBit=bitItr;
            }

            temp>>=1LL;
            bitItr++;
        }


        return highestBit;
    }
    char solve(ll k, int cvr, vector<int> &ops){
        if(k==1){
            return 'a'+cvr;
        }

        int Hbit=HighestBit(k); // gets the left boundary of the number
        int cnt=__builtin_popcount(k); // finds out whether k is a power of 2 or not.

        if(cnt==1){
            if(Hbit>0) Hbit--; // if k is power of 2, we must look reduce Hbit, because these aren't their own left boundary.
            else Hbit=0; 

            char ch=solve(k/2, ops[Hbit], ops);

            if(ch=='z'){
                if(cvr==1) return 'a';
                else return 'z';
            }

            return ch + cvr;
        }
        else{
            ll left = 1LL << Hbit;
            ll val=k-left;
            
            char ch=solve(val, ops[Hbit], ops);

            if(ch=='z'){
                if(cvr==1) return 'a';
                else return 'z';
            }

            return ch + cvr;
        }
        
    }
    char kthCharacter(long long k, vector<int>& ops) {
        
        return solve(k, 0, ops);
    }
};

// Approach 2:-
#define ll long long
class Solution {
public:
    char kthCharacter(long long k, vector<int>& ops) {

        if(k==1) return 'a';
        
        int n=ops.size();

        ll length=1;

        int currops=-1;

        for(int i=0; i<n; i++){
            length*=2;

            if(length>=k){
                currops=ops[i];
                break;
            }
        }

        ll newk=k-length/2;

        char ch=kthCharacter(newk, ops);

        if(currops==0) return ch;

        if(ch=='z') return 'a';

        return ch+1;
    }
};
