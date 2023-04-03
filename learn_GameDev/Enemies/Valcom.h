#pragma once
#include "Enemy.h"

class Valcom : public Enemy
{
public:
	Valcom(const Player*);
	Valcom(const Player*, const sf::Vector2i&);
	Valcom(const Player*, const sf::Vector2i&, const directions&);

	virtual void move(Tile*[33][15]) override;

	~Valcom();
protected:
	virtual double clippingMargin() const override;
private:
	void init(const sf::Vector2i&, const directions&);
	int dirDebounce;
};