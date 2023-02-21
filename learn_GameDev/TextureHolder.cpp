#include "TextureHolder.h"


std::map<textures::id,
	sf::Texture*> TextureHolder::textureMap;


TextureHolder::TextureHolder()
{
	load(textures::PLAYER, "bomberman_player.png");
	load(textures::ITEMS, "bomberman_items.png");
	load(textures::ENEMIES, "bomberman_enemies.png");
	load(textures::EXPLOSION, "bomberman_explosion.png");
}


TextureHolder::~TextureHolder()
{
	for (auto tex : textureMap)
	{
		delete tex.second;
	}
}


void TextureHolder::load(textures::id id, const std::string& filename)
{
	//std::unique_ptr<sf::Texture> txture(new sf::Texture()); 
	sf::Texture* txture = new sf::Texture();
	txture->loadFromFile(filename);

	textureMap.insert(std::make_pair(id, std::move(txture))); 
}


sf::Texture& TextureHolder::get(textures::id id)
{
	std::map<textures::id, sf::Texture*>::iterator 
	found = textureMap.find(id);


	if (found != textureMap.end())
		return *textureMap[found->first];
	else
	{
		sf::Texture emptyTex;
		return emptyTex;
	}
}