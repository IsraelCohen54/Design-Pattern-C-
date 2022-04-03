#include <iostream>
class Target {
public:
	virtual void Request() = 0;
};

class Adaptee { //the specification
public:
	void specificRequest() {
		std::cout << "Tend to the cows! they are starving!\n";
	}
};

class Adapter: public Target, Adaptee {
	void Request() override { //Doesnt need to be public, as it inherit public method, and run the private method via the public one - Request
	specificRequest(); //Having specificRequest method as well via inheritence
	}
};

int main() {
	//as the client know the only the Target:
	Target* target = new Adapter(); //using Target instead of Adapter adp; adp.Request();, as Target is abstruct class who can have a real method implemented, like run in the backgroung.
	target->Request();
}
