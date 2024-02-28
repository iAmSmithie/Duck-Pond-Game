#pragma once
#include <SDL.h>
#include <iostream>

//this class handles the positions and what image file the entities use, they have setters and getters. these are used to retrieve and set variable values and allow private data
//to be accessed when needed
class Ents
{
public:
	Ents(float e_x, float e_y, float e_w, float e_h, SDL_Texture* e_img);

	void setX(float set_x) 
	{ 
		x = set_x; 
	}
	void setY(float set_y) 
	{ 
		y = set_y; 
	}

	float getX() const 
	{ 
		return x; 
	}
	float getY() const 
	{ 
		return y; 
	}
	float getW() const 
	{ 
		return w; 
	}
	float getH() const 
	{ 
		return h; 
	}
	SDL_Texture* getTexture() const 
	{ 
		return imag;
	}
	SDL_Rect getPos() const 
	{ 
		return pos;
	}
private:
	float x, y;
	float w, h;
	SDL_Rect pos;
	SDL_Texture* imag;
};