// leetcode link: https://leetcode.com/problems/design-add-and-search-words-data-structure/description/

/*
Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:

WordDictionary() Initializes the object.
void addWord(word) Adds word to the data structure, it can be matched later.
bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.
*/

// Use recursion to find whether the particular word can be present in the trie or not in case of characters being ".", else all code same. Since there were "." present
// going with sets would be tough, hence used trie

class WordDictionary {
    struct trieNode{
        bool isEndofWord=false;
        vector<trieNode*> children;

        trieNode(){
            children = vector<trieNode*>(26, nullptr);
        }
    };

    trieNode* getTrieNode(){
        trieNode* newnode=new trieNode();

        return newnode;
    }
public:
    bool SearchWordInTrie(string word, trieNode* root){
        int n=word.length();

        trieNode* crawler=root;

        for(int j=0; j<n; j++){
            

            if(word[j]!='.'){ //Use original code
                int idx=word[j]-'a';

                if(crawler->children[idx]==nullptr) return false; 

                crawler=crawler->children[idx];
            }
            else{
                for(int i=0; i<26; i++){ // checking each character word formation possiblites. 
                    if(crawler->children[i]==nullptr) continue;

                    if(SearchWordInTrie(word.substr(j+1),crawler->children[i])==true) return true;
                }

                return false; // After iterating throughout the alphabets, it no match return false
            }
        }

        return crawler->isEndofWord;
    }
    trieNode* root;
    WordDictionary() {
        root=getTrieNode();
    }
    
    void addWord(string word) {

        trieNode* crawler=root;
        int n=word.length();

        for(int i=0; i<n; i++){
            int idx=word[i]-'a';

            if(crawler->children[idx]==nullptr) crawler->children[idx]=getTrieNode();

            crawler=crawler->children[idx];
        }

        crawler->isEndofWord=true;
    }
    
    bool search(string word) {
        
        return SearchWordInTrie(word, root);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
