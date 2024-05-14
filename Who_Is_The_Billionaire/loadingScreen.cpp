#include "loadingScreen.h"

double loadingScreen::timeCounter = 0;
double loadingScreen::timeLoading = 0;
constants::SCREEN_STATE loadingScreen::nextScreen = constants::NONE;
bool loadingScreen::isLoading = false;
double loadingScreen::percent = 0;

void loadingScreen::render()
{
	draw::fullImage("resources/images/mc_message.png", { 0, 0, constants::WIDTH, constants::HEIGHT });
	
	// draw mc message in a box;
	draw::text(constants::mcMessage + " " + constants::correctAns, 715, 150, 25, 230);

	//draw::percentBar(constants::WIDTH / 2, constants::HEIGHT / 2, 250, 25, 4,
	//	loadingScreen::percent, 100, { 255, 255, 255, 255 }, { 0, 0, 255, 255 }, { 0, 0, 0, 255 }
	//	);
}

void loadingScreen::update()
{
	static int frameCount = timeLoading / constants::DELTA_TIME;
	static double percentPerFrame = 100.0 / frameCount;
	percent += percentPerFrame;
	percent = (percent < 100) ? percent : 100;

	if (!isLoading)
		return;
	timeCounter += constants::DELTA_TIME;
	// add 2 delta time to loading to full percent bar
	if (timeCounter >= timeLoading + 2 * constants::DELTA_TIME)
	{
		gameManager::gameState = nextScreen;
		isLoading = false;
		timeCounter = 0;
		percent = 0;
	}
}

void loadingScreen::load(constants::SCREEN_STATE _nextScreen, double _timeLoading)
{
	isLoading = true;
	nextScreen = _nextScreen;
	timeLoading = _timeLoading;
}