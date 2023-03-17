#include "Animation.h"


// destructor
// testing notifications on webhook // testing again
Animation::~Animation()
{
	delete[] frames;
}


// default constructor
Animation::Animation()
{  
	texture = nullptr; 
	frames = nullptr; 
	nFrames = 0; 
	iFrame = 0;
	time = 0.0f; 
	looping = true; 
}


void Animation::setUp(sf::Texture& t, const int& x, const int& y,
	const int& width, const int& height, const int& tFrames)
{
	texture = &t;
	nFrames = tFrames;
	frames = new sf::IntRect[nFrames];

	// cycle through and initialize all the frames 
	// *No spacing between sprite boxes 
	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = sf::IntRect(x + i * width, y, width, height);
	}
}


void Animation::applyToSprite(sf::Sprite& s) const
{
	s.setTexture(*texture);
	s.setTextureRect(frames[iFrame]);
	s.setScale(3, 3); 
}


void Animation::update(const float& dt)
{
	time += dt; 
	while (time >= HOLDTIME)
	{
		time -= HOLDTIME; 
		advance(); 
	}
}


void Animation::showOnce()
{
	looping = false; 
}


void Animation::advance()
{
	if (++iFrame >= nFrames)
	{
		if(looping)
			iFrame = 0; 
	}
}