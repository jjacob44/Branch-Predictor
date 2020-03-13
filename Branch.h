#ifndef BRANCH_H
#define BRANCH_H
#include<cstdlib>
#include<string>

class Branch {
	private:

	std::string behavior;
	int target;
	int addr;
	public:

	void setBehavior(std::string b);
	void setTarget(int t);
	void setAddress(int a);
	std::string getBehavior();
	int getTarget();
	int getAddress();
	Branch();
};
#endif
