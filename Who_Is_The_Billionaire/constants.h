#pragma once
#include <SDL_mixer.h>
#include <string>

class constants {
public:
    static int WIDTH;
    static int HEIGHT;
    static std::string TITLE;
    static enum SCREEN_STATE {
        SS_MENU,
        SS_LOADING,
        SS_STAGE,
        SS_END,
        NONE
    };
    static int MOUSE_X;
    static int MOUSE_Y;
    static int FPS;
    static double DELTA_TIME;
    static std::string mcMessage;
    static std::string correctAns;
    static std::string endMessage;
    static Mix_Music* bgMusic;
    static Mix_Chunk* correctMusic;
    static Mix_Chunk* wrongMusic;
};

