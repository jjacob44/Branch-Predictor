#include"Branch.h"
	void Branch::setBehavior(std::string b){
		this->behavior = b;
	}
	void Branch::setTarget(int t){
		this->target = t;
	}
	std::string Branch::getBehavior(){
		return this->behavior;
	}
	int::Branch::getTarget(){
		return this->target;
	}
	Branch::Branch(){
		this->behavior = "NT";
		this->target = 0;
	}

