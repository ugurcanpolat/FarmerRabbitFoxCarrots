/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 18.03.2018
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o project1
 
 * * * * * * * * * * * * * * * * * */

#ifndef Graph_h
#define Graph_h

#include <chrono> // high_resolution_clock
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <iomanip>

#include "Types.h"

using namespace std;

class Graph {
  private:
    vector<Node*> nodes;
    queue<Node*> safeQueue;
    void insertNode(Position farmer, Position rabbit, Position fox,
                    Position carrot, Node* parent, Node* insert);
    Node* findDuplicate(Node* const compare, Node* const parent);
    int findNode(Position farmer, Position rabbit,
                   Position fox, Position carrot) const;
    vector<Node*> dfsPath(Node* start, Node* end, vector<bool> explored,
                          vector<Node*> path) const;
  public:
    Graph();
    ~Graph();
    void bfsSolve() const;
    void dfsSolve() const;
};

#endif /* Graph_h */
