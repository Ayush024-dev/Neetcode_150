// Question is about simply storing and retriving the values, but this time we need 2d map to store it. As key->timestamp->value , so to find a value at a particular time of a particular key mp[key][time];

// Main concept is about iterator and pointer, whenever we iterate over map, array, vectors, sets etc, we use an iterator which acts like a pointer but it isn't a pointer. Instead it just moves over the values of the
// data structure and can access them as well. But as you may have noticed we cannot change values in any data structure using an iterator, because it just iteraters. 
// Now in a map, it iterator points to map object which is nothing but pair. *it returns a pair but *it.first or second is not correct because this means you want values at it's first or second, but there isn't any 
// first or second for an it. But yes as mentioned b4, you can access the values using it anytime:- it->first, and it->second. So remember this. Here is the code for your reference: -
class TimeMap {
public:
    map<string, map<int, string>> mp;
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        mp[key][timestamp]=value;
    }
    
    string get(string key, int timestamp) {
        if(mp.find(key)==mp.end()) return "";

        auto it=mp[key].upper_bound(timestamp);

        if(it==mp[key].begin()) return "";

        --it;

        return it->second;
    }
};

