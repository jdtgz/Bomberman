#include "TextureHolder.h"

std::map<Textures::ID,
	sf::Texture*> TextureHolder::textureMap;

TextureHolder::TextureHolder()
{
	load(Textures::Player, "bomberman_player.png");
	load(Textures::Items, "bomberman_items.png");
}


TextureHolder::~TextureHolder()
{
	for (auto tex : textureMap)
	{
		delete tex.second;
	}
}


void TextureHolder::load(Textures::ID id, const std::string& filename)
{
	//std::unique_ptr<sf::Texture> txture(new sf::Texture()); 
	sf::Texture* txture = new sf::Texture();
	txture->loadFromFile(filename); 

	textureMap.insert(std::make_pair(id, std::move(txture))); 
}


sf::Texture& TextureHolder::get(Textures::ID id)
{
	std::map<Textures::ID, sf::Texture*>::iterator 
	found = textureMap.find(id);


	if (found != textureMap.end())
		return *textureMap[found->first];
	else
	{
		sf::Texture emptyTex;
		return emptyTex;
	}
}