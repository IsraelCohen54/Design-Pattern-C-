#include <iostream>     
#include <vector>
#include <map>
#include <list>
#include <algorithm>    // std::count_if
#include <queue>        //priority quoue
#include <stack>

//generic template:
template <typename T> //instead of the unessessary <class T>
T maxoftwo(T a, T b) //return T type, accept 2 same T type
{
    return a > b ? a : b; //return if true: a, else return b
}

//global variable:
const int WIDTH = 5;
const int HEIGHT = 3;


struct structNameComeHere
{
    int abc = 123;
    char d = 'e';
    std::vector <int> my_vec;
    std::map<std::string, int> m{ {"CPU", 10}, {"GPU", 15}, {"RAM", 20}, };
    std::list<double>my_Lst={1.2,2.3,3.9};
    bool pointer_to_array[4] = { true,false,0};
    //std::hash
};

int check(int k) {
    k = k + 1;
    return k;
}

int check1(int *k) {
    *k = *k + 1;
    return *k;
}

class check_delete {
public:
    int i;
    check_delete(int num) :i(num) {}
};

template<typename T, typename A> //needed to say its withing compilation, T is generic template, A - allocator per vec type (https://stackoverflow.com/questions/19094340/stdvector-as-a-template-function-argument)
std::vector <T,A> vec_func1(const std::vector <T,A>& my_vec) { //const - not changing the vector, & for not copying all the vector into the function
    std::vector <T,A> vec = my_vec;
    return vec;
}

//print list data, agument each cell:
void showlist(std::list<double> L) {
    std::list<double>::iterator it;
    for (it = L.begin(); it != L.end(); ++it)
        std::cout << '\t' << *it;
    std::cout << '\n';

    ////same result:
    //for (auto &l : L) 
    //    std::cout << '\t'<<l;
    //std::cout << '\n';

    for (it = L.begin(); it != L.end(); ++it)
        *it += (* it) / 2;
    std::cout << '\n';
    
    for (it = L.begin(); it != L.end(); ++it)
        std::cout << '\t' << *it;
    std::cout << '\n';

}

int func_to_learn_val_by_value(int num) {
    return num;
}

int func_to_learn_ref_by_value(intptr_t num) {
    return num;
}

int func_to_learn_val_by_ptr(int* num) {
    return *num;
}

int func_to_learn_val_by_reference(int& num) {
    return num;
}

int func_to_learn_ref_by_reference(intptr_t &num) {
    return num;
}


