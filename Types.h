/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 18.03.2018
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o project1
 
 * * * * * * * * * * * * * * * * * */

#ifndef Types_h
#define Types_h

#include <iostream> // cout
#include <vector> // vector

using namespace std;

typedef enum Algorithm {
    NONE = 0, BFS, DFS
} Algorithm;

typedef enum Position {
    NOTSPECIFIED = 0, EAST, WEST
} Position;

typedef class Node {
  public:
    Node();
    Node(Position pFarmer, Position pRabbit,
         Position pFox, Position pCarrots);
    bool operator==(const Node& compare);
    bool operator!=(const Node& compare);
    bool isSafe(Position pFarmer, Position pRabbit,
                Position pFox, Position pCarrots) const;
    void update(Position pFarmer, Position pRabbit,
                Position pFox, Position pCarrots);
    void printNode() const;
    void printMove(Node* const next);
    int nodeId;
    Position farmer;
    Position rabbit;
    Position fox;
    Position carrots;
    bool safe;
    std::vector<Node*> adjacency;
} Node;

Node::Node() {
    farmer  = NOTSPECIFIED;
    rabbit  = NOTSPECIFIED;
    fox     = NOTSPECIFIED;
    carrots = NOTSPECIFIED;
    safe    = false;
}

Node::Node(Position pFarmer, Position pRabbit,
           Position pFox, Position pCarrots) {
    farmer  = pFarmer;
    rabbit  = pRabbit;
    fox     = pFox;
    carrots = pCarrots;
    safe    = isSafe(pFarmer, pRabbit, pFox, pCarrots);
}

bool Node::operator==(const Node& compare) {
    if (farmer == compare.farmer && rabbit == compare.rabbit &&
        fox == compare.fox && carrots == compare.carrots)
        return true;
    else
        return false;
}

bool Node::operator!=(const Node& compare) {
    return !(*this == compare);
}

bool Node::isSafe(Position pFarmer, Position pRabbit,
                  Position pFox, Position pCarrots) const {
    
    /* Check if it is a safe state or not */
    
    if (pRabbit == pFox && pFarmer != pRabbit)
        return false;
    else if (pRabbit == pCarrots && pFarmer != pRabbit)
        return false;
    else
        return true;
}

void Node::update(Position pFarmer, Position pRabbit,
                  Position pFox, Position pCarrots) {
    farmer  = pFarmer;
    rabbit  = pRabbit;
    fox     = pFox;
    carrots = pCarrots;
    safe    = isSafe(pFarmer, pRabbit, pFox, pCarrots);
}

void Node::printNode() const {
    if(farmer == EAST)
        cout << "Farmer ";
    if(rabbit == EAST)
        cout << "Rabbit ";
    if(carrots == EAST)
        cout << "Carrot ";
    if(fox == EAST)
        cout << "Fox ";
    cout << "|| ";
    if(farmer == WEST)
        cout << "Farmer ";
    if(rabbit == WEST)
        cout << "Rabbit ";
    if(carrots == WEST)
        cout << "Carrot ";
    if(fox == WEST)
        cout << "Fox ";
    cout << endl;
}

void Node::printMove(Node* const next) {
    cout << "(Farmer,";
    if(farmer == EAST) {
        if(rabbit != next->rabbit)
            cout << " Rabbit, ";
        if(carrots != next->carrots)
            cout << " Carrot, ";
        if(fox != next->fox)
            cout << " Fox, ";
        cout << ">)" << endl;
    } else {
        if(rabbit != next->rabbit)
            cout << " Rabbit, ";
        if(carrots != next->carrots)
            cout << " Carrot, ";
        if(fox != next->fox)
            cout << " Fox, ";
        cout << "<)" << endl;
    }
}

#endif /* Types_h */
