#pragma once
#include "Enemy.h"

class Valcom : public Enemy
{
public:
	Valcom();
	Valcom(const sf::Vector2i&);
	Valcom(const sf::Vector2i&, const directions&);

	virtual void move(Tile*[33][15], const sf::Vector2i&) override;

	~Valcom();
protected:
	virtual double getClippingMargin() const override;
	virtual int getMovementChance() const override;
private:
	void init(const sf::Vector2i&, const directions&);
};