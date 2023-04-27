#include <iostream>
#include <cstdlib>
#include <vector>
#include "song.h"

using namespace std;



class Hash {
private:
    static const int tableSize = 1000;

    Song* hashMap[tableSize];

public:
    Hash();
    int hash(string key);
    void insert_key(Song k);
    vector<Song*> FindSong(string title);

};

Hash::Hash(){
    for (int i = 0; i < tableSize; ++i){
        Song* k = new Song;
        k->name = "NULL";
        hashMap[i] = k;
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

void Hash::insert_key(Song k) {

    int index = hash(k.name);


    if (hashMap[index]->name == "NULL")
    {
        hashMap[index] = &k;
    }
    else
    {
        Song* Ptr = hashMap[index];
        Song* n = new Song;
        *n = k;
        n->next = nullptr;

        while(Ptr->next != nullptr)
        {
            Ptr = Ptr->next;
        }
        Ptr->next = n;
    }
}

vector<Song*> Hash::FindSong(string title)
{
    vector<Song*> searchResults;
    int index = hash(title);
    bool foundTitle = false;

    Song* Ptr = hashMap[index];

    while (Ptr != nullptr)
    {
        if (Ptr->name == title)
        {
            foundTitle = true;
            searchResults.push_back(Ptr);
        }
        Ptr = Ptr->next;
    }

    if(foundTitle)
    {
        for (int i = 0; i < searchResults.size(); ++i) {
            cout << "\"" << searchResults[i]->name << "\" by: " << searchResults[i]->artists << endl;
        }

    }
    else
    {
        cout << title << "'s information was not found in the Hash Table\n";
    }

    return searchResults;
}









/*
int Hash::NumberOfItemsInIndex(int index)
{
    int count = 0;

    if(hashMap[index]->info.empty())
    {
        return count;
    }
    else
    {
        count++;
        song* Ptr = hashMap[index];
        while(Ptr->next != NULL)
        {
            count++;
            Ptr = Ptr->next;
        }
    }
    return count;
}

void Hash::PrintTable()
{
    int number;
    for(int i = 0; i < tableSize; i++)
    {
        number = NumberOfItemsInIndex(i);
        cout << "--------------------------\n";
        cout << "index = " << i << endl;
        for (int j = 0; j < hashMap[i]->info.size(); ++j) {
            cout << hashMap[i]->info[j] << ", ";
        }
        cout << "# of items = " << number << endl;
        cout << "--------------------------\n";
    }
}

void Hash::PrintItemsInIndex(int index)
{
    song* Ptr = hashMap[index];

    if(Ptr->info.empty())
    {
        cout << "index = " << index << " is empty";
    }
    else
    {
        cout << "index " << index << " contains the following songs\n";

        while(Ptr != NULL)
        {
            cout <<"--------------\n";
            for (int i = 0; i < Ptr->info.size(); ++i) {
                cout << Ptr->info[i] << ", ";
            }
            cout <<"--------------\n";
            Ptr = Ptr->next;
        }
    }
}

auto cmp = [](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
    return a.first < b.first;
};

vector<pair<float, song*>> Hash::FindSimilar(string title) {

    vector<pair<float, song*>> similar;
    song* songPtr = FindSong(title);
    cout <<songPtr->info[1] << endl;

    for (int i = 0; i < tableSize; ++i) {
        song* Ptr = hashMap[i];
        while (Ptr != NULL)
        {
            float score = 0;
            float valScore;
            for (int j = 9; j < Ptr->info.size(); ++j) {
                if (j != 11 && j != 12 && j != 13 && j != 16 && j != 20 && j != 21) {
                    valScore = abs(stof(songPtr->info[j])-stof(Ptr->info[j]));
                    score+= valScore;
                }
            }
            similar.push_back(make_pair(score,Ptr));
            int k = similar.size();
            Ptr = Ptr->next;
        }
    }

    //TODO: sort similar in ascending order by the float value in each pair.
    // sort similar in ascending order by the float value in each pair.
    std::sort(similar.begin(), similar.end(), [](const auto& lhs, const auto& rhs){
        return lhs.first < rhs.first;
    });

    for (int i = 0; i < 10; ++i) {
        cout << similar[i].second->info[1] << endl;
    }
    return similar;
}

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






















