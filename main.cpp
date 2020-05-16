#include<iostream>
#include<vector>
#include <fstream>
#include<stdlib.h>
#include<algorithm>
#include"Trie.h"
#include"Node.h"

using std::cout;
using std::endl;
using std::vector;



//Function Prototypes
//__________________________________________________________________________________
void InsertNewWord(Trie&);             //done
void DeleteWord(Trie&);                //done
void SearchWord(Trie&);                //done
void WriteToHistory(string);           //done
void ViewHistory();                    //done
void AddToFavList(string);             //done
void ShowFavList();                    //done
void Synonyms(Node*);                  //done
void Antonyms(Node*);                  //done
void NoOfWords(Trie&);                 //done
void ShowNoOfWords(Trie&);             //done
const char* convertString(string str); //done
//__________________________________________________________________________________




//Main
//__________________________________________________________________________________
int main()
{
    //declaration of variables
    vector<char> word;
    string str, meaning, synonyms, antonyms;
    Trie T;
    int no, ch;
    bool flag = true;

    //read from file
    ifstream theFile("No Of Words.txt");
    theFile >> no;
    theFile.close();

    ifstream inFile("Dictionary.txt");
    for(int i=0; i<no; i++)
    {
        getline(inFile,str);
        getline(inFile,meaning);
        getline(inFile,synonyms);
        getline(inFile,antonyms);
        T.InsertWord(convertString(str), meaning, synonyms, antonyms);
    }
    inFile.close();

    while(flag)
    {
        cout<<endl<<endl;
        cout<<" Dictionary Operations "<<endl;
        cout<<" -------------------------------------------- "<<endl;
        cout<<" 1. Search word for meaning. "<<endl;
        cout<<" 2. Insertion/Creation. "<<endl;
        cout<<" 3. Delete a word. "<<endl;
        cout<<" 4. View Favorite word list. "<<endl;
        cout<<" 5. View History. "<<endl;
        cout<<" 6. Show total number of words included. "<<endl;
        cout<<" 7. Exit "<<endl;
        cout<<" -------------------------------------------- "<<endl;
        cout<<" Enter your choice : ";
        cin>>ch;
        switch(ch)
        {
        case 1 :
            SearchWord(T);
            break;
        case 2 :
            InsertNewWord(T);
            break;
        case 3 :
            DeleteWord(T);
            break;
        case 4 :
            ShowFavList();
            break;
        case 5 :
            ViewHistory();
            break;
        case 6 :
            ShowNoOfWords(T);
            break;
        case 7 :
            flag = false;

        NoOfWords(T);
        }
    }
}
//__________________________________________________________________________________





//valid input checker & converter (string to char*)
//__________________________________________________________________________________
bool ValidInput(string word)
{
    int i=0;
    while(word[i])
    {
        if(!isalpha(word[i]))
            return false;
        i++;
    }
    return true;
}

const char* convertString(string str)
{
    const char *S = str.c_str();
    return S;
}
//__________________________________________________________________________________




//Insert
//__________________________________________________________________________________
void InsertNewWord(Trie &tree)
{
    system("cls");
    string word, temp, meaning, synonyms, antonyms;
    getline(cin,temp);

    f:
    cout << "Enter your word: ";
    getline(cin,word,'\n');

    //
    //checks for valid input
    if(!ValidInput(word))
    {
        system("cls");
        cout<<"\nword contains invalid characters!!\n"<<endl;
        goto f;
    }
    //transforms full string to lowercase
    transform(word.begin(), word.end(), word.begin(),::tolower);
    //

    //rest of the inputs
    cout << "Enter meaning: ";
    getline(cin,meaning,'\n');

    cout << "Enter Synonyms: ";
    getline(cin,synonyms,'\n');

    cout << "Enter Antonyms: ";
    getline(cin,antonyms,'\n');


    //main insertion & file writing part
    if(tree.SearchMe(convertString(word))==nullptr)
    {
        tree.InsertWord(convertString(word),meaning,synonyms,antonyms);
        system("cls");
        cout<<"\n\nThe word has been added!!"<<endl;

        //
        ofstream inFile;
        inFile.open("Dictionary.txt", fstream::app);
        inFile << word <<"\n"<< meaning <<"\n"<< synonyms <<"\n"<< antonyms <<endl;
        inFile.close();
        //
    }
    system("cls");
    cout<<"\nThe word is already in the dictionary"<<endl;


}
//__________________________________________________________________________________




