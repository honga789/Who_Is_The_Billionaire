#include "endGameScreen.h"
#include "stageScreen.h"

menuButton* endGameScreen::rePlayButton = new menuButton(300, 515, 180, 70);

void endGameScreen::render()
{
	draw::fullImage("resources/images/endgame.png", { 0, 0, constants::WIDTH, constants::HEIGHT });
	draw::fullImage("resources/images/replay.png", { 0, 0, constants::WIDTH, constants::HEIGHT });
	draw::text(constants::endMessage, 340, 280, 60, 500, { 255, 255, 255 });
	rePlayButton->render("resources/images/replay-hover.png");
}

void endGameScreen::handleEvent(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (endGameScreen::rePlayButton->isPointInButton(e.motion.x, e.motion.y))
		{
			stageScreen::setIsInit(false);
			constants::mcMessage = "";
			constants::correctAns = "";
			constants::endMessage = "";

			gameManager::gameState = constants::SS_STAGE;
		}
	}
}

void endGameScreen::update()
{
	if (endGameScreen::rePlayButton->isPointInButton(constants::MOUSE_X, constants::MOUSE_Y))
		endGameScreen::rePlayButton->onHover();
	else
		endGameScreen::rePlayButton->offHover();
}

