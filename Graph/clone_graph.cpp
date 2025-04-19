//Here we need to deep copy the graph, means for each node, we need to form a copy node and in a way generate a ctrl+c version of original graph. Can we just return the actual graph,...is actual a copy?
//No...so a let me do the thinking please.
//okay, copy of all the node, So copy of the first node, and then copy of all it's neighbors and so on. First let's see the definition of the Node class-
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
// So here we have val and adj list for each node and it's given the graph is undirected. So we need to store those nodes already copied somewhere, to avoid re coping. We can use a hashmap to store the copy of node.
// Map node -> copy of node. If a copy already exist return it. Else insert node->copy and then for each neighbors in node->neighbors, push_back into copy->neighbors, the copy of the each neighbors. And we are done.

// Here is the code: 

class Solution {
public:
    Node* deepcopy(Node* node, unordered_map<Node*, Node*> & mp){
        if(mp.find(node)!=mp.end()) return mp[node]; // If node is already copied, return its copy

        Node* copy = new Node(node->val); // Else form its copy and store in the map.

        mp[node]=copy;

        for(auto nei: node->neighbors){
            copy->neighbors.push_back(deepcopy(nei,mp)); // Here we are pushing_back the copies of the neighbors of node into copy->neighbors. 
        }

        return copy; // Return the copy.
    }
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;
        unordered_map<Node*, Node*> mp;

        return deepcopy(node, mp);
    }
};
