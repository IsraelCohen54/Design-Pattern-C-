//Creating complex object, by choosing specific creatinal methods, like choose salt and salad, or salt and pizza, or all.
# include <iostream>
# include <list>

//abstruct, methods to adding things
class Builder {
public:
	virtual void add_part1() = 0;
	virtual void add_part2() = 0;
	virtual ~Builder() {}
};

//hold product gathered inside builder inheritors as var to be filled
class Product {
public:
	std::list<std::string> my_list_prd;
	void print_data() const {
		for (auto& it : this->my_list_prd) {
			std::cout << it << " ";
		} std::cout << "\n";
	}
};

//launch and dinner inheriting builder abstruct
class ConcreteBuilder_launch : public Builder {
	Product* my_prd;
public:
	ConcreteBuilder_launch() {
		this->my_prd = new Product();
	}
	void add_part1() override {
		this->my_prd->my_list_prd.push_back("Potato");
	}
	void add_part2() override {
		this->my_prd->my_list_prd.push_back("SweetPotato");
	}
	//return product
	Product* get_launch_of_your_choice() {
		Product* lnch = this->my_prd;
		this->my_prd = new Product(); //reset
		return lnch;
	}
	~ConcreteBuilder_launch() override {
		delete this->my_prd;
	}
};

class ConcreteBuilder_dinner : public Builder {
	Product* my_prd;
public:
	ConcreteBuilder_dinner() {
		this->my_prd = new Product();
	}
	void add_part1() override {
		this->my_prd->my_list_prd.push_back("cap of water salt and lemon");
	}
	void add_part2() override {
		this->my_prd->my_list_prd.push_back("apple salad and soup");
	}
	//return product
	Product* get_dinner_of_your_choice() {
		Product* dinner = this->my_prd;
		this->my_prd = new Product(); //reset
		return dinner;
	}
	~ConcreteBuilder_dinner() override {
		delete this->my_prd;
	}
};

//"manager" class, manage what would be added by "part" conctructors, via buider who contain one of it's inheritors and choose from there what to add:
class Director {
	Builder* builder;
public:
	Director(Builder* builder){this->builder = builder; }
	void add_just_basic_one() {
		this->builder->add_part1();
	}
	void add_just_basic_two() {
		this->builder->add_part2();
	}
	void full_build() {
		this->builder->add_part1();
		this->builder->add_part2();
	}
	~Director() {}
};

int main() {
	//flow: director hold builder type, who's filled with builder inheritor type, director choose how to fill product constructor via builder inheritors.
	//Builder is abstruct, so it can have more than one inheritor=> many types of products potentialy:
	ConcreteBuilder_launch* launch = new ConcreteBuilder_launch();
	ConcreteBuilder_dinner* dinner = new ConcreteBuilder_dinner();
	Director *the_prod=new Director(launch);
	Director* the_prod_of_late = new Director(dinner);
	bool x = true;
	int option = 0;
	std::cout << "type launch option from {1,2,3}, option\n1 = (potato),\n2 = (sweetpotato),\n3 = (both), for dinner, try 6 instead of 5 or 4" << std::endl;
	do {
		std::cin >> option;
		switch (option)
		{
		case(1):
			the_prod->add_just_basic_one();
			x = false;
			break;
		case(2):
			the_prod->add_just_basic_two();
			x = false;
			break;
		case(3):
			the_prod->full_build();
			x = false;
			break;
		case(4):
			the_prod_of_late->add_just_basic_one();
			x = false;
			break;
		case(5):
			the_prod_of_late->add_just_basic_two();
			x = false;
			break;
		case(6):
			the_prod_of_late->full_build();
			x = false;
			break;
		default:
			std::cout << "try again, type only one number in range: 1 to 6, than push enter\n";
			break;
		} 
	} while (x);
	std::cout << "List of Selected Launch food type: " << std::endl;
	if (option < 4) {
		Product* food_lst = launch->get_launch_of_your_choice();
		food_lst->print_data();
		delete food_lst;
	}
	if (option > 3) {
		Product* food_lst_dinner = dinner->get_dinner_of_your_choice();
		food_lst_dinner->print_data();
		delete food_lst_dinner;
	}
}
//option to add remove() as well, just saying
