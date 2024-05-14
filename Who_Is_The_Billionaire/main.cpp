#include <iostream>
#include "gameManager.h"
#include "menuScreen.h"
#include "loadingScreen.h"
#include "stageScreen.h"
#include "endGameScreen.h"

#pragma execution_character_set("utf-8")

void initSDL();
void gameLoop();
void destroySDL();

int main(int argc, char* argv[])
{
    initSDL();
    gameLoop();
    destroySDL();
    return 0;
}

void initSDL()
{
    srand((int)time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void gameLoop()
{
    Mix_Music* welcome = Mix_LoadMUS("resources/sounds/welcome.wav");
    Mix_PlayMusic(welcome, 0);
    SDL_Event e;
    while (!gameManager::isQuit)
    {
        SDL_PollEvent(&e);
        switch(e.type)
        {
            case SDL_QUIT:
                gameManager::isQuit = true;
                return;
            case SDL_MOUSEMOTION:
                constants::MOUSE_X = e.motion.x;
                constants::MOUSE_Y = e.motion.y;
                break;
        }
        //std::cout << constants::MOUSE_X << " " << constants::MOUSE_Y << std::endl;
        //std::cout << menuScreen::playButton->isPointInButton(constants::MOUSE_X, constants::MOUSE_Y) << std::endl;
        
        switch (gameManager::gameState)
        {
            case constants::SS_MENU:
                menuScreen::render();
                menuScreen::handleEvent(e);
                menuScreen::update();
                break;

            case constants::SS_STAGE:
                stageScreen::initStage();
                stageScreen::render();
                stageScreen::handleEvent(e);
                stageScreen::update();
                break;

            case constants::SS_LOADING:
                loadingScreen::render();
                loadingScreen::update();
                break;

            case constants::SS_END:
                endGameScreen::render();
                endGameScreen::handleEvent(e);
                endGameScreen::update();
                break;
        }
        SDL_RenderPresent(utils::renderer);

        // convert constants::DELTA_TIME from second to milisecond
        SDL_Delay(constants::DELTA_TIME * 1000);
    }
}

void destroySDL()
{
    SDL_DestroyWindow(utils::window);
    SDL_DestroyRenderer(utils::renderer);
    SDL_Quit();
    TTF_Quit();
}