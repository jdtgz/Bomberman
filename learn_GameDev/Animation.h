#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
	public:
		Animation(); 
		Animation(sf::Texture&, sf::IntRect, int); 
		~Animation(); 

		void applyToSprite(sf::Sprite&) const; 
		void update(float); 

	private:
		void advance(); 

		int nFrames; 
		const int HOLDTIME = 0.1f; 
		sf::Texture texture; 
		sf::IntRect* frames; 
		int iFrame;
		float time; 
};

