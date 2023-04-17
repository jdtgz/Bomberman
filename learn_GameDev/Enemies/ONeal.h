#pragma once
#include "Enemy.h"

class ONeal : public Enemy
{
public:
	ONeal(const Player*);
	ONeal(const Player*, const sf::Vector2i&);
	ONeal(const Player*, const sf::Vector2i&, const direction&);

	virtual void move(Tile* [33][15]) override;

	~ONeal();
private:
	void init(const sf::Vector2i&, const direction&);

	//Debounce counter to delay random heading changes
	int dirDebounce;
	
	bool chasePlayer;
};