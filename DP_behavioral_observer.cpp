#include<iostream>
#include<list>
// Object has it's own list of objects who would like to know when it's changed.
// (need some renovations imo (the very basic does work though), as info of what changed probably should be implemented as well).

//class Event_arg; //meaning what happened, **currently not implemented**
//~~~~~//
//Notify all concern observers onle when there is a change in observed item.
//Than, up to observer when to check out the update.
class Observable; //Declared for observer class...

class Observer {
public:
	//virtual void Update(Observable& o, Event_arg& e) = 0; //from who, what happend, curr not implemented
	virtual void Update(Observable& o) = 0;
};

//class Event_arg { //not inplemented currently
//	char ev;
//public:
//	int do_event(int a, int b) {
//		if (this->ev == '-') {
//			minus(a,b);
//		}
//		if (this->ev == '-') {
//			plus(a, b);
//		}
//		else
//			return -1;
//	}
//	int minus(int a,int b) {
//		std::cout << "minus even\n";
//		return a - b;
//	}
//	int plus(int a, int b) {
//		std::cout << "add even\n";
//		return a + b;
//	}
//};

class Observable{//Observable
	std::list<Observer*> obs_lst;
	//std::list<Event_arg*> ev_arg;
public:
	void Attack_observer(Observer& add_obs) {
		this->obs_lst.push_back(&add_obs); //'&' again, to make an address (alias of variable)  like a pointer, to be saved in pointer array, how exactly? good question :) kinda adress of adress, goes leg back to point to the first address, my guess.
		
	}
	void Notify() {
		for (auto &obs : this->obs_lst)
			obs->Update(*this);
	}
	void Detack(Observer& del_obs) { //check if work, so pointer check didnt go as intended sadly, I move on...
		for (auto& spec_obs : this->obs_lst)
			if (spec_obs) //pointers check, especially after delete the del_obs...
				if (&del_obs == spec_obs) {
					this->obs_lst.remove(spec_obs);
					break;
				}
	}
	//void Update(Observable& o)override {
	//	Notify();}
	~Observable() {}
};

class ConcreteObservable: public Observable { //the interesting subject to know when it's changed
	int observed_data=0; //The observable data
public:		
	int GetState() {
		return this->observed_data;
	}
	void SetState(int set_data_into_od) {
		this->observed_data =set_data_into_od;
		Notify();
	}
	~ConcreteObservable() {}
};

class ConcreteObserver_1 :public Observer {
	ConcreteObservable* crsb;
public:
	ConcreteObserver_1(ConcreteObservable* ovable) {
		this->crsb = ovable;
		ovable->Attack_observer(*this);
	}
	void Update(Observable& o) override {
		std::cout << "Hello! update happened!!!\n";
		std::cout << "wanna see? if so, press 1+enter. Else, press 2+enter\n";
		int ans = -1;
		
		int a;
		int check = 1;
		do
		{
			std::cin >> ans;
			switch (ans)
			{
			case(1):
				a = this->crsb->GetState();
				std::cout << "current value: " << a << ", ConcreteObserver_1 updated!\n";
				check = 0;
				break;
			case(2):
				std::cout << "Too scary, meybe next time?\n";
				check = 0;
				break;
			case(3):
				check = 0;
				break;
			default:
				std::cout<<"'Exit' with 3+enter, else please follow instructions above\n";
				break;
			}
		} while (check);
	}
	~ConcreteObserver_1() {}
};


int main() {
	ConcreteObservable a;     //looking at a, has from inheritance: list(private var), attack, notify, detach, itself add: getstate, SetState
	ConcreteObserver_1 b(&a); //object b observing a. b has virtual update from observer. b use a (it's his private var) to GetState of a.
							  //itself: private var (looking at), constructor with var, than var->attach(this*),
							  //such that at SetState call notify from observer who call update from list of Observer* (that actually contain it's inherotors - concreteobservable e.g.). Crazy
	ConcreteObserver_1 c(&a);
	a.Detack(b);	
	a.SetState(3);
	a.SetState(5);
}
