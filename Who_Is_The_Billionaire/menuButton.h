#pragma once
#include "gameManager.h"	

class menuButton {
private:
	int x, y, w, h;
	bool isHover = false;

public:
	menuButton(int _x, int _y, int _w, int _h);
	void render(std::string src);
	bool isPointInButton(int cx, int cy);
	void onHover();
	void offHover();
};

