#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include <string>

namespace Textures
{
	enum ID { Player, Items, Enemies, Explosion };
}

class TextureHolder
{
	public:
		TextureHolder(); 
		~TextureHolder(); 


		static void load(Textures::ID id, const std::string& filename); 
		static sf::Texture& get(Textures::ID id); 

	private:
		static std::map<Textures::ID,
			sf::Texture*> textureMap; 
};

