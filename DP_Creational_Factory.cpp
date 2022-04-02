/*
// creating in O(1) class type via map <name to create, new creation>
// virtual factory creator as abstruct class, implemented by many. //name doesnt really matter...
// class factory_creation has map member initialized to any type (the abstruct* before), and return (with after check if exist!!!) the creation, if not exist, do not use pointer... 
# include <iostream>
# include <map>

class worker_factory_creator {
public:
	virtual worker_factory_creator* create() = 0;
	virtual void work() = 0;
};

class managar_creator:public worker_factory_creator {
public:
	managar_creator() :worker_factory_creator() {}
	worker_factory_creator* create() override{
		return new managar_creator;
	}
	void work() override{
		std::cout << "Manager, use the milk to give the workers coffee to show your sutisfaction, and the sub_manager your acceptance.\n\tB.t.w, you shouldn't know thte milk was expired.\n";
	}
};

class sub_managar_creator :public worker_factory_creator {
public:
	worker_factory_creator* create() override {
		return new sub_managar_creator;
	}
	void work() override {
		std::cout << "Sub manager, give the manager expired milk to make a coffee,\n\tto show your sutisfaction and support for him and the workers.\n";
	}
};

class worker_creator :public worker_factory_creator {
public:
	worker_factory_creator* create()  override {
		return new worker_creator;
	}
	void work() override {
		std::cout << "Workers, drink the bitter coffee to show your simulated appreciation and sutisfaction.\n";
	}
};

class worker_factory {
	std::map <std::string, worker_factory_creator*> worker_map_creational;
public:
	worker_factory(){ //down casting:
		this->worker_map_creational.insert(std::pair<std::string, worker_factory_creator*>("manager"    , new managar_creator));
		this->worker_map_creational.insert(std::pair<std::string, worker_factory_creator*>("sub_manager", new sub_managar_creator));
		this->worker_map_creational.insert(std::pair<std::string, worker_factory_creator*>("worker", new worker_creator));
	}
	
	worker_factory_creator* create(std::string wrk_name) {
		auto ans = this->worker_map_creational.find(wrk_name);
		if (ans != this->worker_map_creational.end()) {
			std::cout << wrk_name << " was created.\n";
			return ans->second->create();
		}
		else
			std::cout << "Wrong type, no such type - '"<< wrk_name<<"' was found in database.\n";
		return nullptr;
	}
	~worker_factory() {
		this->worker_map_creational.clear();
	}
};

int main() {
	worker_factory *wrk_f = new worker_factory;
	worker_factory_creator *wfc = wrk_f->create("sub_manager");
	//could work with cin>> && do while.. to create as many as client like..
	if (wfc)
	{
		wfc->create();
		wfc->work();
	}
	wfc = wrk_f->create("manager");
	wfc->create();
	wfc->work();
	wfc = wrk_f->create("worker");
	wfc->create();
	wfc->work();
	wfc = wrk_f->create("workerrrrbbbbrrrrrrboom");
	if (wfc)
	{
		wfc->create();
		wfc->work();
	}
	delete wrk_f;
}*/