#include "Collidable.h"
#include <iostream>

bool Collidable::check(Collidable& other)
{
    return m_rect.intersects(other.m_rect);
}

bool Collidable::check(Collidable& other, sf::Vector2f& v_correction, const sf::Vector2f& velocity)
{
    sf::FloatRect inter;
    if (m_rect.intersects(other.m_rect, inter))
    {
        float this_left = m_rect.left;
        float this_right = m_rect.left + m_rect.width;
        float this_top = m_rect.top;
        float this_bottom = m_rect.top + m_rect.height;

        float other_left = other.m_rect.left;
        float other_right = other.m_rect.left + other.m_rect.width;
        float other_top = other.m_rect.top;
        float other_bottom = other.m_rect.top + other.m_rect.height;

        float left_intersect = -(this_right - other_left) - 0.1;
        float right_intersect = -(this_left - other_right) + 0.1;
        float top_intersect = -(this_bottom - other_top) - 0.1;
        float bottom_intersect = -(this_top - other_bottom) + 0.1;

        float c = 20;

        if (inter.height > c && inter.width < c)
        {
            if (inter.left == other_left)
                v_correction.x = left_intersect;
            else
                v_correction.x = right_intersect;
        }
        else if (inter.width > c)
        {
            if (inter.top == other_top)
                v_correction.y = top_intersect;
            else
                v_correction.y = bottom_intersect;
        }

        return true;
    }

    return false;
}

const sf::FloatRect& Collidable::getBounds() const
{
    return m_rect;
}

sf::RectangleShape Collidable::getVisualBounds()
{
    sf::RectangleShape temp({ m_rect.width, m_rect.height });

    temp.setFillColor(sf::Color::Transparent);
    temp.setOutlineColor(sf::Color::Blue);
    temp.setOutlineThickness(1);

    return temp;
}

void Collidable::updateRect(sf::FloatRect rect)
{
    m_rect = rect;
}