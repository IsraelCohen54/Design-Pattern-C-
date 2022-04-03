/*
#include <iostream>
#include "DP_Creational_builder_immutebale_object+IOC=inversion_of_control_usr_ctr.h"

//Creating immutable (=not changable) instance with internal class, while allowing the user to choose order of creation and input, as well as how many type.
//Flow, every setter method in inner class return *this, the class itself, that way we can continue use it's function untill we return the inner data with constructor of outer class.

class Restaurant_place_reserved {
	const std::string name;
	const int number_people;
	const std::string first_dish;
	const std::string free_water;
	const std::string take_away;
	const double tip_payed;

public:
    class user_choices {
	public: //public for outer class recognition
		const std::string _name;
		const int _number_people;
		std::string _first_dish;
		std::string  _free_water;
		std::string  _take_away;
		double _tip_payed;
		
		//To initialize the const value using constructor, we have to use the initialize list. This initializer list is used to initialize the data member of a class.
		//The list of members, that will be initialized, will be present after the constructor after colon. members will be separated using comma.
	public:
		user_choices(std::string name, int num_ppl):_name(name), _number_people(num_ppl){this->_first_dish = ""; this->_free_water = ""; this->_take_away = ""; this->_tip_payed; } //init user choices, as it's not const it's ok (changable).
		~user_choices() {
		//	std::cout << "user_choices class desctructor called\n"; //Just bother.. nice to see once only
		}
		user_choices first_dish_setter(std::string fd) { this->_first_dish = fd; return *this; }
		user_choices free_water_setter(std::string fw) { this->_free_water = fw; return *this; }
		user_choices take_away_setter(std::string ta) { this->_take_away = ta; return *this; }
		user_choices tip_payed_setter(double tp) { this->_tip_payed = tp; return *this; }
		//Line below: *this is in the scope of inner class, hence it's data passed to outer that way. '::' is the way supposedly in c++ to reach inner class from outer.
		Restaurant_place_reserved end() const { return *(new Restaurant_place_reserved::user_choices(*this)); } //'const' exactly there, saying that data can't be changed & reading is allowed.
		//return * to make it return a real object as intended.
	};
	Restaurant_place_reserved(user_choices& us) :name(us._name), number_people(us._number_people), first_dish(us._first_dish), free_water(us._free_water), take_away(us._take_away)
		, tip_payed(us._tip_payed) {} //|^_^|//
	~Restaurant_place_reserved() { std::cout << "Restaurent desctructor called\n"; }
	void print() {
		std::cout << "\nName:\t\t" << this->name << "\nPeople number:  " << this->number_people;
		//for better view, uncomment those: //Point was to show partially constructor input.
		//if (this->first_dish.size() > 0)
			std::cout << "\nFirst dish:\t" << first_dish;
		//if (this->free_water.size() > 0)
			std::cout << "\nFree water:\t" << free_water;
		//if (this->take_away.size() > 0)
			std::cout << "\nTake away:\t" << take_away;
		//if (this->tip_payed>0)
			std::cout<<"\nTip payed:      " << tip_payed << std::endl << std::endl;
	}
};

int main() {
	Restaurant_place_reserved Rpr_data_1 = Restaurant_place_reserved::user_choices("Avraham", 100).first_dish_setter("Fish_dish").free_water_setter("Would love to").take_away_setter("No need").tip_payed_setter
		(20).end();
	Rpr_data_1.print();
	
	Restaurant_place_reserved Rpr_data_2 = Restaurant_place_reserved::user_choices("Yitzchak", 1).free_water_setter("Thanks, king! Sure thing, but only that... ;)").tip_payed_setter(5).end();
	Rpr_data_2.print();

	Restaurant_place_reserved Rpr_data_3 = Restaurant_place_reserved::user_choices("zack", 10).tip_payed_setter(0.000001).end();
	Rpr_data_3.print();
}*/