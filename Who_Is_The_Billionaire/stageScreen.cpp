#include "stageScreen.h"

bool stageScreen::isFirstPlay = true;
bool stageScreen::isInit = false;
std::vector<question> stageScreen::easyQues;
std::vector<question> stageScreen::hardQues;
question stageScreen::curQues;
std::vector<std::string> stageScreen::curAns;
int stageScreen::ans;
button* stageScreen::buttonA = new button(270, 550, 260, 40);
button* stageScreen::buttonB = new button(590, 550, 260, 40);
button* stageScreen::buttonC = new button(270, 640, 260, 40);
button* stageScreen::buttonD = new button(590, 640, 260, 40);
button* stageScreen::help1 = new button(690, 40, 60, 60);
button* stageScreen::help2 = new button(765, 40, 60, 60);
button* stageScreen::help3 = new button(835, 40, 60, 60);
int stageScreen::isUsedHelp1;
int stageScreen::isUsedHelp2;
int stageScreen::isUsedHelp3;
std::string stageScreen::messHelp;
int stageScreen::numLevel;
std::vector<std::string> stageScreen::strLevel;
std::vector<std::string> stageScreen::mcMess;
double stageScreen::timeLimit;
double stageScreen::timeCounter;
bool stageScreen::isTiming;

question stageScreen::getRandomQues(bool isEasy)
{
	if (isEasy)
	{
		int randId = (rand() % (int)stageScreen::easyQues.size());
		question res = stageScreen::easyQues[randId];
		stageScreen::easyQues.erase(stageScreen::easyQues.begin() + randId);
		return res;
	}
	int randId = (rand() % (int)stageScreen::hardQues.size());
	question res = stageScreen::hardQues[randId];
	stageScreen::hardQues.erase(stageScreen::hardQues.begin() + randId);
	return res;
}

void stageScreen::loadQues()
{
	std::ifstream fi;

	if (stageScreen::isFirstPlay)
	{
		fi.open("resources/level-and-mc-message.txt");

		std::string tmp;
		std::getline(fi, tmp);
		stageScreen::strLevel.push_back(tmp);
		for (int i = 1; i <= 15; ++i)
			stageScreen::strLevel.push_back(tmp + " " + std::to_string(i));
		stageScreen::strLevel.push_back(stageScreen::strLevel[15]);

		int x;
		fi >> x;
		fi.ignore();
		for (int i = 0; i < x; ++i)
		{
			std::string mess;
			std::getline(fi, mess);
			stageScreen::mcMess.push_back(mess);
		}

		fi.close();
	}

	if (!stageScreen::easyQues.empty())
		stageScreen::easyQues.clear();
	if (!stageScreen::hardQues.empty())
		stageScreen::hardQues.clear();

	fi.open("resources/data.txt");
	int n, m;
	fi >> n >> m;
	for (int i = 0; i < n + m; ++i)
	{
		fi.ignore();
		std::string q;
		std::getline(fi, q);
		std::string a[4];
		for (int i = 0; i < 4; ++i)
			std::getline(fi, a[i]);
		int x;
		fi >> x;
		std::swap(a[0], a[x]);
		if (i < n)
			stageScreen::easyQues.push_back(question(q, a));
		else
			stageScreen::hardQues.push_back(question(q, a));
	}
	fi.close();
}

std::string stageScreen::help1Handle()
{
	// 60 % correct,
	std::vector<int> v;
	v.push_back(rand() % 40 + 1);
	v.push_back(rand() % 40 + 1);
	v.push_back(rand() % 20 + 1);
	v.push_back(100 - (v[0] + v[1] + v[2]));
	std::sort(v.begin(), v.end(), std::greater<int>());
	int x = (rand() % 10 + 1);
	if (x <= 6)
	{
		for(int i = 0; i < 4; ++i)
			if (stageScreen::curQues.checkAns(stageScreen::curAns[i]))
			{
				std::swap(v[0], v[i]);
				break;
			}
	}
	else
	{
		if (stageScreen::curQues.checkAns(stageScreen::curAns[0]))
			std::swap(v[0], v[rand() % 3 + 1]);
	}
	std::string res = "";
	for (int i = 0; i < 4; ++i)
	{
		if (i == 0)
			res = "A: " + std::to_string(v[0]) + "%, ";
		else if (i < 3)
		{
			res.push_back((char)((int)'A' + i));
			res = res + ": " + std::to_string(v[i]) + "%, ";
		}
		else
			res = res + "D: " + std::to_string(v[3]) + "%.";
	}
	return res;
}

