#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include <string>

namespace textures
{
	enum id { PLAYER, ITEMS, ENEMIES, EXPLOSION };
}

class TextureHolder
{
public:
	TextureHolder(); 
	~TextureHolder(); 

	static void load(textures::id id, const std::string& filename); 
	static sf::Texture& get(textures::id id); 
private:
	static std::map<textures::id,
		sf::Texture*> textureMap; 
};