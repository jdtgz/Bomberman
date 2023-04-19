#pragma once
#include "ONeal.h"
class Minvo : public ONeal
{
public:
	Minvo(const Player*);
	Minvo(const Player*, const sf::Vector2i&);
	Minvo(const Player*, const sf::Vector2i&, const direction&);

	~Minvo();
private:
	void init(const sf::Vector2i&, const direction&);

	//Debounce counter to delay random heading changes
	int dirDebounce;

	bool chasePlayer;
};