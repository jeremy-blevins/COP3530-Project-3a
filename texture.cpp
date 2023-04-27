#include "texture.h"

unordered_map<string, sf::Texture> texture::textures;

void texture::LoadTexture(string fileName)
{
    string path = "./textures/";
    path += fileName + ".png";

    textures[fileName].loadFromFile(path);
}

sf::Texture& texture::GetTexture(string textureName)
{
    if (textures.find(textureName) == textures.end())
    {
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void texture::Clear()
{
    textures.clear();
}