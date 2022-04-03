/*
#include <iostream>

class Singelton {
private:
	static Singelton* _sing_instance; //Initialized outside of class as it's a static type
	Singelton() {} //preventin "new".. creation of the class! (=new Singelton, not allowed) From "the cherno" series https://youtube.com/clip/UgkxEgY9Hz_bzmZW5e5nLZhqY7_f5iMul3iJ
public: //needed to use it from main()
	static Singelton* get_single_instance(); //same as above here, static help to make it relative to the static instance:
	//"By declaring a function member as static, you make it independent of any particular object of the class.
	//A static member function can be called even if no objects of the class exist and the static functions are accessed using only the class name and the scope resolution operator ::
	//A static member function can only access static data member, other static member functions and any other functions from outside the class."
	void print() { std::cout << "using func inside singelton class" << std::endl; } //example usage in main
	~Singelton() { //Destructor. Like any self-respecting class, a Singleton class should define a destructor. If Singleton is to be subclassed, then the destructor should be declared virtual.
		std::cout << "Destructor saying hi\n";
		//delete _sing_instance; // happening automaticly, so no need, as otherwise entering endless loop... 
	}
};

//Create instance with it's type as the beggining (Singelton*)
Singelton* Singelton::_sing_instance; //init, can be =nullptr, or =0 //somehow seems to work without init? mm..

Singelton* Singelton::get_single_instance () { //implementation
	if (!_sing_instance) { //not false<=>not=0<=>not nullptr, all of that resulted to true in the 'if'
		std::cout << "Sole creation of singelton\n";
		_sing_instance = new Singelton; //<=>new Singelton(), no input in constractor... imo work the same.
		return (_sing_instance);
	}
	else {
		std::cout << "Returned the sole creation of singelton instance\n";
		return _sing_instance; //The static method reach it as it's static as well
	}
}

int main() {
	Singelton* singl_instance = ::Singelton::get_single_instance(); //same as Singelton::get_single_instance(), :: at start -> global scope.
	std::cout << "Adress in heap of first creation:  " << singl_instance << std::endl;
	Singelton* seconglton_8l = ::Singelton::get_single_instance();
	std::cout << "Adress in heap of second creation: " << seconglton_8l << std::endl;

	//Working options... do understand that future user :)
	//::Singelton::print(); //no connection between static to other things in class, would work instead: ::Singelton::get_single_instance() as it's a static method
	//Singelton::print();
	//So how can you use it? by the instance:
	seconglton_8l->print();
	
	//Singelton* sin = new Singelton; //Not available! meaning we can't create any new sin! Thanks god :)            reason - line 6.
	delete singl_instance; //seconglton_8l* pointing to same object, no need to delete as well, sin is same but better, it's not deleted, as it can't be created! Funny me
	//singl_instance->print(); //doesn't work of course...
}

//(We can add a static integer in singelton class to sum the number of times an instance of a class was created, another working idea)
*/