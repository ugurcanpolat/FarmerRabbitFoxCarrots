/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 18.03.2018
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o project1
 
 * * * * * * * * * * * * * * * * * */

#include "Graph.h"

Graph::Graph() {
    Node* initial = new Node;
    initial->update(EAST, EAST, EAST, EAST);
    initial->nodeId = 0;
    nodes.push_back(initial);
    
    Node* parent = initial;
    safeQueue.push(initial);
    
    Node* insert;
    while(!safeQueue.empty()) {
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
        if (newNode->safe)
            newNode->adjacency.push_back(insert);
        insert->adjacency.push_back(newNode);
        newNode->nodeId = static_cast<int>(nodes.size());
        nodes.push_back(newNode);
        
        if (newNode->safe)
            safeQueue.push(newNode);
    } else {
        Node* duplicate = findDuplicate(newNode, insert);
        if (*duplicate != *parent && duplicate->farmer != NOTSPECIFIED) {
            if (duplicate->safe)
                duplicate->adjacency.push_back(insert);
            insert->adjacency.push_back(duplicate);
        } else
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

int Graph::findNode(Position farmer, Position rabbit,
                    Position fox, Position carrot) const {
    Node find(farmer,rabbit,fox,carrot);
    for(int i = 0; i < nodes.size(); i++) {
        if (find == *nodes[i])
            return nodes[i]->nodeId;
    }
    return -1;
}

void Graph::bfsSolve() const {
    int visitCount = 1;
    int maxMem = 0;
    float runtime = 0.0;
    int size = static_cast<int>(nodes.size());
    
    using namespace chrono;
    auto bfsStart = high_resolution_clock::now(); // Begin time stamp
    
    bool flag[size];
    vector<Node*> prev;
    prev.resize(size);
    
    for(int i = 0; i < size; i++) {
        flag[i] = false;
        prev[i] = nullptr;
    }
    
    queue<Node*> bfsQueue;
    flag[0] = true;
    bfsQueue.push(nodes[findNode(EAST, EAST, EAST, EAST)]);
    
    while(!bfsQueue.empty()) {
        Node* v = bfsQueue.front();
        bfsQueue.pop();
        
        int adjSize = static_cast<int>(v->adjacency.size());
        
        for(int i = 0; i < adjSize; i++) {
            Node* w = v->adjacency[i];
            if(flag[w->nodeId] == false) {
                flag[w->nodeId] = true;
                prev[w->nodeId] = v;
                bfsQueue.push(w);
                
                if(bfsQueue.size() > maxMem)
                    maxMem = static_cast<int>(bfsQueue.size());
                
                visitCount++;
            }
        }
    }
    
    stack<Node*> printStack;
    
    int solutionCount = 0;
    int visited = findNode(WEST, WEST, WEST, WEST);
    while(visited != 0) {
        printStack.push(nodes[visited]);
        visited = prev[visited]->nodeId;
        solutionCount++;
    }
    printStack.push(nodes[visited]);
    
    auto bfsEnd = high_resolution_clock::now(); // End time stamp
    // Get the elapsed time in unit microseconds
    runtime = duration_cast<microseconds>(bfsEnd - bfsStart).count();
    runtime /= 1000;
    
    cout << "Algorithm: BFS" << endl;
    cout << "Number of the visited nodes: " << visitCount << endl;
    cout << "Maximum number of nodes kept in the memory: " << maxMem << endl;
    cout << "Running time: " << fixed << setprecision(3) << runtime << " milliseconds" << endl;
    cout << "Solution move count: " << solutionCount << endl;
    
    while(!printStack.empty()) {
        Node* current = printStack.top();
        printStack.pop();
        current->printNode();
        if(!printStack.empty())
            current->printMove(printStack.top());
    }
}

void Graph::dfsSolve() const {
    int visitCount = 0;
    int maxMem = 0;
    float runtime = 0.0;
    int size = static_cast<int>(nodes.size());
    
    using namespace chrono;
    auto dfsStart = high_resolution_clock::now(); // Begin time stamp
    
    stack<Node*> dfsStack;
    vector<bool> explored;
    explored.resize(size);
    
    for(int i = 0; i < size; i++)
        explored[i] = false;
    
    dfsStack.push(nodes[findNode(EAST, EAST, EAST, EAST)]);
    
    int finalNode = findNode(WEST, WEST, WEST, WEST);
    vector<Node*> parent;
    parent.resize(size);
    
    while(!dfsStack.empty()) {
        Node* u = dfsStack.top();
        dfsStack.pop();
        if(explored[u->nodeId] == false) {
            explored[u->nodeId] = true;
            
            int adjSize = static_cast<int>(u->adjacency.size());
            
            for(int i = 0; i < adjSize; i++) {
                Node* v = u->adjacency[i];
                dfsStack.push(v);
                if(explored[v->nodeId] == false)
                    parent[v->nodeId] = u;
                
                if(dfsStack.size() > maxMem)
                    maxMem = static_cast<int>(dfsStack.size());
                
            }
            visitCount++;
        }
    }
    
    stack<Node*> printStack;
    
    int solutionCount = 0;
    int visited = finalNode;
    while(visited != 0) {
        printStack.push(nodes[visited]);
        visited = parent[visited]->nodeId;
        solutionCount++;
    }
    printStack.push(nodes[visited]);
    
    auto dfsEnd = high_resolution_clock::now(); // Begin time stamp
    // Get the elapsed time in unit microseconds
    runtime = duration_cast<microseconds>(dfsEnd - dfsStart).count();
    runtime /= 1000;
    
    cout << "Algorithm: DFS" << endl;
    cout << "Number of the visited nodes: " << visitCount << endl;
    cout << "Maximum number of nodes kept in the memory: " << maxMem << endl;
    cout << "Running time: " << fixed << setprecision(3) << runtime << " milliseconds" << endl;
    cout << "Solution move count: " << solutionCount << endl;
    
    while(!printStack.empty()) {
        Node* current = printStack.top();
        printStack.pop();
        current->printNode();
        if(!printStack.empty())
            current->printMove(printStack.top());
    }
}
