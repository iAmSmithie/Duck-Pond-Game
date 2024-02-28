#include <SDL.h>
#include <iostream>
#include <Windows.h>

#include "Gun.h"
#include "duck.h"
#include "WindowRender.h"

Gun::Gun(float e_x, float e_y, float e_w, float e_h, SDL_Texture* e_img, int &points)
    : Ents(e_x, e_y, e_w, e_h, e_img), points(points)
{

}

float Gun::movement()
{
    //declares the boundaries of the game
    int minX = 0;
    int maxX = 900;
    int minY = 0;
    int maxY = 600;

    //the speed of the crosshair
    int speed = 2;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_A])
    {
        //std::cout << "A key pressed" << std::endl;
        if (getX() - speed >= minX) //Check if moving left is within the boundaries
            setX(getX() - speed);
        SDL_Delay(5);
    }

    if (keystate[SDL_SCANCODE_D])
    {
        //std::cout << "D key pressed" << std::endl;
        if (getX() + getW() + speed <= maxX) //Check if moving right is within the boundaries
            setX(getX() + speed);
        SDL_Delay(5);
    }

    if (keystate[SDL_SCANCODE_W])
    {
        //std::cout << "W key pressed" << std::endl;
        if (getY() - speed >= minY) //Check if moving up is within the boundaries
            setY(getY() - speed);
        SDL_Delay(5);
    }

    if (keystate[SDL_SCANCODE_S])
    {
        //std::cout << "S key pressed" << std::endl;
        if (getY() + getH() + speed <= maxY) //Check if moving down is within boundaries
            setY(getY() + speed);
        SDL_Delay(5);
    }

    return 0.0f;
}

bool Gun::crosshairOnDuck(const duck& targetDuck)
{
    //use the getters and setters to get the guns position and set it to the floats
    float gunX = getX() + getW() / 2.0f;
    float gunY = getY() + getH() / 2.0f; 

    //use the getters and setters to get the ducks position and set it to the floats
    float duckPosX = targetDuck.getX() + targetDuck.getW() / 2.0f;
    float duckPosY = targetDuck.getY() + targetDuck.getH() / 2.0f;

    //get the distance between the guns X and Y and the ducks X and Y
    float distanceX = gunX - duckPosX;
    float distanceY = gunY - duckPosY;
    //calculate the overall distance between the gun and the duck using the pythagorean theorem
    float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

    //sets the float duckRadius to the width of the duck
    float duckRadius = targetDuck.getW() / 2.0f;

    return distance <= duckRadius;
}

void Gun::LMBclick(const SDL_MouseButtonEvent& event, duck& targetDuck)
{
    //check if the left mouse button is pressed
    if (event.button == SDL_BUTTON_LEFT && event.state == SDL_PRESSED)
    {
        //checks if the player is aiming at the duck
        bool duckClicked = crosshairOnDuck(targetDuck);
        if (duckClicked)
        {
            //make the duck disappear
            targetDuck.setVisibility(false);
            // Add 1 to points
            points = points + 1;
            std::cout << points << std::endl;
        }
    }
}
