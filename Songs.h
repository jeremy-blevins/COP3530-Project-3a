#include <iostream>
#include <vector>

class Songs {
private:
    std::vector<std::vector<std::string>> songList;
    int FindIndex(const std::string& searchName);

public:
    void AddSong(std::vector<std::string> songInfo);
    std::string GetAlbum(const std::string& searchName);
    std::string GetArtists(const std::string& searchName);
    std::string GetDanceability(const std::string& searchName);
    std::string GetEnergy(const std::string& searchName);
    std::vector<std::string> FindSimilar(const std::string& searchName);
};

int Songs::FindIndex(const std::string& searchName) {
    //set index to -1
    int index = -1;

    //search songList for song name
    for (int i = 0; i < songList.size(); i++){
        if (searchName == songList[i][1]){
            index = i;
        }
    }
    return index;
}

void Songs::AddSong(std::vector<std::string> songInfo) {
    //temp variables;
    std::string songID, songName, songAlbum, songArtists, songDanceability, songEnergy;

    //get relevant song info
    songID = songInfo[0];
    songName = songInfo[1];
    songAlbum = songInfo[2];
    songArtists = songInfo[4];
    songDanceability = songInfo[9];
    songEnergy = songInfo[10];

    //add song to songList
    songList.push_back({songID, songName, songAlbum, songArtists, songDanceability, songEnergy});
}

std::string Songs::GetAlbum(const std::string& searchName) {
    //temp variables
    std::string result;
    int index;

    //find index of song
    index = FindIndex(searchName);

    if (index == -1){
        result = "ERROR: Song not found";
    } else {
        result = songList[index][2];
    }

    return result;
}

std::string Songs::GetArtists(const std::string& searchName) {
    //temp variables
    std::string result;
    int index;

    //find index of song
    index = FindIndex(searchName);

    if (index == -1){
        result = "ERROR: Song not found";
    } else {
        result = songList[index][3];
    }

    return result;
}

std::string Songs::GetDanceability(const std::string& searchName) {
    //temp variables
    std::string result;
    int index;

    //find index of song
    index = FindIndex(searchName);

    if (index == -1){
        result = "ERROR: Song not found";
    } else {
        result = songList[index][4];
    }

    return result;
}

std::string Songs::GetEnergy(const std::string& searchName) {
    //temp variables
    std::string result;
    int index;

    //find index of song
    index = FindIndex(searchName);

    if (index == -1){
        result = "ERROR: Song not found";
    } else {
        result = songList[index][5];
    }

    return result;
}

std::vector<std::string> Songs::FindSimilar(const std::string& searchName) {
    //vector to return list of songs
    std::vector<std::string> results;

    //get danceability
    std::string danceability = GetDanceability(searchName);

    //find 5 similar danceability songs
    for (int i =0; i < songList.size(); i++){
        if (danceability[2] == songList[i][4][2] && searchName != songList[i][1] && results.size() < 5){
            results.push_back(songList[i][1]);
        }
    }

    //get energy
    std::string energy = GetEnergy(searchName);

    //find 5 similar energy songs
    for (int j =0; j < songList.size(); j++){
        if (energy[2] == songList[j][5][2] && searchName != songList[j][1] && results.size() < 10){
            results.push_back(songList[j][1]);
        }
    }

    return results;
}
