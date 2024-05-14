#include "button.h"

button::button(int _x, int _y, int _w, int _h) :
	x(_x), y(_y), w(_w), h(_h) {}

int button::getX()
{
	return x;
}

int button::getY()
{
	return y;
}

bool button::isPointInButton(int cx, int cy)
{
	if (cx < x - (w / 2))
		return false;
	if (cx > x + (w / 2))
		return false;
	if (cy < y - (h / 2))
		return false;
	if (cy > y + (h / 2))
		return false;
	return true;
}
