#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include <string>

namespace textures
{
	enum id { PLAYER = 0, ITEMS, ENEMIES, EXPLOSION };
}

class TextureHolder
{
public:
	TextureHolder(); 
	~TextureHolder(); 

	static void load(const textures::id&, const std::string&); 
	static sf::Texture& get(const textures::id&); 
private:
	static std::map<textures::id,
		sf::Texture*> textureMap; 
};