#include "menuScreen.h"

menuButton* menuScreen::playButton = new menuButton(370, 540, 160, 100);

void menuScreen::render()
{
	draw::fullImage("resources/images/menu.jpg", { 0, 0, constants::WIDTH, constants::HEIGHT });
	playButton->render("resources/images/play_button_hover.png");
}

void menuScreen::handleEvent(SDL_Event e)
{
	switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if (menuScreen::playButton->isPointInButton(e.motion.x, e.motion.y))
			{
				gameManager::gameState = constants::SS_STAGE;
			}
	}
}

void menuScreen::update()
{
	if (menuScreen::playButton->isPointInButton(constants::MOUSE_X, constants::MOUSE_Y))
		menuScreen::playButton->onHover();
	else
		menuScreen::playButton->offHover();
}