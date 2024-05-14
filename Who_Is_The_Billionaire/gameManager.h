#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include <tuple>
#include <algorithm>
#include <time.h>
#include "constants.h"
#include "utils.h"
#include "draw.h"

class gameManager {
public:
    static bool isQuit;
    static constants::SCREEN_STATE gameState;
};