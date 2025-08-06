// Leetcode link: https://leetcode.com/problems/range-sum-query-mutable/description/

//⭐Introduction to Segment Trees⭐
// We divide the whole array into multiple segments, get the answer for each segment and acculmate it to get the answer
// for other segment. 

// If a root node is at index=i, then it's left child will be at index 2*i+1 and right child will be at index 2*i+2.
// Segment Tree is a balanced binary tree, it means, no two child nodes a node will have a height difference of >1.
// Height of a segment tree is log2(N) where N is the size of given array.
// Always declare segment tree of size 3*N or 4*N to prevent runtime errors.

// Time complexity of building segment Tree: O(N) of updating : O(logN) and sum=O(N)
// Space complexity of building segment Tree: O(4*N) + recusion stack space = O(2* log2(N));

// Check code :
class NumArray {
public:
    vector<int> segTree;
    int sz;
    void BuildTree(vector<int> &nums, int i, int l, int r){
        int n=segTree.size();
        if(i>=n) return;
        if(l==r){

            segTree[i]=nums[l];

            return;
        }

        int mid=l+(r-l)/2;

        BuildTree(nums, 2*i+1, l, mid);
        BuildTree(nums, 2*i+2, mid+1, r);

        segTree[i]=segTree[2*i+1]+segTree[2*i+2];
    }

    void updateTree(int val, int i, int l, int r, int idx){
        int n=segTree.size();
        if(i>=n) return ;

        if(l==r){
            segTree[i]=val;

            return;
        }

        int mid=l+(r-l)/2;

        if(idx<=mid) updateTree(val, 2*i+1, l, mid, idx);

        else updateTree(val, 2*i+2, mid+1, r, idx);

        segTree[i]=segTree[2*i+1]+segTree[2*i+2];
    }

    int getSum(int reqL, int reqR, int i, int l, int r){
        int n=segTree.size();
        if(i>=n) return 0;
        if((l>reqR) || (r<reqL)) return 0;

        if(l>=reqL && l<=reqR && r<=reqR){
            return segTree[i];
        }

        int mid=l+(r-l)/2;

        int sum=0;

        int sumL=getSum(reqL, reqR, 2*i+1, l, mid);
        int sumR=getSum(reqL, reqR, 2*i+2, mid+1, r);

        sum=sumL+sumR;

        return sum;
    }
    NumArray(vector<int>& nums) {
        int n=nums.size();

        sz=n;

        segTree.resize(4*n, 0);

        BuildTree(nums, 0, 0, n-1);
    }
    
    void update(int index, int val) {
        updateTree(val, 0, 0, sz-1, index);
    }
    
    int sumRange(int left, int right) {
        return getSum(left, right, 0, 0, sz-1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
