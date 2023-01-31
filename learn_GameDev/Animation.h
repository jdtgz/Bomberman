#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Animation
{
	public:
		Animation() = default;
		Animation(sf::Texture&);
		~Animation(); 

		void initializeRects(int, int, int, int, int);
		void applyToSprite(sf::Sprite&) const; 
		void update(float); 

	private:
		void advance(); 

		int nFrames; 
		static constexpr float HOLDTIME = 0.1f; 
		sf::Texture texture; 
		std::vector<sf::IntRect> frames;
		int iFrame;
		float time; 
};

