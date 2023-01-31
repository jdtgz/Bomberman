#include "TextureHolder.h"


TextureHolder::TextureHolder()
{
	load(Textures::Player, "bomberman_player.png"); 
}


TextureHolder::~TextureHolder()
{
}


void TextureHolder::load(Textures::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> txture(new sf::Texture()); 
	txture->loadFromFile(filename); 

	textureMap.insert(std::make_pair(id, std::move(txture))); 
}


sf::Texture& TextureHolder::get(Textures::ID id)
{
	auto found = textureMap.find(id); 
	return *found->second; 
}
