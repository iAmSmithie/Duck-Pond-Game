#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>

#include "Ent.h"
#include "duck.h"
#include "WindowRender.h"
//just like the duck.h it inherits the attributes and functions from Ents to allow it to spawn in, it also contains the fuction to check if the player is aiming at the duck,
//left mouse button clicks and movement. it also stores the points gotten from shooting ducks
class Gun : public Ents
{
public:
	Gun(float e_x, float e_y, float e_w, float e_h, SDL_Texture* e_img, int &points);

	bool crosshairOnDuck(const duck& targetDuck);
	void LMBclick(const SDL_MouseButtonEvent& event, duck& targetDuck);
	float movement();
private:
	int &points;

};
