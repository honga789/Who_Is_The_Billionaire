#pragma once
#include "gameManager.h"
#include "loadingScreen.h"
#include "question.h"
#include "button.h"

class stageScreen {
private:
	static bool isFirstPlay;
	static bool isInit;
	static std::vector<question> easyQues;
	static std::vector<question> hardQues;
	static question curQues;
	static std::vector<std::string> curAns;
	static int ans;
	static button* buttonA;
	static button* buttonB;
	static button* buttonC;
	static button* buttonD;
	static button* help1;
	static button* help2;
	static button* help3;
	static int isUsedHelp1;
	static int isUsedHelp2;
	static int isUsedHelp3;
	static std::string messHelp;
	static int numLevel;
	static std::vector<std::string> strLevel;
	static std::vector<std::string> mcMess;
	static double timeLimit;
	static double timeCounter;
	static bool isTiming;

	static question getRandomQues(bool isEasy = true);
	static void loadQues();
	static std::string help1Handle();
	static std::string help2Handle();
	static std::string help3Handle();

public:
	static void setIsInit(bool _IsInit);
	static void initStage();
	static void render();
	static void handleEvent(SDL_Event e);
	static void update();
};