//search
//__________________________________________________________________________________
void SearchWord(Trie &tree)
{
    system("cls");
    Node* N;
    string word;
    f:
    cout << "\nEnter word to search: ";
    cin >> word;

    //
    //checks for valid input
    if(!ValidInput(word))
    {
        system("cls");
        cout<<"\nword contains invalid characters!!\n"<<endl;
        goto f;
    }
    //transforms full string to lowercase
    transform(word.begin(), word.end(), word.begin(),::tolower);
    //


    //main search part
    N=tree.SearchMe(convertString(word));
    if(N != nullptr)
    {

        WriteToHistory(word);

        cout <<"Meaning: " << N->details<<endl;
        cout<<" \n----------------------------- \n"<<endl;

        int choice = 0;
        cout<<"1)For more options. \n0)To go back. "<<endl;
        cin >> choice;
        if(choice == 1)
            {
                system("cls");
                cout<< "\n1)See Synonyms \n2)See Antonyms \n3)Save As Favorite \n0)To go back "<<endl;
                cin >> choice;
                if(choice == 1)
                    Synonyms(N);
                else if(choice == 2)
                    Antonyms(N);
                else if(choice == 3)
                    AddToFavList(word);
                else
                {
                    system("cls");
                    return;
                }
            }
        else
            {
                system("cls");
                return;
            }
    }
    else
    {
        system("cls");
        cout << "Word not found!";
        return;
    }



}
//__________________________________________________________________________________



//synonyms & antonyms           //sub-functions of search
//__________________________________________________________________________________
void Synonyms(Node* N)
{
    system("cls");
    cout << "\n\nSynonyms: " << N->synonyms<< endl;
    cout<<"---------------- "<<endl;
    cout<<"Press any key to return"<<endl;
    cin.ignore();
    cin.get();
    system("cls");

}

void Antonyms(Node* N)
{
    system("cls");
    cout << "\n\nAntonyms: " << N->antonyms << endl;
    cout<<"---------------- "<<endl;
    cout<<"Press any key to return"<<endl;
    cin.ignore();
    cin.get();
    system("cls");
}
//__________________________________________________________________________________





//Delete
//__________________________________________________________________________________
void DeleteWord(Trie &T)
{
    system("cls");
    string word, temp;
    f:
    cout<<"\nEnter the word you want to delete: "<<endl;
    cin>>word;

    //
    //checks for valid input
    if(!ValidInput(word))
    {
        system("cls");
        cout<<"\nword contains invalid characters!!\n"<<endl;
        goto f;
    }
    //transforms full string to lowercase
    transform(word.begin(), word.end(), word.begin(),::tolower);
    //

    T.DeleteWord(convertString(word), word);
    system("cls");
    cout<<"\n\nThe word has been deleted!!"<<endl;

}
//__________________________________________________________________________________




//writing history & adding to favorite list
//__________________________________________________________________________________
void WriteToHistory(string word)
{
    //
    ofstream HistoryFile;
    HistoryFile.open("History.txt", fstream::app);
    HistoryFile << word <<endl;
    HistoryFile.close();
    //
}

void AddToFavList(string word)
{
    system("cls");
    cout<<"\n\nWord has been added to your Fav list!!"<<endl;
    ofstream FavFile;
    FavFile.open("Fav.txt", fstream::app);
    FavFile << word <<endl;
    FavFile.close();

}
//__________________________________________________________________________________




//view word history & Favorite list
//__________________________________________________________________________________
void ViewHistory()
{
    system("cls");
    string word;
    cout<<"History : "<<endl;
    cout<<"---------------- "<<endl;
    ifstream theFile("History.txt");
    while(theFile >> word)
    {
        cout<<word<<endl;
    }
    theFile.close();
    cout<<"---------------- "<<endl;
    cout<<"Press any key to return"<<endl;
    cin.ignore();
    cin.get();
    system("cls");
    //return;
}

void ShowFavList()
{
    system("cls");
    string word;
    cout<<"Favorite List : "<<endl;
    cout<<"---------------- "<<endl;
    ifstream theFile("Fav.txt");
    while(theFile >> word)
    {
        cout<<word<<endl;
    }
    theFile.close();
    cout<<"---------------- "<<endl;
    cout<<"Press any key to return"<<endl;
    cin.ignore();
    cin.get();
    system("cls");
    //return;
}
//__________________________________________________________________________________



//count number of words & write it in file
//__________________________________________________________________________________
void ShowNoOfWords(Trie &T)
{
    system("cls");
    cout<<"\n\n\nTotal number of words "<<T.count<<endl;
    cout<<"-------------------------"<<endl;
    cin.ignore();
    cin.get();
    system("cls");
}

void NoOfWords(Trie &T)
{
    system("cls");
    ofstream inFile("No Of Words.txt");
    inFile << T.count <<endl;
    inFile.close();
}
//__________________________________________________________________________________

