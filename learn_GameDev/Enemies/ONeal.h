#pragma once
#include "Enemy.h"
#include "../Game/Player.h"

class ONeal : public Enemy
{
public:
	ONeal(const Player*);
	ONeal(const Player*, const sf::Vector2i&);
	ONeal(const Player*, const sf::Vector2i&, const directions&);

	virtual void update(const float&) override;
	virtual void move(Tile* [33][15], const sf::Vector2i&) override;

	~ONeal();
protected:
	virtual double getClippingMargin() const override;
	virtual int getMovementChance() const override;
	virtual int getChaseChance() const;
private:
	void init(const Player*, const sf::Vector2i&, const directions&);

	const Player* playerPointer;
	bool chasePlayer;
	int chaseDebounce = 0;
	const int CHASE_DEBOUNCE_MAX = 50;
};