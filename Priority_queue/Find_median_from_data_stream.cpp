// qp link: https://leetcode.com/problems/find-median-from-data-stream/description/

// simple explanation of the problem: we would continously add numbers to a data structure. At any point you need to tell the median of the structure so far. Now the naive
// approach is to simple store all these numbers in an array or vector and whenever the median is required...sort it and get the median. But it's not efficient especially
// when the number of operations are huge. So what can be done? There are 2 approaches: -
/* *************************************************************Approach 1 ( Using multiset ) ******************************************************************** */

// So looking at the naive approach or even b4 that, one things sure I need to sort the array or any data struture if I want to get the median. So what if data structure 
// already sorts itself whenever a new element is added? Yes set can help in doing that. But the number are repeating in nature so we can use multiset.
// But there is another issue. Unlike array/vector, set or multisets or maps don't have an index. They are based on bst. So I cannot access the mid element just by calling
// the mid index. I need to iterate everytime...or do I have to..hmmm
// What if I initialize a pointer as st.begin() at the start and update it as the numbers are added in the set. Remember a pointer properly sticks to a position, so if the
// posititon moves so does the pointer. For example if the st={1,2} and pt pointer pointing at 2 and now I add 1 to it, the pt pointer will still point to 2. It's not gonna
// point to 1 just because now 1 is in the index 2 was b4. Rememeber set do not have indices. 
// Now We need to adjust this pointer after the addition of number. If I add a number >= mid pointer value, the number will always be placed at the right side of it else to
// the left side. Now if the size of the set becomes even after addition and the number added is >= mid value, mid++ else mid remain same
// Just the opposite behavior with the odd sized st. If the number added < mid then --mid othervise no change. Check this interview chat if you are confused: https://chatgpt.com/share/67fa2288-ad3c-8009-b8b7-95e4780476e0
// Now see the code: -
class MedianFinder {
public:
    multiset<int> st;
    multiset<int> :: iterator mid;
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        
        st.insert(num);

        if(st.size()==1){
            mid=st.begin();
        }
        else{
            if(st.size()%2==0){
                if(num>=(*mid)) ++mid;
            }
            else{
                if(num<(*mid)) --mid;
            }
        }
    }
    
    double findMedian() {
        
        if(st.size()%2!=0) return (double)(*mid);

        auto pre=prev(mid);

        return (double)((double)(*mid)+(double)(*pre))/2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

/* **************************************************************** Approach 2 ( Using Priority queue ) ******************************************************* */

// other way around to solve this question is using max and min heap. If our max heap stores the first half of elements and min heap stores the last half of it, then 
// we have access to largest of the first half and smallest of the second half. So now if the size is odd, return the top value of the largest sized heap, else return 
// average of both the top values. 
/*🧠 Core Idea:
Use two heaps:

Max-heap (left side) → holds the smaller half of numbers

Min-heap (right side) → holds the larger half of numbers

The invariant is:

The sizes of the heaps should differ by at most 1

All values in maxHeap ≤ all values in minHeap

Median is either:

Top of the larger heap (if odd count) because we are intentionally making maxheap.size()>=minheap.size() but not greater than minHeap.size() + 1.

Average of tops of both heaps (if even count) */
class MedianFinder {
public:
    //priority queue type
    priority_queue<int> maxHeap; // to store the first half of elements
    priority_queue<int, vector<int> , greater<int>> minHeap; // to store the last half of elements
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        
        if(maxHeap.empty() || num<=maxHeap.top()) maxHeap.push(num);
        else minHeap.push(num);

        if(maxHeap.size()>minHeap.size()+1){
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if(minHeap.size()>maxHeap.size()){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        
        if(maxHeap.size()-minHeap.size()==1) return (double)(maxHeap.top());

        return (double)((double)(maxHeap.top())+ (double)(minHeap.top()))/2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
