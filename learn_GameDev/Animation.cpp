#include "Animation.h"


// destructor
// testing notifications on webhook
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
}


void Animation::setUp(sf::Texture& t, int x, int y, int width, int height, int tFrames)
{
	texture = &t;
	nFrames = tFrames;
	frames = new sf::IntRect[nFrames];

	// cycle through and initialize all the frames 
	// *No spacing between sprite boxes 
	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = sf::IntRect(x + i * width, y, width, height);

		std::cout << frames[i].top << " " << frames[i].left << " "
			<< frames[i].height << " " << frames[i].width << " \n";
	}
}


void Animation::applyToSprite(sf::Sprite& s) const
{
	s.setTexture(*texture);
	s.setTextureRect(frames[iFrame]);
	s.setScale(5, 5); 
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