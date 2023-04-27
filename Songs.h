#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stdlib.h>
#include "song.h"

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
    std::vector<std::vector<string>> FindSimilar(const Song& searchSong);
};

bool tuple_comparison (tuple<double,std::vector<string>> i,tuple<double,std::vector<string>> j)
{
    return (std::get<0>(i) < std::get<0>(j));
}

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
    std::string songID, songName, songAlbum, songArtists, songDanceability, songEnergy, songSpeechiness,
            songAcousticness, songInstrumentalness, songLiveliness, songValence;

    //get relevant song info
    songID = songInfo[0];
    songName = songInfo[1];
    songAlbum = songInfo[2];
    songArtists = songInfo[4];
    songDanceability = songInfo[9];
    songEnergy = songInfo[10];
    songSpeechiness = songInfo[14];
    songAcousticness = songInfo[15];
    songInstrumentalness = songInfo[16];
    songLiveliness = songInfo[17];
    songValence = songInfo[18];

    //add song to songList
    songList.push_back({songID, songName, songAlbum, songArtists, songDanceability, songEnergy,
                        songSpeechiness, songAcousticness, songInstrumentalness, songLiveliness, songValence});
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

std::vector<std::vector<string>> Songs::FindSimilar(const Song& searchSong) {
    //vector to return list of songs
    std::vector<std::vector<string>> results;

    std::string searchName = searchSong.name;

    // Calculate the squares of the danceability errors
    std::vector<double> danceability_errors_squared;
    for(int i = 0; i < songList.size(); i++)
    {
        double danceability_error = stod(songList[i][4]) - searchSong.danceability;
        danceability_errors_squared.push_back(danceability_error*danceability_error);
    }

    // Calculate the squares of the energy errors
    std::vector<double> energy_errors_squared;
    for(int i = 0; i < songList.size(); i++)
    {
        double energy_error = stod(songList[i][5]) - searchSong.energy;
        energy_errors_squared.push_back(energy_error*energy_error);
    }

    // Calculate the squares of the speechiness errors
    std::vector<double> speechiness_errors_squared;
    for(int i = 0; i < songList.size(); i++)
    {
        double speechiness_error = stod(songList[i][6]) - searchSong.speechiness;
        speechiness_errors_squared.push_back(speechiness_error*speechiness_error);
    }

    // Calculate the squares of the acousticness errors
    std::vector<double> acousticness_errors_squared;
    for(int i = 0; i < songList.size(); i++)
    {
        double acousticness_error = stod(songList[i][7]) - searchSong.acousticness;
        acousticness_errors_squared.push_back(acousticness_error*acousticness_error);
    }

    // Calculate the squares of the instrumentalness errors
    std::vector<double> instrumentalness_errors_squared;
    for(int i = 0; i < songList.size(); i++)
    {
        double instrumentalness_error = stod(songList[i][8]) - searchSong.instrumentalness;
        instrumentalness_errors_squared.push_back(instrumentalness_error*instrumentalness_error);
    }

    // Calculate the squares of the liveliness errors
    std::vector<double> liveliness_errors_squared;
    for(int i = 0; i < songList.size(); i++)
    {
        double liveliness_error = stod(songList[i][9]) - searchSong.liveliness;
        liveliness_errors_squared.push_back(liveliness_error*liveliness_error);
    }

    // Calculate the squares of the valence errors
    std::vector<double> valence_errors_squared;
    for(int i = 0; i < songList.size(); i++)
    {
        double valence_error = stod(songList[i][10]) - searchSong.valence;
        valence_errors_squared.push_back(valence_error*valence_error);
    }

    // Sum all the errors together across metrics and make sure to pair the song name and artist for each respective song
    // so that the information does not get lost after sorting
    std::vector<tuple<double,std::vector<string>>> distance_squared_tuples;
    for(int i = 0; i < songList.size(); i++)
    {
        double error_sum = danceability_errors_squared[i] + energy_errors_squared[i] + speechiness_errors_squared[i]
                           + acousticness_errors_squared[i] + instrumentalness_errors_squared[i] + liveliness_errors_squared[i]
                           + valence_errors_squared[i];
        vector<string> song_info;
        song_info.push_back(songList[i][1]);
        song_info.push_back(songList[i][3]);
        tuple<double,std::vector<string>> temp(error_sum, song_info);
        distance_squared_tuples.push_back(temp);
    }

    // Sort the vector of tuples in ascending order
    std::sort(distance_squared_tuples.begin(), distance_squared_tuples.end(), tuple_comparison);

    // Push the closest songs to the results vector
    for(int i = 0; results.size() <= 10; i++)
    {
        std::vector<string> songNameAndArtist = std::get<1>(distance_squared_tuples[i]);
        std::string songName = songNameAndArtist[0];
        if(songName != searchName)
        {
            bool repeat_found = false;
            for(int j = 0; j < results.size(); j++)
            {
                if(songName == results[j][0])
                {
                    repeat_found = true;
                }
            }
            if(!repeat_found)
            {
                results.push_back(songNameAndArtist);
            }
        }
    }

    return results;
}

/*
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
*/