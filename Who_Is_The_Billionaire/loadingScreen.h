#pragma once
#include "gameManager.h"

class loadingScreen {
private:
	static double timeCounter;
	static double timeLoading;
	static constants::SCREEN_STATE nextScreen;
	static bool isLoading;
	static double percent;

public:
	static void render();
	static void update();
	static void load(constants::SCREEN_STATE, double _timeLoading = 2);
};

