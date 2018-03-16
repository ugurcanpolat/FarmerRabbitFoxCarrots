/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 18.03.2018
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o 150140117
 
 * * * * * * * * * * * * * * * * * */

#ifndef Types_h
#define Types_h

#include <vector>

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
    bool isFinal() const;
    void update(Position pFarmer, Position pRabbit,
                Position pFox, Position pCarrots);
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
    
    if (pRabbit == pFox && pFarmer != pRabbit)
        return false;
    else if (pRabbit == pCarrots && pFarmer != pRabbit)
        return false;
    else
        return true;
}

bool Node::isFinal() const {
    if (farmer == WEST && rabbit == WEST &&
        fox == WEST    && carrots == WEST)
        return true;
    else
        return false;
}

void Node::update(Position pFarmer, Position pRabbit,
                  Position pFox, Position pCarrots) {
    farmer  = pFarmer;
    rabbit  = pRabbit;
    fox     = pFox;
    carrots = pCarrots;
    safe    = isSafe(pFarmer, pRabbit, pFox, pCarrots);
}

#endif /* Types_h */
