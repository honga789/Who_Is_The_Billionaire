#include "menuButton.h"


menuButton::menuButton(int _x, int _y, int _w, int _h) : 
	x(_x), y(_y), w(_w), h(_h) {}

void menuButton::render(std::string src)
{
	if (isHover)
		draw::fullImage(src, { 0, 0, constants::WIDTH, constants::HEIGHT });
}

bool menuButton::isPointInButton(int cx, int cy)
{
	if (cx < x)
		return false;
	if (cx > x + w)
		return false;
	if (cy < y)
		return false;
	if (cy > y + h)
		return false;
	return true;
}

void menuButton::onHover()
{
	isHover = true;
}

void menuButton::offHover()
{
	isHover = false;
}