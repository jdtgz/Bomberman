#pragma once
#include <SFML/Graphics.hpp>

/* This class should be inherited by other 
classes that will be colliding with anything */
class Collidable
{
public:

	bool check(Collidable& other);
	bool check(Collidable& other, sf::Vector2f& correction);
	const sf::FloatRect& getBounds() const;
	sf::RectangleShape getVisualBounds();

protected:
	void updateRect(sf::FloatRect rect);

private:
	sf::FloatRect m_rect;
};