std::string stageScreen::help2Handle()
{
	// 80% correct;
	int x = rand() % 10 + 1;
	// stageScreen::mcMess[3] = "nguoi than cua ban chon dap an:"
	std::string res = stageScreen::mcMess[3];
	res.push_back(' ');
	if (x <= 8)
	{
		for (int i = 0; i < 4; ++i)
			if (stageScreen::curQues.checkAns(stageScreen::curAns[i]))
			{
				res.push_back((char)((int)'A' + i));
				break;
			}
		res.push_back('.');
	}
	else
	{
		for (int i = 0; i < 4; ++i)
			if (!stageScreen::curQues.checkAns(stageScreen::curAns[i]))
			{
				res.push_back((char)((int)'A' + i));
				break;
			}
		res.push_back('.');
	}
	return res;
}

std::string stageScreen::help3Handle()
{
	std::vector<std::string> v;
	for (int i = 0; i < 4; ++i)
		if (!stageScreen::curQues.checkAns(stageScreen::curAns[i]))
		{
			std::string tmp;
			tmp.push_back((char)((int)'A' + i));
			v.push_back(tmp);
		}
	std::random_shuffle(v.begin(), v.end());
	// stageScreen::mcMess[4] = "hai dap an sai la:"
	std::string res = stageScreen::mcMess[4];
	res = res + " " + v[0] + ", " + v[1] + ".";
	return res;
}

void stageScreen::setIsInit(bool _IsInit)
{
	stageScreen::isInit = _IsInit;
}

void stageScreen::initStage()
{
	if (stageScreen::isInit && stageScreen::numLevel > 15)
	{
		// stageScreen::mcMess[5] = "chuc mung ban da vuot qua cau:"
		constants::endMessage = stageScreen::mcMess[5] + " " + std::to_string(15);

		gameManager::gameState = constants::SS_END;
		return;
	}

	if (stageScreen::isInit)
		return;

	stageScreen::ans = -1;
	stageScreen::isUsedHelp1 = 0;
	stageScreen::isUsedHelp2 = 0;
	stageScreen::isUsedHelp3 = 0;
	stageScreen::numLevel = 1;
	stageScreen::timeLimit = 30 + 1;
	stageScreen::timeCounter = stageScreen::timeLimit;
	stageScreen::isTiming = true;

	if (stageScreen::isFirstPlay)
	{
		constants::bgMusic = Mix_LoadMUS("resources/sounds/lets-play.wav");
		Mix_PlayMusic(constants::bgMusic, -1);
		constants::correctMusic = Mix_LoadWAV("resources/sounds/corect-answer.wav");
		constants::wrongMusic = Mix_LoadWAV("resources/sounds/wrong-answer.wav");

		stageScreen::loadQues();
	}

	if (stageScreen::easyQues.size() < 5 || stageScreen::hardQues.size() < 10)
		stageScreen::loadQues();
	
	stageScreen::curQues = stageScreen::getRandomQues();
	stageScreen::curAns = stageScreen::curQues.getAns();

	stageScreen::isFirstPlay = false;
	stageScreen::isInit = true;
}

void stageScreen::render()
{
	draw::fullImage("resources/images/game_stage_bg.png", { 0, 0, constants::WIDTH, constants::HEIGHT });
	draw::text(std::to_string((int)stageScreen::timeCounter), 450, 30, 25, 100, { 255, 255, 255 });
	draw::text(stageScreen::strLevel[stageScreen::numLevel], 105, 215, 25, 120, {255, 255, 255});
	draw::text(stageScreen::curQues.getQues(), 430, 440, 25, 600, {255, 255, 255});
	draw::text("A: " + stageScreen::curAns[0], 270, 550, 25, 260);
	draw::text("B: " + stageScreen::curAns[1], 590, 550, 25, 260);
	draw::text("C: " + stageScreen::curAns[2], 270, 640, 25, 260);
	draw::text("D: " + stageScreen::curAns[3], 590, 640, 25, 260);
	if (stageScreen::isUsedHelp1 != 0)
		draw::text("XXX", 690, 40, 25, 100, { 255, 0, 0 });
	if (stageScreen::isUsedHelp2 != 0)
		draw::text("XXX", 765, 40, 25, 100, { 255, 0, 0 });
	if (stageScreen::isUsedHelp3 != 0)
		draw::text("XXX", 835, 40, 25, 100, { 255, 0, 0 });
	if (stageScreen::isUsedHelp1 == 1 || stageScreen::isUsedHelp2 == 1 || stageScreen::isUsedHelp3 == 1)
	{
		draw::fullImage("resources/images/mc_message.png", { 0, 0, constants::WIDTH, constants::HEIGHT });
		draw::text(stageScreen::messHelp, 715, 150, 25, 230);
	}
	if (stageScreen::ans != -1)
	{
		// stageScreen::mcMess[6] = "Ban dang chon dap an:"
		std::string choosenAns = stageScreen::mcMess[6] + " ";
		choosenAns.push_back((char)((int)'A' + stageScreen::ans));
		// stageScreen::mcMess[7] = "An Enter de xac nhan!"
		choosenAns += ". " + stageScreen::mcMess[7];
		draw::fullImage("resources/images/mc_message.png", { 0, 0, constants::WIDTH, constants::HEIGHT });
		draw::text(choosenAns, 715, 150, 25, 230);
	}
}

