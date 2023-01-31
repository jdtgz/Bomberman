#include "Animation.h"


Animation::Animation(sf::Texture& t)
{
	texture = t;
	nFrames = 0;
	iFrame = 0;
	time = 0.0f;
}


Animation::~Animation()
{
}


void Animation::initializeRects(int x, int y, int width, int height, int total)
{
	nFrames = total; 
	
	for (int i = 0; i < nFrames; i++)
	{
		frames.push_back(sf::IntRect(x, y + i * width, width, height));
	}
}


void Animation::applyToSprite(sf::Sprite& s) const
{
	s.setTexture(texture);
	s.setTextureRect(frames[iFrame]);
}


void Animation::update(float dt)
{
	time += dt; 
	while (time >= HOLDTIME)
	{
		time -= HOLDTIME; 
		advance(); 
	}
}


void Animation::advance()
{
	if (++iFrame >= nFrames)
	{
		iFrame = 0; 
	}
}