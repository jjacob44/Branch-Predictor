#ifndef BRANCH_H
#define BRANCH_H
#include<cstdlib>
#include<string>

class Branch {
	private:

	std::string behavior;
	int target;
	int addr;
	bool b = false; //for bimodal in tournament. True if the bimodal predicts this branch correctly
	bool g = false; //for g-share in tournament. True if the g-share predicts this branch correctly
	public:

	void setBehavior(std::string b);
	void setTarget(int t);
	void setAddress(int a);
	void setbimodal(bool val);
	void setgshare(bool val);
	std::string getBehavior();
	int getTarget();
	int getAddress();
	bool getbimodal();
	bool getgshare();
	Branch();
};
#endif
