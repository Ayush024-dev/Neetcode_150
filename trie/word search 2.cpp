// leetcode link: https://leetcode.com/problems/word-search-ii/

// problem is very easy to understand, we are given a vector of words and a 2d grid board of characters. Out of all the characters in words, how many can you create with grid, going either horizontly or vertically.

// Now one approach is similar to word search 1, for each word in words, do the dfs on the grid, and if you can found the word, insert it into the array ans.
// But this one is a long approach, Here going to each word TC: O(n) and dfs will be O(nm), therefore total TC: o(m*n2)---> Will give TLE
// So How to optimize...
// We need to add different words and check them right....So we can use trie...Aur questions krna bhai...abhi pta nhi kase---> But trie use krna hai


// So build a trie data structure, and implement the insert function and insert all the words from the string array. Now go to each cell of the grid
// if the root of our trie has a pointer to that character, go forward and do dfs, else continue
// Even in dfs, if any of the children node is null, that means that child isn't forming any word hence continue..
//Look at the code
class Solution {
    struct trieNode{
        bool isEndofWord=false;

        string word=""; // To store the final word in the ans array

        vector<trieNode*> children; // 26 sized array representing each character of english letter. If there a pointer from a particular index of this array, 
                                    // it means the that indexed character is a part of a word which was stored in this trie

        trieNode(){
            children=vector<trieNode*> (26, nullptr); // way to initiallize the array.
        }
    };

    trieNode* getNewNode(){
        trieNode* newnode= new trieNode;

        return newnode;
    }

    void insert(string word, trieNode* root){
        trieNode* crawler=root; // crawler pointer initialized to root.

        int n=word.length();

        for(int i=0; i<n; i++){
            int idx=word[i]-'a'; // Here we are converting char to int index

            if(crawler->children[idx]==nullptr) crawler->children[idx]=getNewNode(); // In insert function if the children[idx] is null, means till now it's not the part of any word,
                                                                                     // Now it's a part of a word, hence point a new node to it.     

            crawler=crawler->children[idx]; // move to child node
        }
        crawler->isEndofWord=true; // At the last node, as the word has ended, mark this true
        crawler->word=word; // Insert the word to easy access
    }

    //-----End of Trie functions-----//
    
    // Direction vector
    vector<pair<int,int>> dirs={{-1,0},{0,-1},{0,1},{1,0}};

    // Get word function 
    void findword(int x, int y, vector<vector<char>>& board, trieNode* root, vector<string> &ans){
        int n=board.size(), m=board[0].size();
        if(root->isEndofWord==true){
            ans.push_back(root->word);
            cout<<"overHere"<<endl;
            root->isEndofWord=false; // Even after this word is added, it may be a substring of a longer words in the same path. For example, you found "Bat"
                                    // and in the same path you have Batte, now as you have found "Bat", make this as false now so that you can move forward
                                    // in the next iteration
        }
        char temp=board[x][y];
        board[x][y]='$';

        for(auto dir: dirs){
            int newx=x+dir.first;
            int newy=y+dir.second;

            if(newx<0 || newx>=n || newy<0 || newy>=m || board[newx][newy]=='$'|| root->children[board[newx][newy]-'a']==nullptr) continue;

            findword(newx, newy, board, root->children[board[newx][newy]-'a'], ans);
        }

        board[x][y]=temp;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        
        trieNode* root=getNewNode();

        for(auto it: words){
            insert(it, root);
        }

        int n=board.size(), m=board[0].size();
        vector<string> ans;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int idx=board[i][j]-'a';

                if(root->children[idx]==nullptr) continue;

                findword(i, j, board, root->children[idx], ans);
            }
        }

        return ans;
    }
};
