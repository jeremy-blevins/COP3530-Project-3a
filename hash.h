#include <iostream>
#include <cstdlib>
#include <vector>
#include "song.h"

using namespace std;



class Hash {
private:

    struct songStruct {
        Song song;
        songStruct* next;
        songStruct* prev;
    };

    static const int tableSize = 100;
    songStruct* hashMap[tableSize];

public:
    Hash();
    int hash(string key);
    void AddSong(Song newSong);
    int NumberOfItemsInIndex(int index);
    void PrintTable();
    void PrintItemsInIndex(int index);
    void FindSong(string name);
    void RemoveItem(string title);
    int count = 0;
};

Hash::Hash(){
    for (int i = 0; i < tableSize; ++i) {
        hashMap[i] = new songStruct;
        hashMap[i]->next = nullptr;
        hashMap[i]->prev = nullptr;
    }

}

void Hash::AddSong(Song newSong) {

    int index = hash(newSong.name);


    if (hashMap[index]->song.name.empty())
    {
        hashMap[index]->song = newSong;
    }
    else
    {
        songStruct* Ptr = hashMap[index];
        songStruct* n = new songStruct;
        n->song = newSong;
        n->next = nullptr;

        while(Ptr->next != nullptr)
        {
            Ptr = Ptr->next;
        }
        Ptr->next = n;
    }
}

int Hash::hash(string key) {

    int hash = 0;
    int index;

    for (int i = 0; i < key.length(); i++) {
        hash = hash + (int) key[i];
    }

    index = hash % tableSize;

    if (index < 0) { index*=-1;}
    return index;
}


void Hash::FindSong(string name)
{
    int index = hash(name);
    bool foundName = false;
    Song song;

    songStruct* Ptr = hashMap[index];
    while (Ptr != nullptr) {

        if(Ptr->song.name == name) {

            foundName = true;
            song = Ptr->song;
        }

        Ptr = Ptr->next;
    }

    if(foundName == true)
    {
        cout << "Song name = " << song.name << endl;
        cout << "Song artist = " << song.artists << endl;
    }
    else
    {
        cout << name << "'s information was not found in the Hash Table\n";
    }
}

/*
void Hash::RemoveItem(string title)
{
    int index = hash(title);

    song* delPtr;
    song* P1;
    song* P2;

    //Case 0: bucket is empty
    if(HashTable[index]->title == "empty" && HashTable[index]->artist == "empty")
    {
        cout << title << " was not found in the Hash Table\n";
    }

    //Case 1: only 1 song in bucket and song has matching title
    else if (HashTable[index]->title == title && HashTable[index]->next == NULL)
    {
        HashTable[index]->title = "empty";
        HashTable[index]->artist = "empty";
        cout << title << " was removed from the Hash Table\n";
    }

    //Case 2: match is located in the first song in the bucket but there are more items in the bucket
    else if (HashTable[index]->title == title)
    {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;

        cout << title << " was removed from the Hash Table\n";
    }
    //Case 3: bucket contains items but first song is not a match
    else
    {
        P1 = HashTable[index]-> next;
        P2 = HashTable[index];

        while (P1 != NULL && P1-> title != title)
        {
            P2 = P1;
            P1 = P1->next;
        }
        //Case3.1 no match
        if(P1 == NULL)
        {
            cout << title << " was not found in the Hash Table\n";
        }
        //Case 3.2 Match is found
        else
        {
            delPtr = P1;
            P1 = P1->next;
            P2->next = P1;
            delete delPtr;
            cout << title << " was removed from the Hash Table\n";
        }
    }
}







*/






















