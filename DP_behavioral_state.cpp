/*
# include <iostream>
//Object change it's behavior when it's state change
//The main point is you can easiliy change behaviour when state changed, without if/switch case (e.g. at end), code looks better that way
//as any class has it's own responsibility and functioning (not many if X.. do A,B,C, else if do..)
#include "windows.h" //not necessary in DP, just for sleep function

class State {
public:
	virtual void Handle() = 0;
};

class ConcreteState_Run :public State{
public:
	void Handle()override {
		std::cout << "ConcreteState_Run: Breath every second, do it fast but as deep as you can.\n";
	}
	//void func if.. print stop you can run no longer...
};

class ConcreteState_Walk :public State {
public:
	void Handle()override {
		std::cout << "ConcreteState_Walk: Breath every 10 second, do it in a moderate speed.\n";
	}
};

class ConcreteState_Sleep :public State {
public:
	void Handle()override {
		std::cout << "ConcreteState_Sleep: Breath every 15 second, do it slowly and deep.\n";
		//std::cout << "ConcreteState_Sleep: check time (static var e.g.) to change sleep side.\n";
		//if...
		change_sleep_side();
	}
	void change_sleep_side() {
		int sleep = 3500; //1 sec (as it's in milisec)
		int k = 2;
		while (k) {
			k -= 1;
			Sleep(sleep);
			std::cout << "ConcreteState_Sleep: Change sleep side, every 48 minutes.\n";
		}
		std::cout << "ConcreteState_Sleep: Should I do other things now?\n";
		//set var counter time to zero
	}
};
class Context {
	State* the_state=nullptr;
public:
	Context() {}
	Context(State* without_swich_case_or_if_condition) {
		this->the_state = without_swich_case_or_if_condition;
		this->the_state->Handle(); //or: Request(); or without_swich_case_or_if_condition->Handle();
	}
	void Request() {
		this->the_state->Handle();
	}
	void set_state(State* wdiF) {
		this->the_state = wdiF;
	}
	~Context() {}
};

int main() {
	Context* feel_like = new Context();
	ConcreteState_Run* A = new ConcreteState_Run;
	ConcreteState_Walk* B = new ConcreteState_Walk;
	ConcreteState_Sleep* C = new ConcreteState_Sleep;
	
	char choose;
	std::cout << "Brain, tell the body to breath, check it's state before, choose: w r s or h:\nWalking Running Sleeping or for Holding breath as long as you can while jumping in a dream\n";
	bool regular_functioning = true;
	do { 
		std::cin >> choose;
		switch (choose) {
		case('r'): 
			feel_like->set_state(A);
			feel_like->Request();
			break;
		case('w'): 
			feel_like->set_state(B);
			feel_like->Request();
			break;
		case('s'):
			feel_like->set_state(C);
			feel_like->Request();
			break;
		case('h'):
			std::cout << "Seems like the brain doesn't like it, seems as a wake up call ;)\n";
			regular_functioning = false;
			break;
		default: 
			std::cout << "try again, type the correct letter, than push enter\n";
			break;
		}
	} while (regular_functioning);
	
	std::cout << "Immediate change state, changed behaviour example:\n";
	Context* feel_like_that = new Context(A);
	feel_like_that->set_state(B);
	feel_like_that->Request();

	delete(feel_like);
	delete(A);
	delete(B);
	delete(C);
	delete(feel_like_that);
}*/