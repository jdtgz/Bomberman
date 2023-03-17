#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Animation
{
	public:
		// constructor/destructor
		Animation(); 
		~Animation(); 

		int getCurrentFrame() const { return iFrame; }

		// Given a texture, initial cords, box size, & number of frames,
		// set all the frames in the animaiton
		void setUp(sf::Texture&, const int&, const int&,
			const int&, const int&, const int&);

		// apply the current frame to a sprite
		void applyToSprite(sf::Sprite&) const; 

		// cycle animation based on time in-game
		void update(const float&); 

		// shows animation once by stopping the looping
		void showOnce(); 

	private:
		// cycles to the next frame in frames
		void advance(); 

		// total number of frames in animation
		int nFrames; 
		// amount of time a single frame will be on screen
		static constexpr float HOLDTIME = 0.1f; 
		// image to pull sprite rects from 
		sf::Texture* texture; 
		// array of IntRects that contain boxes of each frame 
		sf::IntRect* frames;
		// current frames in cycle
		int iFrame;
		// counter to track how long a single frame has been on screen
		float time; 
		// looping var
		bool looping; 
};