void stageScreen::handleEvent(SDL_Event e)
{
	switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if (stageScreen::buttonA->isPointInButton(e.motion.x, e.motion.y))
			{
				//std::cout << "A. " + stageScreen::curAns[0] << std::endl;
				stageScreen::ans = 0;
			}
			else if (stageScreen::buttonB->isPointInButton(e.motion.x, e.motion.y))
			{
				//std::cout << "B. " + stageScreen::curAns[1] << std::endl;
				stageScreen::ans = 1;
			}
			else if (stageScreen::buttonC->isPointInButton(e.motion.x, e.motion.y))
			{
				//std::cout << "C. " + stageScreen::curAns[2] << std::endl;
				stageScreen::ans = 2;
			}
			else if (stageScreen::buttonD->isPointInButton(e.motion.x, e.motion.y))
			{
				//std::cout << "D. " + stageScreen::curAns[3] << std::endl;
				stageScreen::ans = 3;
			}
			else if (stageScreen::isUsedHelp1 == 0 && stageScreen::help1->isPointInButton(e.motion.x, e.motion.y))
			{
				stageScreen::isUsedHelp1 = 1;
				stageScreen::messHelp = stageScreen::help1Handle();
				stageScreen::ans = -1;
			}
			else if (stageScreen::isUsedHelp2 == 0 && stageScreen::help2->isPointInButton(e.motion.x, e.motion.y))
			{
				stageScreen::isUsedHelp2 = 1;
				stageScreen::messHelp = stageScreen::help2Handle();
				stageScreen::ans = -1;
			}
			else if (stageScreen::isUsedHelp3 == 0 && stageScreen::help3->isPointInButton(e.motion.x, e.motion.y))
			{
				stageScreen::isUsedHelp3 = 1;
				stageScreen::messHelp = stageScreen::help3Handle();
				stageScreen::ans = -1;
			}
	}
			
	int flag = -1;
	if (stageScreen::ans != -1 && e.key.keysym.sym == SDLK_RETURN)
	{
		flag = stageScreen::curQues.checkAns(stageScreen::curAns[stageScreen::ans]);
		stageScreen::ans = -1;
	}

	if (flag == 1)
	{
		stageScreen::numLevel++;
		if (stageScreen::numLevel <= 15)
		{
			if (stageScreen::numLevel <= 5)
				stageScreen::curQues = stageScreen::getRandomQues(true);
			else
				stageScreen::curQues = stageScreen::getRandomQues(false);
			stageScreen::curAns = stageScreen::curQues.getAns();

			stageScreen::timeCounter = stageScreen::timeLimit;

			if (stageScreen::isUsedHelp1 == 1)
				stageScreen::isUsedHelp1 = 2;

			if (stageScreen::isUsedHelp2 == 1)
				stageScreen::isUsedHelp2 = 2;

			if (stageScreen::isUsedHelp3 == 1)
				stageScreen::isUsedHelp3 = 2;
		}
		// stageScreen::mcMess[0] = correct answer;
		constants::mcMessage = stageScreen::mcMess[0];

		Mix_PlayChannel(-1, constants::correctMusic, 0);
				
		gameManager::gameState = constants::SS_LOADING;
		loadingScreen::load(constants::SS_STAGE, 3);
	}
	else if (flag == 0)
	{
		// stageScreen::mcMess[1] = wrong answer;
		constants::mcMessage = stageScreen::mcMess[1];
		// stageScreen::mcMess[2] = "The correct answer is:"
		constants::correctAns = stageScreen::mcMess[2];
		for (int i = 0; i < 4; ++i)
			if (stageScreen::curQues.checkAns(stageScreen::curAns[i]))
			{
				std::string tmp = " ";
				tmp.push_back((char)((int)'A' + i));
				constants::correctAns += tmp;
				break;
			}

		Mix_PlayChannel(-1, constants::wrongMusic, 0);

		// stageScreen::mcMess[5] = "chuc mung ban da vuot qua cau:"
		constants::endMessage = stageScreen::mcMess[5] + " " + std::to_string(stageScreen::numLevel - 1);

		gameManager::gameState = constants::SS_LOADING;
		loadingScreen::load(constants::SS_END, 3);
	}
}

void stageScreen::update()
{
	if (stageScreen::isTiming)
	{
		stageScreen::timeCounter -= constants::DELTA_TIME;
		if (stageScreen::timeCounter <= 0)
		{
			// stageScreen::mcMess[5] = "chuc mung ban da vuot qua cau:"
			constants::endMessage = stageScreen::mcMess[5] + " " + std::to_string(stageScreen::numLevel - 1);

			gameManager::gameState = constants::SS_END;
		}
	}

}