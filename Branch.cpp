#include"Branch.h"
	void Branch::setBehavior(std::string b){
		this->behavior = b;
	}
	void Branch::setTarget(int t){
		this->target = t;
	}
	void Branch::setAddress(int a){
		this->addr = a;
	}
	void Branch::setbimodal(bool val){
		this->b = val;
	}
	void Branch::setgshare(bool val){
		this->g = val;
	}
	std::string Branch::getBehavior(){
		return this->behavior;
	}
	int Branch::getTarget(){
		return this->target;
	}
	int Branch::getAddress(){
		return this->addr;
	}
	bool Branch::getbimodal(){
		return this->b;
	}
	bool Branch::getgshare(){
		return this->b;
	}
	Branch::Branch(){
		this->behavior = "NT";
		this->target = 0;
	}

