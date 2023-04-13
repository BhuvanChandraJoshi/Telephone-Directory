#include <bits/stdc++.h>
using namespace std;

string toUpperCase(string s){
    for(int i=0; i<s.length(); i++){
        s[i] = toupper(s[i]);
    }
    return s;
}

class TrieNode;

class PhoneDirectory;

class PhoneDataType;

class TrieNode {
private:
    TrieNode* arr[26];
    bool isEndOfWord;
    vector<int> indexOfRecord;
public:
    TrieNode(){
        for(int i=0; i<26; i++){
            arr[i] = NULL;
        }
        isEndOfWord = false;
        indexOfRecord = {};
    }
    friend void InsertRecordInTree(TrieNode*, PhoneDataType, int);
    friend class PhoneDirectory;
};

class PhoneDataType {       //Class to Record a person's details and number(basic unit)
private:
    string name;
    string number;
public:
    PhoneDataType(string name, string number){
        this->name = name;
        this->number = number;
    }

    void PrintRecord() {
        cout<<name<<"\t\t\t"<<number<<endl;
    }

    friend void InsertRecordInTree(TrieNode*, PhoneDataType, int);
};

class PhoneDirectory {      //Class to maintain the phone directory
private:
    vector<PhoneDataType> Directory;
    TrieNode* root;
public:
    PhoneDirectory() {
        //Reading Directory File and inserting all the records in Directory vector and creating a Tree
        root = new TrieNode();
        fstream DirectoryFile;
        DirectoryFile.open("directory.txt", ios::in);
        string phoneRecord;
        while(getline(DirectoryFile, phoneRecord)){
            stringstream s(phoneRecord);
            string name, number;
            s >> name;
            s >> number;
            PhoneDataType temp(name, number);
            Directory.push_back(temp);
            InsertRecordInTree(root, temp, Directory.size()-1);
        }
        DirectoryFile.close();
    }

    void PrintPhoneDirectory() {
        cout<<"Name\t\t\tNumber\n";
        cout<<"-------------------------------------------\n";
        for(auto Record: Directory){
            Record.PrintRecord();
        }
    }

    void AddNewRecord(){
        //Creating Record
        string name, number;
        cout<<"Name: ";
        cin>>name;
        name = toUpperCase(name);
        cout<<"Number: ";
        cin>>number;
        PhoneDataType temp(name, number);

        //Adding record to Directory vector
        Directory.push_back(temp);

        //Adding record to directory file
        fstream DirectoryFile;
        DirectoryFile.open("directory.txt", ios::app);
        DirectoryFile<<name+" "+number;
        DirectoryFile.close();
    }

    void Search(){
        string s;
        cout<<"Enter name: ";
        cin>>s;
        s = toUpperCase(s);
        TrieNode* curr = root;
        for(int i=0; i<s.size(); i++){
            if(curr->arr[s[i]-'A'] == NULL){
                cout<<"No record matched with given details.\n";
                return;
            }
            else
                curr = curr->arr[s[i]-'A'];
        }
        if(curr->isEndOfWord){
            for(int i=0; i<curr->indexOfRecord.size(); i++){
                Directory[curr->indexOfRecord[i]].PrintRecord();
            }
        }
    }
};

void InsertRecordInTree(TrieNode* root, PhoneDataType record, int indexOfRecord) {
    string name = record.name;
    for(int i=0; i<name.size(); i++){
        if(root->arr[name[i]-'A'] == NULL){
            TrieNode* temp = new TrieNode();
            root->arr[name[i]-'A'] = temp;
        }
        root = root->arr[name[i]-'A'];
    }
    root->indexOfRecord.push_back(indexOfRecord);
    root->isEndOfWord = true;
}

void Menu(){
    PhoneDirectory p;
    cout<<"Phone Directory\n";
    bool flag = true;
    while(flag){
        cout<<"1. Search Record\n2.Add record\n3.Exit\n";
        int choice;
        cin>>choice;
        if(choice == 1)
            p.Search();
        else if(choice == 2)
            p.AddNewRecord();
        else
            flag = false;
    }
}

int main(){
    Menu();
}
