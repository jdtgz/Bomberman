#pragma once
#include "Enemy.h"

class Valcom : public Enemy
{
public:
	Valcom(const sf::Vector2i&);
	Valcom(const sf::Vector2i&, const dir&);

	virtual void update(const float&) override;
	virtual void move(Tile*[31][13], const sf::Vector2i&) override;

	~Valcom();
private:
	void init(const sf::Vector2i&, const dir&);

	const double CLIPPING_MARGIN = 2.5;
	int debounce;
	const int DEBOUNCE_MAX = 10;
};