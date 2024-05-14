#include "question.h"

question::question() {};

question::question(std::string _ques, std::string _ans[])
{
	ques = _ques;
	ans[_ans[0]] = true;
	for (int i = 1; i < 4; ++i)
		ans[_ans[i]] = false;

}

std::string question::getQues()
{
	return ques;
}

std::vector<std::string> question::getAns()
{
	std::vector<std::string> res;
	for (auto it : ans)
		res.push_back(it.first);
	std::random_shuffle(res.begin(), res.end());
	return res;
}

bool question::checkAns(std::string s)
{
	return ans[s];
}