#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include "Songs.h"

void parseFile(const std::string& filename, Songs &songList){
    //create an input filestream
    std::fstream file;

    file.open(filename, std::ios::in);

    //temp variable to hold the line
    std::string line;

    //check if file is open
    if (file.is_open()){

        //get header line
        std::getline(file, line);

        //loop through the file
        while (std::getline(file,line)) {
            //vector to hold each song value
            std::vector<std::string> songInfo;

            //create stringstream
            std::stringstream temp(line);

            //variable to hold each value
            std::string value;

            //add each value to vector
            while (getline(temp, value, '|')) {
                songInfo.push_back(value);
            }

            //add song to class
            songList.AddSong(songInfo);
        }

    } else {
        //throw error if file was not opened
        std::cout << "ERROR: FILE NOT OPENED" << std::endl;
        return;
    }
}

int main() {
    //create Songs object
    Songs songList;
    std::cout << "Initializing..." << std::endl;
    parseFile("../Songs100k.txt", songList);


    std::cout << "Adding songs to B tree..." << std::endl;

    //start clock
    auto start = std::chrono::steady_clock::now();

    //TODO add songs to b tree
    for (int i = 0; i < 1000000000; i++){}

    //stop clock
    auto stop = std::chrono::steady_clock::now();

    //calculate and print clock difference
    std::chrono::duration<double> duration = stop - start;
    std::cout << "Time to add songs to B tree " << duration.count() << " s"<< std::endl;

    std::cout << "Adding songs to hash..." << std::endl;

    //start clock
    start = std::chrono::steady_clock::now();

    //TODO add songs to hash
    for (int i = 0; i < 100000; i++){}

    //stop clock
    stop = std::chrono::steady_clock::now();

    //calculate and print clock difference
    duration = stop - start;
    std::cout << "Time to add songs to hash " << duration.count() << " s"<< std::endl;

    //prompt for user search
    std::cout << "Type song to search for: ";

    //string to hold user search
    std::string input;

    //search for the song
    std::cin >> input;

    //TODO search for the song in b tree

    //TODO search for song in hash map

    //prints a list of similar songs
    std::vector<std::string> similarSongs;
    similarSongs = songList.FindSimilar(input);

    std::cout << "You may also like these songs:" << std::endl;

    for (int i  =0;i < similarSongs.size();i++){
        std::cout << similarSongs[i] << std::endl;
    }
    return 0;
}
