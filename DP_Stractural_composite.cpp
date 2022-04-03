//Made by Israel at 15/03/22, preventing circles in hierarchy.. Have a good day you there! (user... ;)

#include <iostream>
#include <list>

class Component {
public:
	Component* parent_ = nullptr;
	//next 4 are the base:
	virtual void operation() = 0;
	virtual void add(Component*) = 0;
	virtual void Remove(Component*) = 0;
	virtual void GetChild(Component*) = 0;
	//next 6 for circles check, using saved pointer to parent as well:
	virtual int hierarchy_check() = 0;
	virtual const std::list<Component*> get_tree_hierarchy() = 0;
	virtual int check_every_Child(Component*) { return 0; }
	virtual int get_tree_size() { return 0; }
	
	void SetParent(Component* parent) {
		this->parent_ = parent;
	}
	Component* GetParent() const {
		if (parent_ != nullptr)
			return this->parent_;
		std::cout << "nullptr reached\n";
	}
	virtual ~Component() {} //good practice
};

class Leaf :public Component {
private:
	std::string name;
	int node_type = 0; //Leaf type
public:
	Leaf(std::string my_name) {
		name = my_name;
	}
	void operation() {
		std::cout << "Doing the right things in leaf "<<this->name<<"!\n";
	}
	void add(Component*) {}
	void Remove(Component*) {}
	void GetChild(Component*) {}
	int hierarchy_check() { 
		return node_type;
	}
	const std::list<Component*> get_tree_hierarchy() { return this->get_tree_hierarchy(); }
};

class Composite :public Component {
	std::list<Component*> tree_hierarchy; //Can have many leafs and branches, circles are not good (branch1 son of branch1 in hierarchy somewhere).
	int node_type = 1; //not a leaf

public:
	//Doing wanted operation/s
	void operation() {
		for (Component* child : tree_hierarchy)
		{
			child->operation();
		}
	}
	const std::list<Component*>get_tree_hierarchy()override {
		if (tree_hierarchy.size() != 0)
		return tree_hierarchy;
	}
	//List isn't empty:
	int get_tree_size() override {
			return tree_hierarchy.size();
	}
	//checking circles toward sons, like branch2.add(branch1) while branch2 is branch1 son...
	int check_every_Child(Component* node) override {
		int is_true=0; //sum reccursion result
		if (node) {
			if (node->get_tree_size() !=0) {
				for (auto child : node->get_tree_hierarchy())
					if (child != node->get_tree_hierarchy().back()) {
						if (this == child) {
							is_true += 1;
							return is_true;
						}
						is_true+=check_every_Child(child);
					}
					else
						if (this == child) {
							is_true += 1;
							return is_true;
						}
			}
		}
		if (is_true==0)
			return 0;
		return 1;
	}
	//Be uniqe in the tree... checking for circles:
	bool Check_uniqe_circle_preventation(Component* node) {
		if (node->hierarchy_check() == 0) //It's a leaf
			return false;
		//need to check:
		//1: does dad point to son in hierarchy
		//2: check it's not the same (tree.add(tree))
		//3: does son point to dad in hierarchy
		
		//1: 
		if (tree_hierarchy.size()!=0)
			for (auto  child : tree_hierarchy) {
				if (child) //not nullptr
					if(child->hierarchy_check() != 0) //not a leaf (so we can have common leaf, otherwise it would say it's a circle.
						if (node == child->GetParent())
									return true;
			}
		//2:
		if (node == this)
			return true;
		//3:
		return check_every_Child(node);
	}
	
	//Adding leaf or composite to branch/main tree, while checking for unnwanted circles:
	void add(Component* node) override {
		bool is_exist = Check_uniqe_circle_preventation(node);
		if (!is_exist) {
			tree_hierarchy.push_back(node);
			node->SetParent(this);
		}
		else
			std::cout << "Circle preventing adding this composite again!\n";
	}
	//Removing specific node
	void Remove(Component* node) override {
		tree_hierarchy.remove(node);
		node->SetParent(nullptr);
		
	}
	//Doing every childs operations:
	void GetChild(Component* h) override {
		for(auto child:tree_hierarchy)
			if (child!= tree_hierarchy.back())
			{
				GetChild(child);
			}
			else {
				child->operation();
			}
	}
	//Leaf (0) or composite (1) check:
	int hierarchy_check() {
		return node_type;
	}
};

int main() {
	std::cout << "all right, lets begin!\n";
	Component *tree = new Composite();
	Leaf* leefy1 = new Leaf("first_L");
	Leaf* leefy2 = new Leaf("Sec_L");
	Leaf* leefy3 = new Leaf("Third_L");
	Component* Branch1 = new Composite();
	Component* Branch2 = new Composite();
	tree->add(tree); //Circle 1
	tree->add(leefy1);
	Branch1->add(leefy1); //many same leafs..
	Branch1->add(leefy1);
	Branch1->add(leefy2);
	Branch1->add(leefy2);
	Branch2->add(leefy2);
	Branch2->add(leefy3);
	Branch1->add(Branch2); //Haveing common leaf, it's ok.
	Branch1->add(Branch1); //Circle 2
	Branch2->add(Branch1); //Circle 3
	tree->add(Branch1);
	tree->add(Branch2); //Not circle as I understand it
	Branch1->add(tree); //Circle 4
	Branch2->add(tree); //Circle 5
	tree->operation();
	
	delete tree;
	delete leefy1;
	delete leefy2;
	delete leefy3;
	delete Branch1;
	delete Branch2;
}
