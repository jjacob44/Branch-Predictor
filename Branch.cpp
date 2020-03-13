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
	std::string Branch::getBehavior(){
		return this->behavior;
	}
	int Branch::getTarget(){
		return this->target;
	}
	int Branch::getAddress(){
		return this->addr;
	}
	Branch::Branch(){
		this->behavior = "NT";
		this->target = 0;
	}

