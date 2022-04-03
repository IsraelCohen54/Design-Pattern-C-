//question from exam in advanced cpp:
/*
#include <iostream>
using namespace std;

// 31 points
class Graph {
    size_t vs;// Vertices
    bool** adjMat; // Adjacency Matrix
    void clear() { // frees the matrix
        cout << "clear()" << endl;
        if (adjMat != nullptr) {
            for (size_t i = 0; i < vs; i++)
                delete[] adjMat[i];
            delete[] adjMat;
        }
    }

public:
    Graph(size_t vs) : vs(vs) { // constructor
        cout << "Graph(size_t vs)" << endl;
        adjMat = new bool* [vs];
        for (size_t i = 0; i < vs; i++) {
            adjMat[i] = new bool[vs];
            for (size_t j = 0; j < vs; j++)
                adjMat[i][j] = false;
        }
    }

    void addEdge(size_t i, size_t j) { // adds an edge
        if (i < vs && j < vs)
            adjMat[i][j] = true;
    }
    // continue the implementation from here:

    // copy constructor
    Graph(const Graph& g) { // Signature 1 point
        cout << "Graph(const Graph &g)" << endl;
        adjMat = nullptr; // use of null to avoid segmentation fault bug 3 points
        *this = g; // reuse of assignment operator 3 points
    }

    // OPERATOR =
    Graph& operator=(const Graph& g) { // Signature 2 points
        cout << "Graph &operator=(const Graph &g)" << endl;
        if (this != &g) { // avoid bug g=g 3 points
            clear(); // clearing old allocation 3 points
// copying - 1 point
            vs = g.vs;
            adjMat = new bool* [vs];
            for (size_t i = 0; i < vs; i++) {
                adjMat[i] = new bool[vs];
                for (size_t j = 0; j < vs; j++)
                    adjMat[i][j] = g.adjMat[i][j];

            }
        }
        return *this;// 1 point
    }

    // move constructor
    Graph(Graph&& g) noexcept { // Signature 2 points
        cout << "Graph(Graph &&g)" << endl;
        *this = move(g); // reuse of assignment (move) operator 3 points
    }

    // move OPERATOR =
    Graph& operator=(Graph&& g) noexcept{ // Signature 2 points
        cout << "Graph &operator=(Graph &&g)" << endl;
        if (this != &g) {// avoid bug 2 points
// correct move 3 points
            vs = g.vs;
            adjMat = g.adjMat;
            g.vs = 0;
            g.adjMat = nullptr;
        }
        return *this;
    }

    ~Graph() { // 2 points
        cout << "~Graph()" << endl;
        clear();
    }
};

int main() {
    
    std::cout << "Hello, World!" << std::endl;
    Graph g1 =  Graph(5);
    Graph g2 = g1; //copy constructor, Graph(const Graph &g)-> Graph &operator=(const Graph &g)

    Graph *g3 =  new Graph(5);
    Graph g4 = *g3; //copy constructor, Graph(const Graph &g)-> Graph &operator=(const Graph &g)
    
    Graph *g5 =  new Graph(5);
    Graph *g6 = g5; //nothing

    Graph g7 = Graph(5);
    Graph g8 = move(g7); //move constructor, Graph(Graph &&g)-> Graph &operator=(Graph &&g)

    Graph *g9 =  new Graph(5);
    Graph g10 = move(*g9); //move constructor, Graph(Graph &&g)-> Graph &operator=(Graph &&g)

    g3->~Graph();
    g5->~Graph();
    g9->~Graph();
    std::cout << "FINISH" << std::endl;
    return 0;
    
}*/
