// leetcode link: https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/?envType=daily-question&envId=2025-06-15

// The problem is easy, it's just that I learned a new thing today. If you want to assign a negative number as char to a char variable, always assign it's int value
// like: char a=-1 and not char a='-1'. 

// Here is the code; -
#define ll long long
class Solution {
public:
    int maxDiff(int num) {
        string no=to_string(num);
        
        char mini, maxi;

        char minRep=-1;



        for(int i=0; i<no.length(); i++){
            if(no[i]!='9') {
                maxi=no[i];
                break;
            }
        }

        string maxNo, minNo;

        if(no[0]=='1'){
            for(int i=1; i<no.length(); i++){
                if(no[i]!='0' && no[i]!='1'){
                    minRep=no[i];
                    // if(minRep=='1') cout<<"Yha ho rhi upar"<<endl;
                    break;
                }
            }
        mini='0';
        }
        else if(no[0]!='1'){
            minRep=no[0];
            // cout<<"Yha ho rhi niche"<<endl;
            mini='1';
        }
       
        // cout<<minRep<<endl;
        bool noNeed=false;

        if(minRep==-1){
            minNo=no;
            noNeed=true;
        }

        for(int i=0; i<no.length(); i++){

            if(no[i]==maxi){
                maxNo.push_back('9');
            }
            else maxNo.push_back(no[i]);

            if(noNeed==false){
                if(no[i]==minRep){
                    minNo.push_back(mini);
                }
                else minNo.push_back(no[i]);
            }

        }

        

        ll maxNoInt=stoll(maxNo);
        ll minNoInt=stoll(minNo);

        return (maxNoInt-minNoInt);
    }
};
