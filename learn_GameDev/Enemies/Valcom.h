#pragma once
#include "Enemy.h"

class Valcom : public Enemy
{
public:
	Valcom(const sf::Vector2i&);
	Valcom(const sf::Vector2i&, const dir&);

	virtual void update(const float&) override;
	virtual void move(Tile*[33][15], const sf::Vector2i&) override;

	~Valcom();
private:
	int debounce = 0;
	const int DEBOUNCE_MAX = 10;

protected:
	virtual void init(const sf::Vector2i&, const dir&);
	virtual double getClippingMargin() const;
};