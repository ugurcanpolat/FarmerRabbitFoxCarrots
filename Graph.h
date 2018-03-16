/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 18.03.2018
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o 150140117
 
 * * * * * * * * * * * * * * * * * */

#ifndef Graph_h
#define Graph_h

#include <string>
#include <vector>
#include <queue>

#include "Types.h"

using namespace std;

class Graph {
  private:
    vector<Node*> nodes;
    queue<Node*> safeQueue;
    void insertNode(Position farmer, Position rabbit, Position fox,
                    Position carrot, Node* parent, Node* insert);
    Node* findDuplicate(Node* const compare, Node* const parent);
  public:
    Graph();
    ~Graph();
    void bfsSolve() const;
    void dfsSolve() const;
};

#endif /* Graph_h */
