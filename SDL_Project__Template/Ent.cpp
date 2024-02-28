#include <SDL.h>
#include <iostream>
#include "Ent.h"

//allows the main.cpp to render in the entities such as the player and the target ducks with their respective images
Ents::Ents(float e_x, float e_y, float e_w, float e_h, SDL_Texture* e_img)
	:x(e_x), y(e_y), w(e_w), h(e_h), imag(e_img)
{
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
}
