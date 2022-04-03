/*
#include <iostream>

class Sword {
public:
	virtual void create_sword() = 0;
	~Sword() {}
};

class plain_sword : public Sword {
public:
	void create_sword() {
		std::cout<< "My sword: o=||===>\n";
	}
	~plain_sword() {}
};

class Light_saber : public Sword {
public:
	void create_sword() {
		std::cout << "My sword: ={====\n";
	}
	~Light_saber() {}
};

class Shield {
public:
	virtual void create_shield() = 0;
	~Shield() {}
};

class plain_shield : public Shield {
public:
	void create_shield() {
		std::cout<<"My shield: __\n          |__|\n          |__|\n";
	}
	~plain_shield(){}
};

class Deflector : public Shield {
public:
	void create_shield() {
		std::cout << "My shield: ##\n           ##\n";
	}
	~Deflector(){}
};

class armory_factory {
public:
	virtual Sword* createSword() = 0;
	virtual Shield* createShield() = 0;
};

class star_wars_armory :public armory_factory {
public:
	Sword* createSword() override {
		Light_saber* swrd = new Light_saber();
		swrd->create_sword();
		return swrd;
	}
	Shield* createShield() override {
		Deflector* shld = new Deflector();
		shld->create_shield();
		return shld;
	}
	~star_wars_armory() {}
};

class plain_armory :public armory_factory {
public:
	Sword* createSword() override {
		plain_sword* swrd = new plain_sword();
		swrd->create_sword();
		return swrd;
	}
	Shield* createShield() override {
		plain_shield* shld = new plain_shield();
		shld->create_shield();
		return shld;
	}
	~plain_armory() {}
};

int main() {
	armory_factory *a = new plain_armory();
	Sword *sword = a->createSword();
	Shield *shield = a->createShield();
	armory_factory* b = new star_wars_armory();
	Sword* sword_b = b->createSword();
	Shield* shield_b = b->createShield();
	
	delete a;
	delete sword;
	delete shield;
	delete b;
	delete sword_b;
	delete shield_b;
}*/