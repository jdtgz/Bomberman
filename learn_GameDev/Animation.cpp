#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(sf::Texture& txt, sf::IntRect rect, int total)
{
	nFrames = total; 
	iFrame = 0; 
	time = 0.0f;
	texture = txt;
	frames = new sf::IntRect[nFrames]; 
}


Animation::~Animation()
{
	delete[] frames;
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