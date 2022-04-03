/*
#include<iostream>
#include <map>
#include <vector>

//Clonning class with 'clone' as virtual method, in the department(abstruct class)
//that bequeaths to it's heirs,
//such that each return new instance of it's own override the 'clone' virtual function.

struct my_things { //not connected to dp, just struct..
	int x=0;
	std::string y="";
	std::map<char, int> z;
	std::vector<int> my_vec;
};

class Prototype_things {
public:
	virtual Prototype_things* Clone() = 0;
};

class Concryte_prototye1 : public Prototype_things {
	my_things mt;
public:
	Concryte_prototye1() {
		this->mt.x = 1;
		this->mt.y = "thing";
		this->mt.z.insert(std::pair<char, int>('a', 1));
		this->mt.my_vec.push_back(1);
	} // next line, "Concryte_prototye1* Clone().." work ass well, prob because it's inheriting proto, in heap is derived class, return now casted up, using virtual method so its ok,
	  // if method wouldn't be of the bequeath, but it's son, prob no good.
	Prototype_things* Clone() override { 
		return new Concryte_prototye1(*this); //main clone DP point...
	}
	void some_func() {
		std::cout << "some func 1 do some things.\n";
	}
	~Concryte_prototye1() {}
};

class Concryte_prototye2 : public Prototype_things {
	my_things mt;
public:
	Concryte_prototye2() {
		this->mt.x = 2;
		this->mt.y = "shwing";
		this->mt.z.insert(std::pair<char, int>('s', 9));
		this->mt.my_vec.push_back(3);
	}
	Prototype_things* Clone() override {
		return new Concryte_prototye2(*this); //main clone DP point...
	}
	void some_fung_shwey() {
		std::cout << "some fung shwey do some shwing.\n";
		std::cout << this->mt.x<<std::endl;
	}
	~Concryte_prototye2() {}
};

int main() {

	////main clone DP point as I understand it:
	Prototype_things* a = new Concryte_prototye1();
	std::cout << "print address of original class variable:\t\t\t"<< &a << std::endl;
	Prototype_things* b = a->Clone();
	std::cout << "print address of cloned class variable (by & as needed :)     " <<"  "<< & b << std::endl;

	//optional - func usage for derived class + clone ass well
	Concryte_prototye2* cp2= new Concryte_prototye2();
	cp2->some_fung_shwey();
	cp2 = (Concryte_prototye2*) a->Clone();
	std::cout << "after clone: (eventhough not sure if that is the clone intended, but whateve...)\n";
	cp2->some_fung_shwey();

	delete a;
	delete b;
}*/