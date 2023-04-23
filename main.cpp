#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Songs.h"

void parseFile(const std::string& filename, Songs songList){
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
            while (getline(temp, value, ',')) {
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
    parseFile("../Songs100.csv", songList);
    std::cout << songList.GetAlbum("Testify") << std::endl;
    return 0;
}
