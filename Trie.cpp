#include"Trie.h"


//constructor
//__________________________________________________________________________________
Trie::Trie()
{
    trieTree = new Node;
    count = 0;
}

//__________________________________________________________________________________




//Insertion
//__________________________________________________________________________________
void Trie::InsertWord(const char *word, string meaning, string syn, string ant)
{
    Node *curr = trieTree; //root

    while(*word != '\0')
    {
        if(curr->children[*word - CASE] == nullptr)
        {
            curr->children[*word - CASE] = new Node();
            curr->children[*word - CASE]->parent = curr;
        }

        curr = curr->children[*word - CASE];
        ++word;
    }

    ++curr->occurrences;
    if(curr->occurrences==1)
       {
            count++;
       }
    curr->isWord = true;
    curr->details = meaning;
    curr->synonyms = syn;
    curr->antonyms = ant;
}

//__________________________________________________________________________________




//Search
//__________________________________________________________________________________
Node* Trie::SearchMe(const char *word)
{
    Node *curr = Search(trieTree,word);
    return curr;
}



Node* Trie::Search(Node *Tree, const char *word)
{
    while(*word != '\0')
    {
        if(Tree->children[*word - CASE] != nullptr)
        {
            Tree = Tree->children[*word - CASE];
            ++word;
        }
        else return nullptr;

    }
    return (Tree->isWord) ? Tree : nullptr;
}


//__________________________________________________________________________________




//Delete
//__________________________________________________________________________________
void Trie::DeleteWord(const char* word, string str)
{
    Node *curr = Search(trieTree, word);

    if(curr != nullptr)
        {

            //writing in memory
            string line;
            ifstream inFile("Dictionary.txt");
            ofstream out("OutFile.txt");
            while( getline(inFile,line) )
            {
                if(line != str)
                if(line != curr->details)
                if(line != curr->synonyms)
                if(line != curr->antonyms)
                    out << line << "\n";
            }
            inFile.close();
            out.close();
            remove("Dictionary.txt");
            rename("outfile.txt","Dictionary.txt");
            //


            //deletes from console
            count--;
            curr->isWord = false;
            --curr->occurrences;
            Node *parent = nullptr;
            bool IsLeaf = true;

            for(int i=0; i<ALPHABET_SIZE; i++)
            {
                if(curr->children[i]!=nullptr)
                {
                    IsLeaf = false;
                    break;
                }
            }

            while(curr->parent != nullptr && IsLeaf && (!curr->isWord))
            {
                parent = curr->parent;
                for(int i=0; i<ALPHABET_SIZE; i++)
                {
                    if(parent->children[i] == curr)
                    {
                        parent->children[i] = nullptr;
                        delete curr;
                        curr = parent;
                    }
                    else if(parent->children[i] != nullptr)
                    {
                        IsLeaf = false;
                        break;
                    }
                }
            }
        }
        else
            cout<<"Word is not here"<<endl;
}


//__________________________________________________________________________________
