// Simple question, We just need to return the kth largest number in an array. Basic way is to sort array everytime a new character is added and then iterate over it to get the kth largest number. But the method is 
// slow. What if it could sort itself taking less time and return us the required? ....Yes we could use a priority_queue to store characters. But a pq could only provide largest or smallest of the lot, how to get the 
// kth largest? Well the kth largest is the smallest number if taken from back k at a time, right...So just store k numbers in a min heap pq and when the size of the pq >k pq.pop()...in this way we will always have
// access to the kth largest number in the array. Now here is the code: -
class KthLargest {
public:
    int K;
    priority_queue<int> pq;
    KthLargest(int k, vector<int>& nums) {
        

        for(auto it: nums) pq.push(-1*it);
        K=k;
    }
    
    int add(int val) {
        pq.push(-1*val);

        while(pq.size()>K){
            pq.pop();
        }

        return -1*pq.top();
    }
};
