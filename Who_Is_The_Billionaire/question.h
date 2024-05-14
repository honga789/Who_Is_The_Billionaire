#pragma once
#include "gameManager.h"

class question {
private:
	std::string ques;
	std::unordered_map<std::string, bool> ans;

public:
	// _ans[0] stogare true ans;
	question();
	question(std::string _ques, std::string _ans[]);
	std::string getQues();
	std::vector<std::string> getAns();
	bool checkAns(std::string s);
};

