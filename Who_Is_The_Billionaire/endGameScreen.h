#pragma once
#include "gameManager.h"
#include "menuButton.h"

class endGameScreen {
public:
	static void render();
	static void handleEvent(SDL_Event e);
	static void update();
	static menuButton* rePlayButton;
};

