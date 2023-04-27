#pragma once

#include <string>
using namespace std;

struct Song
{
    string name;
    string artists;
    string album;
    Song* next = nullptr;

    // Metrics for determining song closeness
    double danceability;
    double energy;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveliness;
    double valence;

    Song() : name("") {};
    Song(string s_name, string s_arts, string s_album)
            : name(s_name)
            , artists(s_arts)
            , album(s_album)
    {};
    Song(string s_name, string s_arts, string s_album, double s_dabil, double s_ener,
         double s_spch, double s_acst, double s_instr, double s_livl, double s_vlce)
            : name(s_name)
            , artists(s_arts)
            , album(s_album)
            , danceability(s_dabil)
            , energy(s_ener)
            , speechiness(s_spch)
            , acousticness(s_acst)
            , instrumentalness(s_instr)
            , liveliness(s_livl)
            , valence(s_vlce)
    {};
    friend bool operator< (const Song& lhs, const Song& rhs);
    friend bool operator> (const Song& lhs, const Song& rhs);
};

// Operators for comparing songs
bool operator< (const Song& lhs, const Song& rhs)
{
    return (lhs.name.compare(rhs.name) < 0);
}

bool operator> (const Song& lhs, const Song& rhs)
{
    return (lhs.name.compare(rhs.name) > 0);
}
