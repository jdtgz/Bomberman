#pragma once
#include "Enemy.h"

class Valcom : public Enemy
{
public:
	//Constructors
	Valcom(const Player*);
	Valcom(const Player*, const sf::Vector2i&);
	Valcom(const Player*, const sf::Vector2i&, const direction&);

	//Valcom movement AI
	virtual void move(Tile* [33][15]) override;

	//Destructor
	~Valcom();
private:
	//Initialization method, called by constructor
	void init(const sf::Vector2i&, const direction&);

	//Debounce counter to delay random heading changes
	int dirDebounce;
};