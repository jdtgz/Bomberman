#include "Animation.h"


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


// destructor
Animation::~Animation()
{
	delete[] frames;
}


// Initializes the TextureRects of the animation
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


// applyies the right textureRect to the animation and scales it
void Animation::applyToSprite(sf::Sprite& s) const
{
	s.setTexture(*texture);
	s.setTextureRect(frames[iFrame]);
	s.setScale(3, 3); 
}


// cycle animation based on dt
void Animation::update(const float& dt)
{
	time += dt; 
	while (time >= HOLDTIME)
	{
		time -= HOLDTIME; 
		advance(); 
	}
}


// makes a animation cycle once  
void Animation::showOnce()
{
	looping = false; 
}


// return the currently frame being displayed
int Animation::getCurrentFrame() const
{
	return iFrame; 
}


// advances the frame of the animation
void Animation::advance()
{
	if (++iFrame >= nFrames)
	{
		if(looping)
			iFrame = 0; 
	}
}