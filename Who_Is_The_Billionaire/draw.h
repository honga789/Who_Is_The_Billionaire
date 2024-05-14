#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "utils.h"

class draw {
private:
	static int preFontSize;

public:
	static std::vector<SDL_Texture*> loadedTexture;
	static std::map<std::string, int> loadedSrc;
	static SDL_Texture* getTexture(std::string src);

	static TTF_Font* mainFont;
	static std::vector<SDL_Texture*> loadedFontTexture;
	static std::map<std::pair<std::string, int>, int> loadedFont;
	static SDL_Texture* getFontTexture(
		std::string text, 
		int wrapLength,
		SDL_Color c = { 0, 0, 0 }
	);


	static void image(
		std::string src,
		SDL_Rect srcRect,
		SDL_Rect dsRect,
		double angle = 0,
		SDL_Point center = { 0, 0 }
	);

	static void fullImage(
		std::string src,
		SDL_Rect dsRect,
		double angle = 0,
		SDL_Point center = { 0, 0 }
	);

	static void rect(SDL_Rect rect, SDL_Color c);

	static void text(
		std::string text,
		int x, int y,
		int fontSize,
		int wrapLength,
		SDL_Color c = { 0, 0, 0 }
	);

	static void percentBar(
		int x, int y,
		int width, int height,
		int borderWidth,
		double currentValue, double maxValue,
		SDL_Color bgColor,
		SDL_Color activeColor,
		SDL_Color borderColor,
		bool isHorizontal = true
	);

};
