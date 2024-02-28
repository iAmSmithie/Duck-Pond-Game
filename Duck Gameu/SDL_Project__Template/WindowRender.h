#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Ent.h"
#include "Gun.h"

//this class holds the functions used by the main.cpp, these functions contain the code to allow the program to run images, audio files and the window.
//they have private and public to protect data and keep it secure
class WindowRender
{
public:
	WindowRender(const char* _name, int _w, int _h);
	SDL_Texture* loadTexture(const char* _file);
	void CleanRAM();
	void clearscreen();
	void renderer(Ents& p_entity);
	void renderBackgrounds(SDL_Texture* texture);
	void display();
	void playMusic();
	void stopMusic();
	void gunShot();
private:
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Surface* Surface = NULL;

	Mix_Music* backgroundMusic = nullptr;
	Mix_Chunk* bang = nullptr;
};
