/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 18.03.2018
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o 150140117
 
 * * * * * * * * * * * * * * * * * */

#include "Graph.h"

Graph::Graph() {
    Node* initial = new Node;
    (*initial).update(EAST, EAST, EAST, EAST);
    nodes.push_back(initial);
    
    Node* parent = initial;
    safeQueue.push(initial);
    
    Node* insert;
    while(!(nodes.back()->isFinal())) {
        insert = safeQueue.front();
        safeQueue.pop();
        if (!insert->adjacency.empty())
            parent = (*insert).adjacency.back();

        if (insert->farmer == EAST) {
            insertNode(WEST,insert->rabbit,insert->fox,insert->carrots,parent,insert);
        
            if(insert->rabbit == EAST)
                insertNode(WEST,WEST,insert->fox,insert->carrots,parent,insert);
            
            if(insert->fox == EAST)
                insertNode(WEST,insert->rabbit,WEST,insert->carrots,parent,insert);
            
            if(insert->carrots == EAST)
                insertNode(WEST,insert->rabbit,insert->fox,WEST,parent,insert);
        } else {
            insertNode(EAST,insert->rabbit,insert->fox,insert->carrots,parent,insert);
            
            if(insert->rabbit == WEST)
                insertNode(EAST,EAST,insert->fox,insert->carrots,parent,insert);
            
            if(insert->fox == WEST)
                insertNode(EAST,insert->rabbit,EAST,insert->carrots,parent,insert);
            
            if(insert->carrots == WEST)
                insertNode(EAST,insert->rabbit,insert->fox,EAST,parent,insert);
        }
    }
}

Graph::~Graph() {
    for(int i = 0; i < nodes.size(); i++)
        delete nodes[i];
}

void Graph::insertNode(Position farmer, Position rabbit, Position fox,
                       Position carrot, Node* parent, Node* insert) {
    Node* newNode = new Node;
    newNode->update(farmer,rabbit,fox,carrot);
    if (findDuplicate(newNode,insert) == nullptr) {
        newNode->adjacency.push_back(insert);
        insert->adjacency.push_back(newNode);
        nodes.push_back(newNode);
        
        if (newNode->safe)
            safeQueue.push(newNode);
    } else {
        Node* duplicate = findDuplicate(newNode, insert);
        if (*duplicate != *parent && duplicate->safe &&
            duplicate->farmer != NOTSPECIFIED) {
            duplicate->adjacency.push_back(insert);
            insert->adjacency.push_back(duplicate);
        }
        
        if (duplicate->farmer == NOTSPECIFIED)
            delete duplicate;
        
        delete newNode;
    }
}

Node* Graph::findDuplicate(Node* const compare, Node* const parent){
    for(int i = 0; i < nodes.size(); i++) {
        if (*compare == *(nodes[i])) {
            for(int j = 0; j < nodes[i]->adjacency.size(); j++) {
                if (*parent == *(nodes[i])->adjacency[j]) {
                    Node* dumb = new Node;
                    return dumb;
                }
            }
            return nodes[i];
        }
    }
    return nullptr;
}

void Graph::bfsSolve() const {
    return;
}

void Graph::dfsSolve() const {
    return;
}
