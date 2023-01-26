#pragma once
#include "iostream"
#include "SFML/Graphics.hpp"
#include <string>

namespace Textures
{
	enum ID { Enemies, Player };
}

class TextureHolder
{
	public:
		TextureHolder(); 
		~TextureHolder(); 


		void load(Textures::ID id, const std::string& filename); 
		sf::Texture& get(Textures::ID id); 

	private:
		std::map<Textures::ID,
			std::unique_ptr<sf::Texture>> textureMap; 
};

