#include "constants.h"

int constants::WIDTH = 900;
int constants::HEIGHT = 700;
std::string constants::TITLE = "Who is the Billionaire";
int constants::MOUSE_X = 0;
int constants::MOUSE_Y = 0;
int constants::FPS = 60;
double constants::DELTA_TIME = 1.0 / constants::FPS;
std::string constants::mcMessage = "";
std::string constants::correctAns = "";
std::string constants::endMessage = "";
Mix_Music* constants::bgMusic = NULL;
Mix_Chunk* constants::correctMusic = NULL;
Mix_Chunk* constants::wrongMusic = NULL;