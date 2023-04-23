Project 3 Proposal
Team TJJ
Justin Nagovskiy, Trent Wantman, Jeremy Blevins
Project Title: Song Recommender


Problem
Music streaming services have been the subject of criticism due to their perceived lack of proficiency in recommending songs. Despite utilizing sophisticated algorithms and machine learning technologies, these services fall short in taking into account important variables such as a user's mood, context, and individual taste which can be highly variable depending on the situation. Rather, these services rely heavily on a user's past listening history and behavior, which can be limiting and biased in predicting what they might enjoy in the future. Furthermore, recommendations are often based on popular songs, which may not necessarily reflect the unique preferences of individual users. 

Motivation
This deficiency in recommendations can lead to user dissatisfaction, as they struggle to find fresh and exciting music that resonates with them. The impact of this issue extends beyond users and also affects smaller and independent artists, who have a harder time reaching new listeners and expanding their fan base. Streaming services frequently prioritize popular and established artists with record deals over lesser-known independent artists, which results in a lack of exposure for the latter group. Consequently, users may miss out on discovering new music that they would enjoy if given the chance to. And smaller artists may find it challenging to gain recognition and support themselves financially through their music.
Through a comprehensive analysis of musical characteristics, such as melody, rhythm, tempo, lyrics, and genre, our recommendation system identifies unique patterns and connections between songs that align with each user's specific preferences. This personalized approach not only enhances users' listening experiences but also provides smaller and independent artists with a platform to gain wider exposure and reach new audiences.

Features
The program will allow the user to search for a particular song. The program will then search for the song within a data set of songs. If the song is found, it will let the user know. The user will then be prompted to select between different options that change how the program will recommend songs. For example, a user might be able to choose a range of years between which the songs they are looking for are released. The program will then sort the list of songs (excluding the song that the user searched for) by how similar it is to the user’s song. This will be determined using numerical data for each song, such as key, tempo, and popularity. The differences between each of these numerical quantities and the user’s song will be calculated, squared, and added for each song in the data set. The data set will then be sorted in ascending order by this value. The user will select the number of songs to return, and the program will return that number of songs that had the lowest values in the data set. The whole data set does not need to be sorted. These songs are the songs in the data set that are most similar to the one the user searched for and are the program’s recommendations for the user.

Data
We will most likely be using the Spotify API for our data. Information about it is found in the references [1]. Some of the information available in this data set is genre, release date, artist, album, key, tempo, and energy. We will be using at least 100,000 songs containing popular songs from across genres and decades. Nobody in our group has previous experience with APIs, so we will have to learn. Since multiple other groups in past semesters have used the Spotify API, it seems like a reasonable choice. If we are not able to get the API working, we will use a data set from CORGIS [2]. This data set only has 10,000 songs, so we will have to randomly generate the remaining 90,000 songs.

Tools
We will primarily be using C++ and, if we use the Spotify API, likely Python. We will also attempt to build a web application if time permits. If so, we will be using JavaScript, HTML, and CSS. If not, we will be using a menu-driven program in the command prompt.

Strategy
We will be implementing two data structures to hold our data set, these being a B tree and a hash map. There will be a song class, which contains all information pertaining to a song. This song class will represent the keys in the B tree and the buckets in the hash map. When the user searches for a song, the user can select which data structure to search in. In the B tree, the songs will be sorted by name. The input to the hash map will be the name the user searches. The time taken to find the song will be listed each time the user searches. Moreover, we will need a data structure and an algorithm to sort the data structures by similarity to the user’s song. This may be done using a separate C++ STL data structure containing all the data and a heap sort, as comparison of sorting algorithms is outside the scope of the project.

Distribution of Responsibility and Roles
Everything will be split evenly. Work on the system design will be done together. Two of us will be responsible for implementing one of the two data structures that we will be comparing. The third student will be responsible for implementing the web application and helping the other two students with the data structures.

Visuals
	The following are four different options we have considered for our visual.








References


[1] https://engineering.atspotify.com/2015/03/understanding-spotify-web-api/#:~:text=You%20c an%20make%20similar%20calls,that%20it's%20free%20to%20access
[2] https://think.cs.vt.edu/corgis/csv/music/
