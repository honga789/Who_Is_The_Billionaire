#include "utils.h"

SDL_Window* utils::window = SDL_CreateWindow (
    constants::TITLE.c_str(),
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    constants::WIDTH,
    constants::HEIGHT,
    SDL_WINDOW_SHOWN
);

SDL_Renderer* utils::renderer = SDL_CreateRenderer (
    utils::window, -1, 0
);