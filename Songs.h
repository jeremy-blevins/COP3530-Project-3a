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
    double GetDanceability(const std::string& searchName);
    double GetEnergy(const std::string& searchName);
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

double Songs::GetDanceability(const std::string& searchName) {
    //temp variables
    double result;
    int index;

    //find index of song
    index = FindIndex(searchName);

    if (index == -1){
        result = -1.0;
    } else {
        result = std::stod(songList[index][4]);
    }

    return result;
}

double Songs::GetEnergy(const std::string& searchName) {
    //temp variables
    double result;
    int index;

    //find index of song
    index = FindIndex(searchName);

    if (index == -1){
        result = -1.0;
    } else {
        result = std::stod(songList[index][5]);
    }

    return result;
}