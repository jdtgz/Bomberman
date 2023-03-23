#pragma once
#include "Enemy.h"

class ONeal : public Enemy
{
public:
	ONeal(const Player*);
	ONeal(const Player*, const sf::Vector2i&);
	ONeal(const Player*, const sf::Vector2i&, const directions&);

	virtual void move(Tile* [33][15]) override;

	~ONeal();
protected:
	virtual double clippingMargin() const override;
private:
	void init(const sf::Vector2i&, const directions&);
	int dirDebounce;
};