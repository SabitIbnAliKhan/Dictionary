#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include<iostream>


using namespace std;

//Constants
const int ALPHABET_SIZE = 26;
const int CASE = 'a';


//Data Packet
class Node
{
    public:
        Node *parent = nullptr;
        Node *children[ALPHABET_SIZE] = {};
        int occurrences = 0;
        bool isWord = false;
        string details;
        string synonyms;
        string antonyms;
        //int numberOfWords = 0;

};
#endif
