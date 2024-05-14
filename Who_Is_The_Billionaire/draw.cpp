#include "draw.h"

int draw::preFontSize = 0;
std::vector<SDL_Texture*> draw::loadedTexture;
std::map<std::string, int> draw::loadedSrc;

SDL_Texture* draw::getTexture(std::string src)
{
	// ignore draw::loadedTexture[0]
	if (draw::loadedTexture.size() <= 0)
		draw::loadedTexture.push_back(nullptr);

	if (draw::loadedSrc[src] != 0)
		return draw::loadedTexture[loadedSrc[src]];

	SDL_Surface* surface = IMG_Load(src.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(utils::renderer, surface);
	SDL_FreeSurface(surface);
	draw::loadedSrc[src] = draw::loadedTexture.size();
	draw::loadedTexture.push_back(texture);

	return texture;
}

TTF_Font* draw::mainFont = NULL;
std::vector<SDL_Texture*> draw::loadedFontTexture;
std::map<std::pair<std::string, int>, int> draw::loadedFont;

SDL_Texture* draw::getFontTexture(std::string text, int wrapLength, SDL_Color c)
{
	// ignore draw::loadedFontTexture[0]
	if (draw::loadedFontTexture.size() <= 0)
		draw::loadedFontTexture.push_back(nullptr);
	
	if (draw::loadedFont[std::make_pair(text, wrapLength)])
		return draw::loadedFontTexture[loadedFont[std::make_pair(text, wrapLength)]];

	SDL_Surface* surface = TTF_RenderUTF8_Solid_Wrapped(draw::mainFont, text.c_str(), c, wrapLength);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(utils::renderer, surface);
	SDL_FreeSurface(surface);
	draw::loadedFont[std::make_pair(text, wrapLength)] = draw::loadedFontTexture.size();
	draw::loadedFontTexture.push_back(texture);

	return texture;
}

void draw::image(std::string src, SDL_Rect srcRect, SDL_Rect dsRect, double angle, SDL_Point center)
{
	SDL_RenderCopyEx(
		utils::renderer,
		draw::getTexture(src),
		&srcRect,
		&dsRect,
		angle,
		&center,
		SDL_FLIP_NONE
	);
}

void draw::fullImage(std::string src, SDL_Rect dsRect, double angle, SDL_Point center)
{
	int w, h;
	SDL_Texture* texture = draw::getTexture(src);
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	SDL_Rect srcRect = { 0, 0, w, h };

	SDL_RenderCopyEx(
		utils::renderer,
		texture,
		&srcRect,
		&dsRect,
		angle,
		&center,
		SDL_FLIP_NONE
	);
}

void draw::rect(SDL_Rect rect, SDL_Color c)
{
	SDL_SetRenderDrawBlendMode(utils::renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(utils::renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(utils::renderer, &rect);
}

void draw::text(std::string text, int x, int y, int fontSize, int wrapLength, SDL_Color c)
{

	if (draw::mainFont == NULL || draw::preFontSize != fontSize)
	{
		std::string mainFontSrc = "resources/fonts/OpenSans.ttf";
		draw::mainFont = TTF_OpenFont(mainFontSrc.c_str(), fontSize);
		draw::preFontSize = fontSize;
	}
	
	SDL_Texture* texture = draw::getFontTexture(text, wrapLength, c);
	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	SDL_Rect dsRect = { x - w / 2, y - h / 2, w, h };
	SDL_RenderCopy(utils::renderer, texture, nullptr, &dsRect);
}


void draw::percentBar(
	int x, int y,
	int width, int height,
	int borderWidth,
	double currentValue, double maxValue,
	SDL_Color bgColor,
	SDL_Color activeColor,
	SDL_Color borderColor,
	bool isHorizontal) 
{
	rect(
		{
			x - width / 2 - borderWidth,
			y - height / 2 - borderWidth,
			width + 2 * borderWidth,
			height + 2 * borderWidth
		},
		borderColor
	);

	rect(
		{
			x - width / 2,
			y - height / 2,
			width,
			height
		},
		bgColor
	);

	if (isHorizontal) {
		int percentBarWidth = width * currentValue / maxValue;
		rect(
			{
				x - width / 2,
				y - height / 2,
				percentBarWidth, height
			},
			{ 255, 0, 0 }
		);
	}
	else {
		int percentBarHeight = height * currentValue / maxValue;
		rect(
			{
				x - width / 2,
				y + height / 2 - percentBarHeight,
				width, percentBarHeight
			},
			{ 255, 0, 0 }
		);
	}
}
