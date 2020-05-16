#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED
#include "Node.h"
#include<vector>
#include <fstream>

class Trie
{
    private:
        Node *trieTree;


    public :
        Trie();
        void InsertWord(const char*, string, string, string);
        Node* SearchMe(const char*);
        Node* Search(Node*,const char*);
        void DeleteWord(const char*, string);
        int count;

};
#endif // TRIE_H_INCLUDED
