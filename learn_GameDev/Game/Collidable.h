#pragma once
#include <SFML/Graphics.hpp>

/* This class should be inherited by other */
/* classes that will be colliding with anything */
class Collidable
{
public:

	/* Returns true if this intersects with other */
	bool check(Collidable& other);

	/* Does the same as check(Collidable&), */     
	/* but modifies the correction/offset accordingly */
	bool check(Collidable& other, sf::Vector2f& correction);

	/* Gets the bounds of the collider */
	const sf::FloatRect& getBounds() const;

	/* Returns a RectangleShape in case you want to draw the collision to the screen */
	sf::RectangleShape getVisualBounds();

protected:
	/* Updates the rect for the collidable */
	void updateRect(sf::FloatRect rect);

private:
	sf::FloatRect m_rect;
};