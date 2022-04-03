#include <iostream>

//"class Component" - base, for client creating this: Component* name = new class/es_inheriting_from_decorator'
// at end - class inherit from component as they'r without a constractor, they'r the type of the finished decored product.
//  Further explanation: the clases who inherit from component other than decorator, are the "end game" classes, e.g. create pizza, salad, or hamburger.
//	To those, you can DECORATE (and only one of them!) with classes who inherit from decoretor
// (who inherit form component and has instance of it (like composite) to allow many decoretor class together with one of the other inheritor implementing component class
// (who doesnt have instance of component, so it's end there) - cheese class, tomato class, etc.

class Component {
public:
	virtual void Operation()=0;
};

class Concrete_Component_chair : public Component {
	void Operation() override {
		std::cout << "Making a chair\t\t\tOperation in Concrete Component (chair)\n";
	}
};

class Non_Concrete_Component_relax : public Component {
	void Operation() override {
		std::cout << "Relaxing\t\t\tOperation in Concrete Component (relax)\n";
	}
};

class NON_Concrete_Component_breath : public Component {
	void Operation() override {
		std::cout << "Breathing\t\t\tOperation in NON_Concrete Component (breath)\n";
	}
};

class Decorator :public Component {
public:
	Component* cmp = nullptr;
	Decorator(Component* compo) :Component() {
		cmp = compo;
	}
	void Operation() override {
		cmp->Operation();
		//this->cmp->Operation(); 
	}
};

class concrete_Decorator_Adding_State :public Decorator {
public:
	concrete_Decorator_Adding_State(Component* compo) :Decorator(compo) {}
	void adding_state() {
		std::cout << "Satiated\t\t\tAdded to human state {decorator inheritence}\n";
	}
	void Operation() override {
		adding_state();
		cmp->Operation();
	}
};

class concrete_Decorator_Adding_Behaviour :public Decorator {
public:
	concrete_Decorator_Adding_Behaviour(Component* compo) :Decorator(compo) {}
	void adding_behaviour() {
		std::cout << "Running\t\t\t\tAdded to human behaviour {decorator inheritence}\n";
	}
	void Operation() override {
		adding_behaviour();
		cmp->Operation();
	}
};

class concrete_Decorator_beautifying_haircut :public Decorator {
public:
	concrete_Decorator_beautifying_haircut(Component* compo) :Decorator(compo) {}
	void adding_beauty() {
		std::cout << "Haircut!\t\t\tAdded to human beauty {decorator inheritence}\n";
	}
	void Operation() override {
		adding_beauty();
		cmp->Operation();
	}
};

class concrete_Decorator_beautifying_shower :public Decorator {
public:
	concrete_Decorator_beautifying_shower(Component* compo) :Decorator(compo) {}
	void adding_beauty() {
		std::cout << "Go to shower NNNNNNNOWWWWWW!!!\tAddede to human beauty {decorator inheritence}\n";
	}
	void Operation() override {
		adding_beauty();
		cmp->Operation();
	}
};

int main() {
	//Decoretor isn't at end, but other classes who inheriting Component class are, reason - by the lacking of constructor to fill...:
	Component* the_cmp_of_being = new concrete_Decorator_Adding_Behaviour(new concrete_Decorator_beautifying_shower(new concrete_Decorator_Adding_State(new NON_Concrete_Component_breath)));
	Component* the_cmp_of_creating = new concrete_Decorator_Adding_State(new Concrete_Component_chair);
	Component* the_cmp_of_beauty_creating = new concrete_Decorator_beautifying_haircut(new concrete_Decorator_beautifying_shower(new Non_Concrete_Component_relax));
	Component* the_cmp_of_a_racer = new concrete_Decorator_Adding_Behaviour(new concrete_Decorator_beautifying_shower(new concrete_Decorator_Adding_Behaviour(new concrete_Decorator_beautifying_shower(new Non_Concrete_Component_relax))));
	//Component* the_cmp_of_beauty_creating = new concrete_Decorator_beautifying(new Concrete_Component_statue(new Concrete_Component_chair)); //Doesn't working!!! do notice that!
	the_cmp_of_being->Operation();
	std::cout << std::endl;
	the_cmp_of_creating->Operation();
	std::cout << std::endl;
	the_cmp_of_beauty_creating->Operation();
	std::cout << std::endl;
	the_cmp_of_a_racer->Operation();

	
	//creation of circle like composite failed: (it's working, not behave a circle, debug to get in depth)
	// the difference from composite, is: Decorator immediate input, as well as 'add' method of composite DP.
	// ok, got it imo, the 'new' every time, make input in new place in heap memory, so it's not a real circle.
	//Component* Branch1 = new Decorator(new Non_Concrete_Component_relax);
	//Component* Branch2 = new Decorator(Branch1);
	//Branch1 = new Decorator(Branch2);
	//Branch1->Operation();
	//delete(Branch1);
	//delete(Branch2);

	delete (the_cmp_of_being);
	delete (the_cmp_of_creating);
	delete (the_cmp_of_beauty_creating);
	delete (the_cmp_of_a_racer);
}
