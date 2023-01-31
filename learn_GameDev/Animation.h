#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Animation
{
	public:
		Animation() = default; 
		Animation(sf::Texture&, int, int, int, int, int); 
		~Animation(); 

		void applyToSprite(sf::Sprite&) const; 
		void update(float); 

	private:
		void advance(); 

		int nFrames = 3; 
		static constexpr float HOLDTIME = 0.1f; 
		sf::Texture texture; 
		sf::IntRect* frames;
		int iFrame;
		float time; 
};

