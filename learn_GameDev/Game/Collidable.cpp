#include "Collidable.h"
#include <iostream>


// Returns true if this intersects with other
bool Collidable::check(Collidable& other)
{
    return m_rect.intersects(other.m_rect);
}


// Does the same as check(Collidable&)   
// but modifies the correction/offset accordingly 
bool Collidable::check(Collidable& other, sf::Vector2f& v_correction)
{
    sf::FloatRect inter;
    if (m_rect.intersects(other.m_rect, inter))
    {
        // Calculate overlap along the x and y axes
        float overlapX = std::min(m_rect.left + m_rect.width,
                                  other.m_rect.left + other.m_rect.width) - 
                                  std::max(m_rect.left, other.m_rect.left);
        float overlapY = std::min(m_rect.top + m_rect.height,
                                  other.m_rect.top + other.m_rect.height) - 
                                  std::max(m_rect.top, other.m_rect.top);

        // Check for potential edge cases
        if (overlapX == 0.0f && overlapY == 0.0f)
        {
            // Objects are exactly on top of each other, resolve collision along y-axis
            if (m_rect.top < other.m_rect.top)
                v_correction.y = -overlapY;
            else
                v_correction.y = overlapY;
        }
        else if (overlapX == 0.0f)
        {
            // Objects are colliding vertically, resolve collision along y-axis
            if (m_rect.top < other.m_rect.top)
                v_correction.y = -overlapY;
            else
                v_correction.y = overlapY;
        }
        else if (overlapY == 0.0f)
        {
            // Objects are colliding horizontally, resolve collision along x-axis
            if (m_rect.left < other.m_rect.left)
                v_correction.x = -overlapX;
            else
                v_correction.x = overlapX;
        }
        else
        {
            // Objects are colliding diagonally, resolve collision along the axis with smaller overlap
            if (overlapX < overlapY)
            {
                if (m_rect.left < other.m_rect.left)
                    v_correction.x = -overlapX;
                else
                    v_correction.x = overlapX;
            }
            else
            {
                if (m_rect.top < other.m_rect.top)
                    v_correction.y = -overlapY;
                else
                    v_correction.y = overlapY;
            }
        }

        return true;
    }

    return false;
}


const sf::FloatRect& Collidable::getBounds() const
{
    return m_rect;
}


// Returns a RectangleShape in case you want to draw the collision to the screen 
sf::RectangleShape Collidable::getVisualBounds()
{
    sf::RectangleShape temp({ m_rect.width, m_rect.height });

    temp.setFillColor(sf::Color::Transparent);
    temp.setOutlineColor(sf::Color::Blue);
    temp.setOutlineThickness(1);

    return temp;
}


// Updates the rect for the collidable
void Collidable::updateRect(sf::FloatRect rect)
{
    m_rect = rect;
}