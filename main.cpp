#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "texture.h"
#include "Songs.h"
#include "song.h"
#include "b_tree.h"
#include "hash.h"

using namespace std;

void parseFile(const std::string& filename, Songs &songList, vector<Song>& allSongs){
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

            // Add song object to vector of songs
            allSongs.push_back(temp_song);
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

    //Songs
    Songs songList;
    // Create B Tree object
    B_Tree songTree(10);
    //Create Hash Map Object
    Hash songHash;
    vector<Song> allSongs;

    parseFile("./Songs100k.txt", songList, allSongs);

    //Support Variables
    double mouseX;
    double mouseY;
    int state = 0;
    string search = "";
    vector<sf::Text> songs;
    vector<sf::Text> messages;
    bool logScroll = false;
    int sub;

    /*-------------------Create Window----------------*/
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Project 3");
    sf::Sprite back;
    back.setTexture(texture::GetTexture("backLog"));
    cout << back.getGlobalBounds().height << endl;
    cout << back.getGlobalBounds().width << endl;
    double midX = back.getGlobalBounds().width/2;
    double midY = back.getGlobalBounds().height/2;

    float scaleX = window.getSize().x/back.getGlobalBounds().width;
    float scaleY = window.getSize().y/back.getGlobalBounds().height;

    cout << scaleX << endl;
    cout << scaleY << endl;

    back.setScale(scaleX, scaleY);


    /*-------------------Create Screen Objects----------------*/
    sf::Sprite mid;
    mid.setTexture(texture::GetTexture("mid"));
    mid.setPosition(804,254);
    mid.setScale(540/mid.getGlobalBounds().width, 804/mid.getGlobalBounds().width);

    sf::Sprite treeView;
    treeView.setTexture(texture::GetTexture("btree"));
    treeView.setPosition(829, 129);
    treeView.setScale(87 / treeView.getGlobalBounds().width, 87 / treeView.getGlobalBounds().width);

    sf::Sprite mapView;
    mapView.setTexture(texture::GetTexture("hashmap"));
    mapView.setPosition(929 , 129);
    mapView.setScale(87 / mapView.getGlobalBounds().width, 87 / mapView.getGlobalBounds().width);

    sf::Sprite playlist;
    playlist.setTexture(texture::GetTexture("playlist"));
    playlist.setPosition(1029 , 129);
    playlist.setScale(87 / playlist.getGlobalBounds().width, 87 / playlist.getGlobalBounds().width);

    sf::Sprite log;
    log.setTexture(texture::GetTexture("log"));
    log.setPosition(1129 , 129);
    log.setScale(87 / log.getGlobalBounds().width, 87 / log.getGlobalBounds().width);


    sf::Sprite restart;
    restart.setTexture(texture::GetTexture("restart"));
    restart.setPosition(1229,129);
    restart.setScale(87/restart.getGlobalBounds().width, 87/restart.getGlobalBounds().width);

    sf::Sprite mag;
    mag.setTexture(texture::GetTexture("search"));
    mag.setPosition(735.478,121);
    mag.setScale(49.522/mag.getGlobalBounds().width, 49.522/mag.getGlobalBounds().width);

    sf::Sprite searchBar;
    searchBar.setTexture(texture::GetTexture("searchBar"));
    searchBar.setPosition(22,121);
    searchBar.setScale(713.48/searchBar.getGlobalBounds().width, 713.48/searchBar.getGlobalBounds().width);


    //Font
    sf::Font font;
    font.loadFromFile("./fonts/ProximaNova.ttc");


    //Search Term
    sf::Text searchTerm;
    searchTerm.setFont(font);
    searchTerm.setString("Search");
    searchTerm.setPosition(41, 130);
    searchTerm.setCharacterSize(36);
    searchTerm.setFillColor(sf::Color::Black);

    //Icon names
    vector<sf::Text> labels;
    sf::Text treeViewTxt;
    treeViewTxt.setFont(font);
    treeViewTxt.setString("B Tree");
    treeViewTxt.setPosition(851, 227.443);
    treeViewTxt.setCharacterSize(16.51);
    treeViewTxt.setFillColor(sf::Color::White);
    labels.push_back(treeViewTxt);
    sf::Text mapViewTxt;
    mapViewTxt.setFont(font);
    mapViewTxt.setString("Hash Map");
    mapViewTxt.setPosition(947, 227.443);
    mapViewTxt.setCharacterSize(16.51);
    mapViewTxt.setFillColor(sf::Color::White);
    labels.push_back(mapViewTxt);
    sf::Text playlistTxt;
    playlistTxt.setFont(font);
    playlistTxt.setString("Playlist");
    playlistTxt.setPosition(1049, 227.443);
    playlistTxt.setCharacterSize(16.51);
    playlistTxt.setFillColor(sf::Color::White);
    labels.push_back(playlistTxt);
    sf::Text logTxt;
    logTxt.setFont(font);
    logTxt.setString("Log");
    logTxt.setPosition(1151, 227.443);
    logTxt.setCharacterSize(16.51);
    logTxt.setFillColor(sf::Color::White);
    labels.push_back(logTxt);
    sf::Text restartTxt;
    restartTxt.setFont(font);
    restartTxt.setString("Restart");
    restartTxt.setPosition(1247, 227.443);
    restartTxt.setCharacterSize(16.51);
    restartTxt.setFillColor(sf::Color::White);
    labels.push_back(restartTxt);



//Window Loop
while(window.isOpen()) {

sf::Event event;

    while (state == 0) {

        //TODO add songs to B Tree
        messages.clear();
        songs.clear();
        search = "";
        searchTerm.setString("Search");
        logScroll = false;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(back);
        messages.push_back(sf::Text("Adding songs to B Tree...",font,20));
        messages[messages.size()-1].setPosition(818.6,302.029);

        int j = 0;
        auto start = std::chrono::steady_clock::now();
        //TODO add songs to B Tree

        for (int i = 0; i < allSongs.size(); ++i) {
            songTree.insert_key(allSongs[i]);
            j++;
        }
        cout << j << endl;

        auto stop = std::chrono::steady_clock::now();

        std::chrono::duration<double> duration = stop - start;
        string time = "Time to add songs to B tree: " + to_string(duration.count()) + " ms";
        messages.push_back(sf::Text(time,font,20));
        messages[messages.size()-1].setPosition(818.6,messages[messages.size()-2].getGlobalBounds().top+25);
        messages.push_back(sf::Text("Adding songs to Hash Map...",font,20));
        messages[messages.size()-1].setPosition(818.6,messages[messages.size()-2].getGlobalBounds().top+25);

        j = 0;
        start = std::chrono::steady_clock::now();
        //TODO add songs to Hash Map

        for (int i = 0; i < allSongs.size(); ++i) {
            songHash.insert_key(allSongs[i]);
            j++;
        }
        cout << j << endl;

        stop = std::chrono::steady_clock::now();

        duration = stop - start;
        time = "Time to add songs to Hash Map: " + to_string(duration.count()) + " ms";
        messages.push_back(sf::Text(time,font,20));
        messages[messages.size()-1].setPosition(818.6,messages[messages.size()-2].getGlobalBounds().top+25);

        state = 1;


    }

    while(state == 1) {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                //Search
                if (searchBar.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
                    state = 2;
                    if (search == "") { searchTerm.setString("");}
                }
                else if (treeView.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    //TODO create search function with B Tree
                }
                else if (mapView.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    //TODO create search function with B Tree
                }
                else if (restart.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
                    state = 0;
                }

            }
        }

        //Draw Window
        window.clear();
        window.draw(mid);
        for (int i = 0; i < messages.size(); ++i) {window.draw(messages[i]);}
        window.draw(back);
        for (int i = 0; i < songs.size(); ++i) {window.draw(songs[i]);}
        window.draw(treeView);
        window.draw(mapView);
        window.draw(playlist);
        window.draw(log);
        window.draw(restart);
        window.draw(searchBar);
        window.draw(mag);
        window.draw(searchTerm);
        for (int i = 0; i < labels.size(); ++i) {window.draw(labels[i]);}
        for (int i = 0; i < messages.size(); ++i) {window.draw(messages[i]);}
        window.display();
    }

    while (state == 2) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered)
            {
                //Enter
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    // Enter key pressed, do something
                    state = 1;
                    Song* searchedSong;
                    messages.push_back(sf::Text("Searching Simular songs to: " + search,font,20));
                    messages[messages.size()-1].setPosition(818.6,messages[messages.size()-2].getGlobalBounds().top+25);

                    if (messages.size() > 17) {
                        for (int i = 0; i < messages.size(); i++) {
                            if (i == 0) {messages[i].move(0, -25); continue;}
                            messages[i].move(0, -25);
                            logScroll = true;
                        }
                    }

                    auto start = std::chrono::steady_clock::now();
                    searchedSong = songTree.search(search);
                    cout << search << endl;
                    auto stop = std::chrono::steady_clock::now();

                    std::chrono::duration<double> duration = stop - start;
                    string time = "Time to find songs in B tree: " + to_string(duration.count()) + " ms";
                    messages.push_back(sf::Text(time,font,20));
                    messages[messages.size()-1].setPosition(818.6,messages[messages.size()-2].getGlobalBounds().top+25);

                    start = std::chrono::steady_clock::now();
                    songHash.FindSong(search);
                    cout << search << endl;
                    stop = std::chrono::steady_clock::now();

                    duration = stop - start;
                    time = "Time to find songs in Hash Map: " + to_string(duration.count()) + " ms";
                    messages.push_back(sf::Text(time,font,20));
                    messages[messages.size()-1].setPosition(818.6,messages[messages.size()-2].getGlobalBounds().top+25);

                    vector<vector<string>> temp = songList.FindSimilar(*searchedSong);

                    songs.clear();
                    for (int i = 0; i < temp.size(); ++i){
                        string tempStr = "Song #" + (to_string(i+1)) + ": " + temp[i][0];
                        sf::Text song;
                        song.setString(tempStr);
                        song.setPosition(30,199 + (i*57));
                        song.setFillColor(sf::Color::White);
                        song.setFont(font);
                        song.setCharacterSize(25);
                        songs.push_back(song);
                    }
                }

                //Backspace
                else if (event.text.unicode == 8)
                {
                    if(!search.empty())
                        search.pop_back();
                }

                // Check for other printable characters
                else if (event.text.unicode >= 32 && event.text.unicode <= 126)
                {
                    // Printable character entered, add it to the search string
                    search += static_cast<char>(event.text.unicode);
                }
                else
                {
                    search += static_cast<char>(event.text.unicode);
                }
                //Update text
                searchTerm.setString(search);
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                //Search
                if (treeView.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    state = 2;
                }
                else if (mapView.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                    state = 2;
                }
                else if (restart.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
                    state = 0;
                }
                else if (!searchBar.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)) {
                    state = 1;
                }
            }
        }

        //Draw Window
        window.clear();
        window.draw(mid);
        for (int i = 0; i < messages.size(); ++i) {window.draw(messages[i]);}
        window.draw(back);
        for (int i = 0; i < songs.size(); ++i) {window.draw(songs[i]);}
        window.draw(treeView);
        window.draw(mapView);
        window.draw(playlist);
        window.draw(log);
        window.draw(restart);
        window.draw(searchBar);
        window.draw(searchTerm);
        for (int i = 0; i < labels.size(); ++i) {window.draw(labels[i]);}
        for (int i = 0; i < messages.size(); ++i) {window.draw(messages[i]);}
        window.display();

    }


}  //LOOP ^



    return 0;
}