int main() {
    //~~~template example: getting unknown variable type~~~
    std::cout << "max of 2,5: " << maxoftwo(2, 5) << "\n";
    std::cout << "max of 5.5, 2.7: " << maxoftwo(5.5, 2.7) << "\n";

    //~~~struct example:~~~
    structNameComeHere first;
    std::cout << "my struct integer & char: " << first.abc << " " << first.d << "\n";

    //~~~reference + pointers example:~~~
    int res = 1;
    std::cout << "check by value: " << check(res) << "\n"; //by value
    res = check1(&res); //by reference
    first.abc += check(first.abc);
    structNameComeHere* second; //currently doesnt get memory, junk, not right values, as not memory got allocated to heap
    second = new structNameComeHere; //ok
    //*something.thing == something->thing
    (*second).abc = check((*second).abc); //meaning - got that alloc mem, find there...
    std::cout << "(*second).abc= " << (*second).abc << "\n";
    delete second;

    //~~~vector example:~~~
    std::vector <char> vec = { 'a','b' };
    vec.push_back('c');
    std::cout << "using 'at' with vector - specific index, getting index 1 from a b c: " << vec.at(1) << std::endl;
    std::cout << "vec size: " << vec.size() << std::endl; //vec size: 3
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << "vec[i]: " << vec[i] << std::endl;
    }
    //~~~foreach example? (a real for_each down at end)~~~ (same result as before)
    for (auto& ve : vec) //reference so that we dont need to copy each vertex in the vector.
    {
        std::cout << "auto vec: " << ve << std::endl;
    }
    vec = vec_func1(vec);

    std::vector<std::vector<char>> vec_vecush; //2D vector
    vec_vecush.push_back(vec);
    vec_vecush.push_back(vec);

    std::cout << "printing specific cell- [1][1], in 2D vector: " << vec_vecush[1][1] << std::endl;
    // Displaying the 2D vector
    std::cout << "2D vector by 2 for loops: " << std::endl;
    for (int i = 0; i < vec_vecush.size(); i++) {
        for (int j = 0; j < vec_vecush[i].size(); j++)
            std::cout << vec_vecush[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << "2D vector by Foreach: " << std::endl;
    for (auto& vecc : vec_vecush) { //same as: char &vecc : vec_vecush, as we know it's char...
        for (auto& vecc2 : vecc) //same as: char &vecc2: vecc, auto find it's type, which is char.
            std::cout << vecc2 << " ";
    }
    std::cout << std::endl;

    vec.erase(vec.begin() + 1); //delete specific cell - 'a' deleted
    vec.clear(); //delete all of vec data
    vec_vecush.clear();

    //~~~map example:~~~

    //std::map<int, char> my_map;
    //my_map[5] = 'E'; //work with type defined as key.

    std::map<std::string, char> my_map;
    //inserting 2 options, first:
    my_map.insert({ "key1", 'a' }); //map_name.insert({key, element})
    my_map.insert({ "key2", '2' });
    my_map.erase("key1");
    my_map.insert({ "3", 'c' });
    my_map.insert(std::pair<std::string, char>("4", 'D'));
    //sec opt
    my_map["5!"] = 'E'; //map_name[key]= element
    //next line, using '\' to cancel " meaning
    std::cout << "\nmy_map.find(\"5!\")->first: " << my_map.find("5!")->first << " my_map.find(\"5!\")->second: " << my_map.find("5!")->second << std::endl;
    //using iterator with map to delete anything in map from first key to "key2":
    //std::map<std::string, char>::iterator it; //better with auto(next line), as it can hold better if find doesn't find key.
    auto it = my_map.find("key1");
    it = my_map.find("key2");
    if (it != my_map.end())
        std::cout << "it->first(key): " << it->first << " (*it).second (element): " << (*it).second << std::endl;
    my_map.erase(it);
    //pair, than add to map:
    std::pair<std::string, char>sixss("66", 'f');
    my_map.insert(sixss);
    //printing all map
    for (auto itr = my_map.begin(); itr != my_map.end(); ++itr) {
        std::cout << itr->first << '\t' << itr->second << '\n'; //\t meaning tab
    }
    my_map.erase("67"); //do nothing, as there isn't any...
    my_map.erase(sixss.first); //delete pair "66" 'f' , could write as well: my_map.erase("66");

    //delete map:
    my_map.clear();

    //~~~Do while, cin, boolean example~~~
    bool dowl = true;
    char check_answer;
    do {
        std::cout << "Would you like to see the general \"Hello World!\" theme? y/n \n";
        std::cin >> check_answer;
        if (check_answer == 'y')
        {
            dowl = false;
        }
        else
            std::cout << "Try again! :) \n";
    } while (dowl);
    std::cout << "Hello World!\n";
    //~~~list example~~~:
    std::list<double>my_ex_Lst = { 1.1,2.2,3.3,6.6,13.2 };
    my_ex_Lst.push_back(80.08);
    //print it:
    // function for printing the elements in a list
    showlist(my_ex_Lst);
    std::cout << "printing last cell in list, \nusefull checking end of list in foreach loop: my_ex_Lst.back(): " << my_ex_Lst.back() << std::endl;

    //~~~count_if example~~~ (+lambda func):
    std::vector<int> myvector;
    for (int i = 1; i < 10; i++) myvector.push_back(i); // myvector: 1 2 3 4 5 6 7 8 9

    int four = 4;
    int mycount = std::count_if(myvector.begin(), myvector.end(), [](int i) {std::cout << "i=" << i << "  "; return ((i % 2) == 1); });
    std::cout << "\ncount_if example: myvector contains " << mycount << " odd values.\n";

    //~~priority quoue~~:
    std::priority_queue<int> prq;
    prq.push(1);
    prq.push(2);
    prq.push(3);
    int pop_q = prq.top();
    std::cout << "priority quoue (push 1->2->3) prq.top() = " << pop_q << std::endl;
    prq.pop();
    std::cout << "priority quoue (push 1->2->3) prq.top() after pop = " << prq.top() << std::endl;

    //no simple iterator, take out with top() into another quoue..
    std::cout << "print pq: ";
    std::priority_queue<int> temp = prq;
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;

    //~~stack examle:~~
    using namespace std;
    stack<int> mystack;
    mystack.push(21);
    mystack.push(22);
    mystack.push(24);
    mystack.push(25);

    mystack.pop();
    mystack.pop();

    std::cout << "stack print ex:" << std::endl;
    while (!mystack.empty()) {
        cout << " " << mystack.top();
        mystack.pop();
    }
    std::cout << std::endl;
    //~~array:
    int my_arr[4] = { 1,2 };
    my_arr[3] = 9;
    int igoesup = 0;
    for (int& var : my_arr)
    {
        std::cout << "array[" << igoesup << "]= " << var << std::endl;
        igoesup += 1;
    }

    //~~lambda + for_each ~~:
    sort(myvector.begin(), myvector.end(), [](const int& a, const int& b) { return a > b; } );
    std::list<check_delete*>class_ex;
    check_delete* aaa = new check_delete(1);
    check_delete* bbb = new check_delete(2);
    check_delete* ccc = new check_delete(3);
    class_ex.push_back(aaa);
    class_ex.push_back(bbb);
    class_ex.push_back(ccc);
    for_each(class_ex.begin(), class_ex.end(), [](check_delete* i) { //can be (auto i) as well
        delete i;
        });
    //~~by value/reference/pointer:~~
    //value by value (coping val):
    int mynumval = 15;
    std::cout << "~value by value~" << mynumval << std::endl;
    std::cout << "address original: " << &mynumval << std::endl;
    int res0 = func_to_learn_val_by_value(mynumval);
    std::cout << "address returned: " << &res0 << " val: " << res0 << std::endl;
    //reference by value:
    intptr_t mynum1= 15;
    std::cout << "~reference by value~" << mynum1 << std::endl;
    std::cout << "address original: " << &mynum1 << std::endl;
    int res1 = func_to_learn_ref_by_value(mynum1);
    std::cout << "address returned: " << &res1 <<  " val: " << res1<< std::endl;
    //val by ptr:
    int mynum2 = 15;
    std::cout << "~val by ptr~" << mynum2 << std::endl;
    std::cout << "address original: " << &mynum2 << std::endl;
    int res2 = func_to_learn_val_by_ptr(&mynum2);
    std::cout << "address returned: " << &res2 << " val: " << res2 << std::endl;
    //val by reference:
    int mynum3 = 15;
    std::cout << "~val by reference~ " << mynum3 <<std::endl;
    std::cout << "address original: " << &mynum3 << std::endl;
    int res3 = func_to_learn_val_by_reference(mynum3);
    std::cout << "address returned: " << &res3 << " val: " << res3 << std::endl;
    //ref by reference:
    intptr_t mynum4 = 26;
    std::cout << "~ref by reference:~" << mynum4 << std::endl;
    std::cout << "address original: " << &mynum4 << std::endl;
    int res4 = func_to_learn_ref_by_reference(mynum4);
    std::cout << "address returned: " << &res4 <<" val: "<< res4 << std::endl;
    return EXIT_SUCCESS; //To the lucky one ;) who may read it, learn as well about uniqe ptr, make uniqe, share lock, lock guard, catch throw error, send funcion to func, mutex, imutable, sleep, threads in general.
}