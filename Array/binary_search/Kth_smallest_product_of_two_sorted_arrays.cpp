// leetcode link: https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/description/?envType=daily-question&envId=2025-06-25

// refer editorial:-
#define ll long long
class Solution {
public:
    ll getOrder(vector<int> &nums1, vector<int> &nums2, ll midP){
        int n=nums2.size();
        ll order=0;

        for(int i=0; i<nums1.size(); i++){

            

            if(nums1[i]>=0){
                int l=0;
                int r=n-1;
                int m=-1;
                while(l<=r){
                    int mid=l+(r-l)/2;
                    
                    if((ll)((ll)nums1[i]*(ll)nums2[mid])<=midP){
                        m=mid;
                        l=mid+1;
                    }
                    else r=mid-1;
                
                }

                order+=(ll)(m+1);
            }
            else{
                int l=0, r=n-1;
                int m=n;
                
                while(l<=r){
                    int mid=l+(r-l)/2;

                if((ll)((ll)nums1[i]*(ll)nums2[mid])<=midP){
                    m=mid;
                    r=mid-1;
                }
                else l=mid+1;
                }

                order+=(ll)(n-m);
            }
        }

        return order;
    }
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        
        ll s=-1e10;
        ll e=1e10;
        ll res=0;
        while(s<=e){
            ll mid=s+(e-s)/2;

            ll order=getOrder(nums1, nums2, mid);

            if(order>=k){
                res=mid;
                e=mid-1;
            }
            else s=mid+1;
        }

        return res;
    }
};
