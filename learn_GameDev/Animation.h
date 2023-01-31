#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Animation
{
	public:
		Animation(sf::Texture&, int, int, int, int); 
		~Animation(); 

		void initializeRects(int, int, int, int, int);
		void applyToSprite(sf::Sprite&) const; 
		void update(float); 

	private:
		void advance(); 

		static constexpr int nFrames = 3; 
		static constexpr float HOLDTIME = 0.1f; 
		sf::Texture texture; 
		sf::IntRect frames[nFrames];
		int iFrame;
		float time; 
};

