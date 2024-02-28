#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <SDL_mixer.h>

#include "WindowRender.h"
#include "Ent.h"
#include "Gun.h"
#include "duck.h"

//the functions used to run the game, display the menu and the results
void runGame(WindowRender& window, bool& Gamestart);
void displayMenu(WindowRender& window, bool& Gamestart);
bool displayResults(WindowRender& window, int &points);

int main(int argc, char* argv[])
{
    //intialises all SDL subsystems and audio with a check to see if its loaded properly
    if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) == -1)
    {
        std::cout << "SDL video failed to load :(" << SDL_GetError() << std::endl;
        return 1;
    }
    //sets up the audios frequency, format, channels and chunk sizes, also has a check to see if its opened properly
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cout << "audio failed to open :( " << Mix_GetError() << std::endl;
        return 0;
    }
    //renders the window onto the screen and sets bool Gamestart to false so the it does not load
    WindowRender window("Duck Murder Game", 900, 600);
    bool Gamestart = false;
    //runs the displayMenu function which displays the menu
    displayMenu(window, Gamestart);
    //loads the CleanRAM function
    window.CleanRAM();
    //cleans up all initialised subsystems
    SDL_Quit();
    return 0;

}
//creates an enum class for the menu and creates a set of constants
enum class MenuOption
{
	PLAY,
	INSTRUCTIONS, 
	QUIT
};

void displayMenu(WindowRender& window, bool& Gamestart)
{
    //load the menu and the instructions for rendering
    SDL_Texture* menu = window.loadTexture("game-menu.bmp");
    SDL_Texture* inst = window.loadTexture("inst.bmp");
    //set bools to false or true to allow the menu loop to run but not the game
    bool menuShown = true;
    bool gameOver = true;
    bool start = false;
    bool showInstructions = false;
    Gamestart = false;
    SDL_Event event;

    //the loop for the menu so it stays open
    while (menuShown)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                menuShown = false;
                break;
            }
            //this waits for the user to either press 1,2 or 3 on the keyboard to either start the game, show the instructions or quit the game.
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_1:
                    //displays "Play option selected." on the console for debugging (if uncommented) and goes to the runGame function and sets the menuShown to false so it does not run the loop again
                    std::cout << "Play option selected." << std::endl;
                    runGame(window, Gamestart);
                    menuShown = false;
                    break;
                case SDLK_2:
                    //displays "Instructions option selected." for debugging (if uncommented) and sets showInstructions to true so that loop runs.
                    std::cout << "Instructions option selected." << std::endl;
                    showInstructions = true;
                    break;
                case SDLK_3:
                    //displays "Quit option selected." for debugging (if uncommented), destroys the window and closes SDL. also sets menuShown to false to stop the loop
                    std::cout << "Quit option selected." << std::endl;
                    window.CleanRAM();
                    SDL_QUIT;
                    menuShown = false;
                    break;
                default:
                    break;
                }
            }
        }
        //keeps the menuShown to true so when its returned to after a game it runs again, also display the menu background.
        menuShown = true;
        window.clearscreen();
        window.renderBackgrounds(menu);
        window.display();

        //checks if the showInstructions bool is true, if yes display the instrucions and wait till E is pressed, if yes return to the menu
        if (showInstructions)
        {
            window.renderBackgrounds(inst);
            window.display();

            while (showInstructions) 
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        menuShown = false;
                        showInstructions = false;
                        break;
                    }
                    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
                    {
                        showInstructions = false;
                    }
                }
            }
        }
    }
    //start the game and destroy the menu texture
    Gamestart = true;
    SDL_DestroyTexture(menu);
}

void runGame(WindowRender& window, bool& Gamestart)
{
    //set up the srand so the game can have randomised duck spawns also sets points to 0 at the start of the game and declare the games duration to 30 seconds. also play background music
    srand(time(nullptr));
    int points = 0;
    bool gameOver = false;
    bool backToMenu = false;
    const int gameDuration = 30000; //30 seconds
    int gameStartTime = SDL_GetTicks();
    window.playMusic();

    //load the textures for all the images that are going to be displayed
    SDL_Texture* background = window.loadTexture("carnivalBackground.bmp");
    SDL_Texture* crosshair = window.loadTexture("crosshair.bmp");
    SDL_Texture* target = window.loadTexture("targetDuck.bmp");
    SDL_Texture* win = window.loadTexture("winning.bmp");
    SDL_Texture* lose = window.loadTexture("losing.bmp");

    //set the entities position, size and texture
    Ents playArea(0, 0, 900, 600, background);
    Ents winnin(0, 0, 100, 100, win);
    Ents losin(0, 0, 100, 100, lose);
    Gun player(0, 0, 100, 100, crosshair, points);
    duck targetDuck(0, 0, 100, 100, target);

    //set the bool for left mouse button to false and game over to false so they dont run and get the time of the start of the game, also display points (if std::cout is uncommented) for debugging
    bool leftMouseButtonPressed = false;
    gameOver = false;
    int currentTime = SDL_GetTicks();
    std::cout << points << std::endl;

    //the loop for the game so it stays open
    while (!gameOver)
    {
        //checks if the game has ended, if yes stop the music and SFX, stop the game loop and run the displayResults function
        if (currentTime - gameStartTime >= gameDuration)
        {
            window.stopMusic();
            gameOver = true;
            bool returnToMenu = displayResults(window, points);
            Gamestart = !returnToMenu;
        }
        //another loop to continuously check for LMB clicks, if yes run the gunshot function and the LMBclick function
        SDL_Event Q;
        while (SDL_PollEvent(&Q))
        {
            if (Q.type == SDL_QUIT)
            {
                Gamestart = false;
                return;
            }
            else if (Q.type == SDL_MOUSEBUTTONDOWN)
            {
                window.gunShot();
                player.LMBclick(Q.button, targetDuck);
            }
        }

        //functions used for updating the ducks visibility, players movement, clearing the screen up, rendering the player and the play area.
        window.clearscreen();
        targetDuck.updateVisibility();
        player.movement();
        window.renderer(playArea);
        window.renderer(player);
        
        //check if the isVisible bool is true, if yes render the duck in
        if (targetDuck.isVisible())
        {
            window.renderer(targetDuck);
        }
        //display all the previous changes and get the currentTime
        window.display();
        currentTime = SDL_GetTicks();
    }
}

bool displayResults(WindowRender& window, int &points)
{
    //load the end screen and the winning and losing textures, also set their positions and size. displays the points (if uncommented) for debugging
    SDL_Texture* endScreen = window.loadTexture("end-screen.bmp");
    SDL_Texture* winning = window.loadTexture("winning.bmp");
    SDL_Texture* losing = window.loadTexture("losing.bmp");
    Ents Endscreen(0, 0, 900, 600, endScreen);
    Ents winnin(0, 0, 100, 100, winning);
    Ents losin(0, 0, 100, 100, losing);
    std::cout << points << std::endl;

    bool returnToMenu = false;
    SDL_Event event;

    //a loop to keep the results up unless the user presses E on the keyboard
    while (!returnToMenu)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
            {
                returnToMenu = true;
            }
        }
        //clear the screen and display the end screen
        window.clearscreen();
        window.renderer(Endscreen);
        //check if points is greater than or equal to 20, if yes display the winning.bmp, if not display the losing.bmp
        if (points >= 20)
        {
            window.renderer(winnin);
        }
        else 
        {
            window.renderer(losin);
        }
        //display the changes
        window.display();
    }
    //return returnToMenu to be sent back to the menu
    return returnToMenu;
}
