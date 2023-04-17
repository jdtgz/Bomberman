#pragma once
#include "Enemy.h"

class Valcom : public Enemy
{
public:
	Valcom(const Player*);
	Valcom(const Player*, const sf::Vector2i&);
	Valcom(const Player*, const sf::Vector2i&, const direction&);

	virtual void move(Tile* [33][15]) override;

	~Valcom();
private:
	void init(const sf::Vector2i&, const direction&);

	//Debounce counter to delay random heading changes
	int dirDebounce;
};