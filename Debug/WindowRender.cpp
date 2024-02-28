#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "WindowRender.h"
#include "Ent.h"
#include "Gun.h"

//this allows the main.cpp to create a window using 3 parameters, the name of the window, the width and the height of the window
WindowRender::WindowRender(const char* _name, int _w, int _h)
	:window(NULL), render(NULL)
{
	//create the window with specified positions and dimentions, those are set in the main.cpp
	window = SDL_CreateWindow(_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _w, _h, SDL_WINDOW_SHOWN);

	//check to see if the window loads, if not diplay the std::cout
	if (window == NULL)
	{
		std::cout << "window failed to load " << SDL_GetError() << std::endl;
	}
	//create the renderer for the window to use
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* WindowRender::loadTexture(const char* _file)
{
	//create a surface from the bmp and the desired file and check if the surface has loaded, if not display the std::cout
	SDL_Surface* Surface = SDL_LoadBMP(_file);
	if (Surface == NULL)
	{
		std::cout << "failed to load image :( " << SDL_GetError() << std::endl;
		return NULL;
	}
	//create a texture that is used for rendering the images onto the screen
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, Surface);
	//free the surface for the image
	SDL_FreeSurface(Surface);

	return texture;
}

void WindowRender::CleanRAM()
{
	//destroys the window
	SDL_DestroyWindow(window);
}

void WindowRender::clearscreen()
{
	//clear the screen so theres nothing on it
	SDL_RenderClear(render);
}

void WindowRender::renderer(Ents& p_entity)
{
	//this is the starting point of the entitys
	SDL_Rect source;
	source.x = p_entity.getPos().x;
	source.y = p_entity.getPos().y;
	source.w = p_entity.getPos().w;
	source.h = p_entity.getPos().h;
	//this is the destination of the entitys,
	SDL_Rect destin;
	destin.x = p_entity.getX();
	destin.y = p_entity.getY();
	destin.w = p_entity.getW();
	destin.h = p_entity.getH();

	//tells the renderer to display the image onto the screen using the texture stated and the destination, this is for most entities that move around and do multiple things
	SDL_RenderCopy(render, p_entity.getTexture(), &source, &destin);
}

void WindowRender::renderBackgrounds(SDL_Texture* texture)
{
	//a more simple way of rendering images, for backgrounds as it does not handle the picture moving around
	SDL_RenderCopy(render, texture, nullptr, nullptr);
}

void WindowRender::display()
{
	//update the screen with all changes, this will make all the pictures, audio and visuals show onto the screen
	SDL_RenderPresent(render);
}

void WindowRender::playMusic()
{
	//loads up the background music file, has a check to make sure it loads properly
	backgroundMusic = Mix_LoadMUS("circusMusic.ogg");
	if (!backgroundMusic)
	{
		std::cout << "Failed to load background music: " << Mix_GetError() << std::endl;
		return;
	}
	//plays the background music
	if (Mix_PlayMusic(backgroundMusic, -1) == -1) 
	{
		std::cout << "music failed to play :( " << Mix_GetError() << std::endl;
		return;
	}
	//controls the volume of the music
	int volume = 30;
	Mix_VolumeMusic(volume);
}
void WindowRender::stopMusic()
{
	//checks to see if the music is playing then stops it and deletes it
	if (backgroundMusic)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(backgroundMusic);
		Mix_FreeChunk(bang);
		backgroundMusic = nullptr;
	}
}

void WindowRender::gunShot()
{
	//loads up and plays the gunshot audio
	bang = Mix_LoadWAV("gunshot.ogg");
	(Mix_PlayChannel(-1, bang, 0) == -1);
}
