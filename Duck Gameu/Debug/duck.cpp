#include <SDL.h>
#include <iostream>

#include "duck.h"
#include "Gun.h"
#include <cstdlib>

duck::duck(float r_x, float r_y, float r_w, float r_h, SDL_Texture* r_img)
    : Ents(r_x, r_y, r_w, r_h, r_img), duckVisible(false)
{
    lastTp = SDL_GetTicks();
}

void duck::updateVisibility()
{
    //the time to wait before teleporting again
    const int teleportDelay = 1000;

    //the time the duck will stay visible before disappearing
    const int visibilityDuration = 2000;

    //get the amount of time the games been running for
    int currentTime = SDL_GetTicks();

    //used to spawn in the duck in random locations by checking if its visible and if enough time has passed since the last spawn
    if (!duckVisible && (currentTime - lastTp >= teleportDelay))
    {
        //spawn the duck at a random position within the selected x and y values
        float duckX = float(rand() % static_cast<int>(800 - getW()));
        float duckY = float(rand() % static_cast<int>(500 - getH())); 


        //the ducks current x and y position
        setX(duckX);
        setY(duckY);

        duckVisible = true;
        //update the lastTp integer so the program knows when the last teleport was
        lastTp = currentTime;
    }
    //checks if the duck has been visible for more than 2 seconds
    if (duckVisible && (currentTime - lastTp >= visibilityDuration))
    {
        duckVisible = false;
        //update the lastTp integer so the program knows when the last teleport was
        lastTp = currentTime;
    }
}
//function to make the duck dissapear
void duck::setVisibility(bool visible)
{
    duckVisible = visible;
}
//return the duckVisible boolean
bool duck::isVisible() const
{
    return duckVisible;
}