#pragma once
#include <SFML/Graphics.hpp>

class Collidable
{
public:

	//Returns true if this intersects with other
	bool check(Collidable& other);

	//Does the same as check(Collidable&), 
	//but modifies the velocity accordingly
	bool check(Collidable& other, sf::Vector2f& correction, const sf::Vector2f& velocity);

	const sf::FloatRect& getBounds() const;
	sf::RectangleShape getVisualBounds();

protected:
	void updateRect(sf::FloatRect rect);

private:
	sf::FloatRect m_rect;
};