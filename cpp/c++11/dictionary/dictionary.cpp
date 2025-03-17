#include <string>
#include <iostream>
#include <vector>
#include <cassert>

struct Node{
    char key;
    bool isWord;
    Node* children[26];
    Node(): key('\0'), isWord(false){
        for(int i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }

    Node(char key, bool isWord): key(key), isWord(isWord){
        for(int i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }

    ~Node(){
        for(int i = 0; i < 26; i++){
            delete children[i];
            
        }
    }
};


class Dictionary{
private:
    Node* root;
    void recInsert(std::string& word,int readInx, Node* current){
       if(word[readInx] == '\0'){
           current->isWord = true;
           return;
       }
        
        if(current->children[word[readInx] - 'a'] == nullptr){
            current->children[word[readInx] - 'a'] = new Node(word[readInx], false);          
        }
        recInsert(word, readInx + 1, current->children[word[readInx] - 'a']);
    }lass Solution {

public:
    
    bool isMatch(string s, string p) {
      
      return isMachRec(s,0,p,0);
    }

…        if(i == s.size() && j < p.size())//s finished p not
        {
           for (;j < p.size();j++){
            if(p[j] != '*'){
                return false;
            }
           }
            return true;
        }


    void print(Node *current, std::string word){
        if(current == nullptr){
            return;
        }
        std::string newWord = word + current->key;
        if(current->isWord){
           std::cout<< newWord << std::endl;
        }
       
        for(int i = 0; i < 26; i++){
            if(current->children[i] != nullptr){
                print(current->children[i], newWord);
            }
        }
        
    }

    


    bool findRec(std::string& word, int readInx, Node* current){
       
       if(current == nullptr || word[readInx] != current->key){
        return false;
       }

       if(readInx == word.size() - 1){
           return current->isWord;
       }

       return findRec(word, readInx + 1, current->children[word[readInx + 1] - 'a']);       
    }

public:
    Dictionary(): root( new Node()){}
    Dictionary(Dictionary& other) = delete;
    Dictionary& operator=(Dictionary& other) = delete;
    ~Dictionary(){
        delete root;
    }

    void insert(std::string& word){
       if(word[0] == '\0'){
           return;
       }
       
       if(root->children[word[0]-'a'] == nullptr){
           root->children[word[0]-'a'] = new Node(word[0], false);
       }
    recInsert(word, 1, root->children[word[0]-'a']);
    }

    void printDictionary(){
        print(root, "");
    }


    bool find(std::string& word){
       return findRec(word,0,root->children[word[0]-'a']);
    }  


};


int main(){

    Dictionary dict;
   std::vector<std::string> words = {"hello", "hellow", "yyyello"};
   std::string unUsed =  std::string("world");
   
  

   for(auto word : words){
    dict.insert(word);
   }
    
    
    dict.printDictionary();

    assert(dict.find(words[0]));
    assert(dict.find(words[1]));
    assert(dict.find(words[2]));
    assert(!dict.find(unUsed));

    return 0;
}