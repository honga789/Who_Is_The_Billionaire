#pragma once
#include "gameManager.h"

class button {
private:
	int x, y, w, h;

public:
	button(int _x, int _y, int _w, int _h);
	int getX();
	int getY();
	bool isPointInButton(int cx, int cy);
};

