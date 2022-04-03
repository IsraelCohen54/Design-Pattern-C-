/*
# include <iostream>
# include <map>

//abstruct class, 2 classes (real+proxy) inherit from it,
//the proxy has variable of real class to reach there if doesn't find solution within proxy class
class Observable {
public:
    virtual int Request(std::string) = 0;
};

//Real object class, if we can, we try to answer via proxy without reaching it.
class tasty_level :public Observable {
public:
    int Request(std::string dish) {
        return (int)(dish.length() * 2.6 + 7.8 - 3.2); //"Time comsuming" method... of meybe reaching the real object it the TC? whatever
    }
};

class Proxy : public Observable {
    tasty_level *tlv = new tasty_level;
    std::map<std::string, int> dish_rank;
public:
    int Request(std::string dish_name) override { //returning restaurent rank by dish
        auto rank_answer_iterator = this->dish_rank.find(dish_name); //'anwer' is this map type iterator
        
        if (rank_answer_iterator != this->dish_rank.end()) //if iterator 'answer' didn't reached map end => key found:
        {
            std::cout <<dish_name<< " rank via proxy data: \n";
            return rank_answer_iterator->second;
        }
        int rank_via_real = tlv->Request(dish_name);
        std::pair<std::string, int>new_pair(dish_name, rank_via_real);
        this->dish_rank.insert(new_pair);
        std::cout  << dish_name << " rank via real_object (tasty lvl class) data: \n";
        return rank_via_real;
    }
    ~Proxy() {
        std::cout << "destractor called" << std::endl;
        delete this->tlv;
    }
};

int main() {
    Observable* Jerusalem_restaurent = new Proxy();
    int dish_rank = Jerusalem_restaurent->Request("omelet");
    std::cout << dish_rank << std::endl;
    dish_rank = Jerusalem_restaurent->Request("omelet");
    std::cout << dish_rank << std::endl;
    dish_rank = Jerusalem_restaurent->Request("Big_Pizza_with_tomatoes");
    std::cout << dish_rank << std::endl;
    dish_rank = Jerusalem_restaurent->Request("Big_Pizza_with_tomatoes");
    std::cout << dish_rank << std::endl;
    dish_rank = Jerusalem_restaurent->Request("omelet");
    std::cout << dish_rank << std::endl;
    dish_rank = Jerusalem_restaurent->Request("Some_funny_client_joke_goes_wgorng");
    std::cout << dish_rank << std::endl;
    delete Jerusalem_restaurent;
}
*/