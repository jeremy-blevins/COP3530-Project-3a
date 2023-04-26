#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include "Songs.h"
#include "song.h"
#include "b_tree.h"
//#include "b_tree.h"
//#include "song.h"

void parseFile(const std::string& filename, Songs &songList, B_Tree& tree){
    //create an input filestream
    std::fstream file;

    file.open(filename, std::ios::in);

    //temp variable to hold the line
    std::string line;

    //check if file is open
    if (file.is_open()) {
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

            // Create a new song object for the B tree
            Song temp_song(  /*Name*/ songInfo[1], 
                            /*Artists*/ songInfo[4], 
                            /*Album*/ songInfo[2],
                            /*Danceability*/ stod(songInfo[9]),
                            /*Energy*/ stod(songInfo[10]),
                            /*Speechiness*/ stod(songInfo[14]),
                            /*Acousticness*/ stod(songInfo[15]),
                            /*Instrumentalness*/ stod(songInfo[16]),
                            /*Liveliness*/ stod(songInfo[17]),
                            /*Valence*/ stod(songInfo[18]));

            // Add song object to B Tree
            tree.insert_key(temp_song);

            //add song to class
            songList.AddSong(songInfo);
        }
    } 
    else {
        //throw error if file was not opened
        std::cout << "ERROR: FILE NOT OPENED" << std::endl;
        return;
    }
}

int main() {
    //create Songs object
    Songs songList;
    std::cout << "Initializing..." << std::endl;

    // Create B Tree object
    B_Tree songTree(10);

    // Read in all the songs in the CSV file
    parseFile("./Songs100k.txt", songList, songTree);

    std::cout << "Adding songs to B tree..." << std::endl;

    std::cout << "Tree has " << songTree.num_nodes << " Nodes" << std::endl << std::endl;


    


    

    //std::cout << "Adding songs to hash..." << std::endl;

    //start clock
    //start = std::chrono::steady_clock::now();

    //TODO add songs to hash
    //for (int i = 0; i < 100000; i++){}

    //stop clock
    //stop = std::chrono::steady_clock::now();

    //calculate and print clock difference
    //duration = stop - start;
    //std::cout << "Time to add songs to hash " << duration.count() << " s"<< std::endl;

    //prompt for user search
    std::cout << "Type song to search for: ";

    //string to hold user search
    std::string input;

    //get the input from the terminal (should be changed to get the input from the GUI)
    getline(std::cin, input);

    // Define an output string stream for the search operation
    std::ostringstream search_out;

/* SEARCH FOR THE SONG IN B TREE */

    std::string searched_song = input;
    search_out << "Searching for song using a B Tree \"" << searched_song << "\"" << std::endl;
    
    //start clock
    auto start = std::chrono::steady_clock::now();

    Song* found_song = songTree.search(searched_song);

    //stop clock
    auto stop = std::chrono::steady_clock::now();

    //calculate and print clock difference
    std::chrono::duration<double> duration = stop - start;
    search_out << "Time to search for the song \"" << searched_song << "\": " << duration.count() << " s" << std::endl << std::endl;

    //if the song is found, print it
    if(found_song != nullptr)
    {
        search_out << "Song found: ";
        search_out << found_song->name << endl;
        if(found_song->artists[0] == '"') // if there is more than one artist in the list
        {
            search_out << "Artists: " << (found_song->artists).substr(2,(found_song->artists).length()-4) << endl;
        }
        else
        {
            search_out << "Artists: " << (found_song->artists).substr(1,(found_song->artists).length()-2) << endl;
        }
        
        search_out << "Album: " << found_song->album << endl;
    }
    else
    {
        search_out << "Song not found" << endl;
    }

    std::cout << search_out.str() << std::endl;

/* END OF SEARCH FOR SONG IN B TREE */

/* BEGINNING OF SONG RECOMMENDATIONS */

    // Define an output string stream for the similar songs operation
    std::ostringstream similar_out;

    // Print a list of similar songs is the original song was found
    if(found_song != nullptr)
    {
        std::vector<std::vector<string>> similarSongs;
        similarSongs = songList.FindSimilar(*found_song);

        similar_out << std::endl << "You may also like these songs:" << std::endl;

        for (int i = 0;i < similarSongs.size();i++)
        {
            string song_name = similarSongs[i][0];
            string song_artists = similarSongs[i][1];

            similar_out << song_name << " by ";

            if(song_artists[0] == '"') // if there is more than one artist in the list
            {
                similar_out << song_artists.substr(2,song_artists.length()-4);
            }
            else
            {
                similar_out << song_artists.substr(1,song_artists.length()-2);
            }

            similar_out << std::endl;
        }
    }

    std::cout << similar_out.str() << std::endl;

/* END OF SONG RECOMMENDATIONS */

    //TODO search for song in hash map

    
    return 0;
}

/*
int main()
{
    B_Tree b_tree(2);

    Song temp0("A", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp1("B", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp2("C", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp3("D", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp4("E", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp5("F", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp6("G", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp7("H", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp8("I", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Song temp9("J", "", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    b_tree.insert_key(temp5);
    b_tree.insert_key(temp9);
    b_tree.insert_key(temp3);
    b_tree.insert_key(temp7);
    b_tree.insert_key(temp1);
    b_tree.insert_key(temp2);
    b_tree.insert_key(temp8);
    b_tree.insert_key(temp6);
    b_tree.insert_key(temp0);
    b_tree.insert_key(temp4);

    b_tree.print_tree();

    cout << endl << "Searching" << endl;

    Song* found_song = b_tree.search("adsa");

    if(found_song != nullptr)
    {
        cout << "Song found: ";
        cout << found_song->name << endl;
    }
    else
    {
        cout << "Song not found" << endl;
    }

    return 0;
}
*/
