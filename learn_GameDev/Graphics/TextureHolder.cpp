#include "TextureHolder.h"


std::map<textures::id,
	sf::Texture*> TextureHolder::textureMap;


TextureHolder::TextureHolder()
{
	load(textures::PLAYER, "Textures/bomberman_player.png");
	load(textures::ITEMS, "Textures/bomberman_items.png");
	load(textures::ENEMIES, "Textures/bomberman_enemies.png");
	load(textures::EXPLOSION, "Textures/bomberman_explosion.png");
}


TextureHolder::~TextureHolder()
{
	for (auto tex : textureMap)
	{
		delete tex.second;
	}
}


void TextureHolder::load(const textures::id& id, const std::string& filename)
{
	sf::Texture* txture = new sf::Texture();
	txture->loadFromFile(filename);

	textureMap.insert(std::make_pair(id, std::move(txture))); 
}


sf::Texture& TextureHolder::get(const textures::id& id)
{
	std::map<textures::id, sf::Texture*>::iterator 
	found = textureMap.find(id);


	// Prevents loading of a non-existing texture in map
	if (found != textureMap.end())
		return *textureMap[found->first];
	else
	{
		sf::Texture emptyTex;
		return emptyTex;
	}
}