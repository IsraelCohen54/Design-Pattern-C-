/*
#include <iostream>

class House_Implementation {
public:
	virtual void createDoor()=0;
	virtual void createWall()=0;
};
class Wood_Implementation: public House_Implementation {
	void createDoor()override {
		std::cout<<"Door builded from wood\n";
	}
	void createWall()override {
		std::cout << "Wall builded from wood\n";
	}
};

class Brick_Implementation: public House_Implementation {
	void createDoor()override {
		std::cout << "Door builded from bricks\n";
	}
	void createWall()override {
		std::cout << "Wall builded from bricks\n";
	}
};

class House {
protected:
	House_Implementation* H_I;
public:
	House(House_Implementation* h_i) { //constructor
		H_I = h_i;
	}
	virtual void build() = 0; //virtual => abstruct class

	void open_door() {
		std::cout << "Door is opened\n";
	}
	void close_door() {
		std::cout << "Door is closed\n";
	}
};

class Big_House:public House {
public:
	Big_House(House_Implementation* specific_H_I) :House(specific_H_I) {
		//H_I = specific_H_I; //as it do the same, House constructor needed by cpp for my understanding.
	}
	void build() override {
		std::cout << "What a big house! I like it, but I need a door and some more walls here.\n";
		H_I->createDoor();
		H_I->createWall();
	}
};

class Small_House :public House {
public:
	Small_House(House_Implementation* specific_H_I):House(specific_H_I) {
		H_I = specific_H_I; 
	}
	void build() override {
		std::cout << "What a small cosy house! I like it, but I need a door and some more walls here.\n";
		H_I->createDoor();
		H_I->createWall();
	}
};

int main() {
	House* my_big_house = new Big_House(new Brick_Implementation);
	my_big_house->build();
	my_big_house->close_door();
	House* my_house = new Small_House(new Wood_Implementation);
	my_house->build();
	
	delete (my_big_house); //delete is needed per pointer, not like that - delete(a,b);
	delete(my_house);
}*/