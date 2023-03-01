#pragma once
#include "Enemy.h"

class Valcom : public Enemy
{
public:
	Valcom();

	virtual void update(const float&) override;
	virtual void move(Tile*[31][13], const sf::Vector2i&, const sf::Vector2i&) override;

	~Valcom();
private:
	bool vertical;
	bool positive;
};