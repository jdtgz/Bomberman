#pragma once
#include "Enemy.h"

class ONeal : public Enemy
{
public:
	//Constructors
	ONeal(const Player*);
	ONeal(const Player*, const sf::Vector2i&);
	ONeal(const Player*, const sf::Vector2i&, const direction&);

	//O'Neal movement AI
	virtual void move(Tile* [33][15]) override;

	//Destructor
	~ONeal();
private:
	//Initialization method, called by constructor
	void init(const sf::Vector2i&, const direction&);

	//Debounce counter to delay random heading changes
	int dirDebounce;
};