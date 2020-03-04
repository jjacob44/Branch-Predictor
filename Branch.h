#ifndef BRANCH_H
#define BRANCH_H
#include<cstdlib>
#include<string>

class Branch {
	private:

	std::string behavior;
	int target;
	public:
	void setBehavior(std::string b);
	void setTarget(int t);
	std::string getBehavior();
	int getTarget();
	Branch();
};
#endif
