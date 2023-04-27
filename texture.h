#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class texture
{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string fileName);
    static string imagesDirectory;
public:
    static sf::Texture& GetTexture(string textureName);
    static void SetImagesDirectory(string directoryPath);
    static void Clear();
};
