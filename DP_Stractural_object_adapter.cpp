#include <iostream>

class art_of_any_type {
public:
	virtual void aoat_printer() = 0;
};

class art :public art_of_any_type {
	void aoat_printer() override {
		std::cout << "Here goes my art! <(^_^)>\n";
	}
};

class poetry :public art_of_any_type {
	void aoat_printer() override {
		std::cout << "Here goes my art!\n";
		std::cout << "The day has come to it's end, the idea is potentialy a sublime\n";
		std::cout << "It's that scary, muhahaha! and here come the rhyme\n";
	}
};


class Target {
public:
	virtual void Request() = 0 ;
};

class Adapter :public Target {
	art_of_any_type* wished_art; //can have more than one such a connection!
public:	
	Adapter(art_of_any_type *the_art) {
		wished_art = the_art;
	}
	void Request() override {
		wished_art->aoat_printer();
	} //override
	//Adpter has it's own functions ass well ***
};

int main() {
	std::cout << "what would you like to choose? Art or poetry? a/p\n";
	char choice;
	bool check = true;
	Target *client_wish=NULL;
	do
	{
	std::cin >> choice;
		switch (choice) {
		case 'a':
			client_wish = new Adapter((new art()));
			check = false;
			break;
		case 'p':
			client_wish = new Adapter((new poetry()));
			check = false;
			break;
		default:
			std::cout << "choose by typing a or p, good luck\n";
		}
	} while (check);
	client_wish->Request();
	std::cout << "THE END\n";
	std::cout << "Well done!\n";
}
