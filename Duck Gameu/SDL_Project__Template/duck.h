#pragma once
#include <SDL.h>
#include <iostream>

#include "Ent.h"
#include "duck.h"

//this class handles the functions of the duck that allow it to dissapear and spawn in random locations, its a child class of ents which means it uses inheritance to take the
//have access to all the attributes and functions from Ents
class duck : public Ents
{
public:
	duck(float r_x, float r_y, float r_w, float r_h, SDL_Texture* r_img);

	void setVisibility(bool visible);
	void updateVisibility();
	bool isVisible() const;
private:
	bool duckVisible = false;
	int lastTp;
};
