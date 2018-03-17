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
    initial->update(EAST, EAST, EAST, EAST); // Start node
    initial->nodeId = 0;
    nodes.push_back(initial); // Insert start node
    
    Node* parent = initial;
    safeQueue.push(initial); // Safe state queue
    
    Node* insert;
    while(!safeQueue.empty()) {
        insert = safeQueue.front(); // Node that will have create new nodes
        safeQueue.pop();
        
        // Find parent of that node to avoid infinite loop
        if (!insert->adjacency.empty())
            parent = (*insert).adjacency.back(); // Parent is the last adjacent

        if (insert->farmer == EAST) { // If farmer is in the East side of the river
            // Only farmer moves to WEST side
            insertNode(WEST,insert->rabbit,insert->fox,insert->carrots,parent,insert);
        
            // Farmer moves with rabbit if it is in the East side as well
            if(insert->rabbit == EAST)
                insertNode(WEST,WEST,insert->fox,insert->carrots,parent,insert);
            
            // Farmer moves with fox if it is in the East side as well
            if(insert->fox == EAST)
                insertNode(WEST,insert->rabbit,WEST,insert->carrots,parent,insert);
            
            // Farmer moves with carrots if they are in the East side as well
            if(insert->carrots == EAST)
                insertNode(WEST,insert->rabbit,insert->fox,WEST,parent,insert);
        } else {
            // Only farmer moves to East side
            insertNode(EAST,insert->rabbit,insert->fox,insert->carrots,parent,insert);
            
            // Farmer moves with rabbit if it is in the West side as well
            if(insert->rabbit == WEST)
                insertNode(EAST,EAST,insert->fox,insert->carrots,parent,insert);
            
            // Farmer moves with fox if it is in the West side as well
            if(insert->fox == WEST)
                insertNode(EAST,insert->rabbit,EAST,insert->carrots,parent,insert);
            
            // Farmer moves with carrots if they are in the West side as well
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
    if (findDuplicate(newNode,insert) == nullptr) { // New node
        // Node can only be adjacent to its father if it is a safe state
        if (newNode->safe)
            newNode->adjacency.push_back(insert);
        insert->adjacency.push_back(newNode); // Adjacent to father
        newNode->nodeId = static_cast<int>(nodes.size()); // Assign id
        nodes.push_back(newNode); // Insert node to graph
        
        /* If safe state, add it to queue to find other nodes can be
         created from this node. */
        if (newNode->safe)
            safeQueue.push(newNode);
    } else {
        Node* duplicate = findDuplicate(newNode, insert);
        // Avoid infinite loop while creating the graph.
        if (*duplicate != *parent && duplicate->farmer != NOTSPECIFIED) {
            /* If |duplicate| node is not a safe state, it cannot be
             adjacent of the node being inserted. */
            if (duplicate->safe)
                duplicate->adjacency.push_back(insert);
            insert->adjacency.push_back(duplicate);
        } else
            delete duplicate;
        
        // Created node is useless since it will not be inserted to the graph.
        delete newNode;
    }
}

Node* Graph::findDuplicate(Node* const compare, Node* const parent) {
    /* This function determines if the |compare| node is already
     in the graph. If it is, returns the pointer to that node
     int th graph. */
    
    for(int i = 0; i < nodes.size(); i++) {
        if (*compare == *(nodes[i])) {
            for(int j = 0; j < nodes[i]->adjacency.size(); j++) {
                if (*parent == *(nodes[i])->adjacency[j]) {
                    /* If duplicated node is parent of the
                     node being check, return a dumb node to
                     avoid infinite loop while creating graph. */
                    
                    Node* dumb = new Node;
                    return dumb;
                }
            }
            return nodes[i]; // Return already inserted node
        }
    }
    return nullptr;
}

int Graph::findNode(Position farmer, Position rabbit,
                    Position fox, Position carrot) const {
    // Create a node to compare
    Node find(farmer,rabbit,fox,carrot);
    for(int i = 0; i < nodes.size(); i++) {
        if (find == *nodes[i])
            return nodes[i]->nodeId; // Found
    }
    return -1; // not found
}

void Graph::bfsSolve() const {
    /* This function is implemented according to pseudocode provided
     in the Recitation-2 slide. */
    
    int visitCount = 1;
    int maxMem = 0;
    float runtime = 0.0;
    int size = static_cast<int>(nodes.size());
    int start = findNode(EAST, EAST, EAST, EAST);
    int end = findNode(WEST, WEST, WEST, WEST);
    
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
    flag[start] = true;
    bfsQueue.push(nodes[start]);
    
    while(!bfsQueue.empty()) {
        Node* v = bfsQueue.front();
        bfsQueue.pop();
        
        int adjSize = static_cast<int>(v->adjacency.size());
        
        for(int i = 0; i < adjSize; i++) {
            Node* w = v->adjacency[i];
            if(flag[w->nodeId] == false) { // Unvisited node
                flag[w->nodeId] = true; // Mark as visited
                prev[w->nodeId] = v;
                bfsQueue.push(w); // Add to the stack
                
                if(bfsQueue.size() > maxMem)
                    maxMem = static_cast<int>(bfsQueue.size());
                
                visitCount++;
            }
        }
    }
    
    
    /* It uses stack to order print elements since path found by
     DFS can be reach by iterating starting from the End node to
     Start node which is reverse ordered. */
    stack<Node*> printStack;
    
    int solutionCount = 0;
    int visited = end;
    while(visited != start) {
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
    
    // Print moves and states
    while(!printStack.empty()) {
        Node* current = printStack.top();
        printStack.pop();
        current->printNode();
        if(!printStack.empty())
            current->printMove(printStack.top());
    }
}

void Graph::dfsSolve() const {
    /* This function is implemented according to pseudocode provided
     in the Graph slide. */
    
    int visitCount = 0;
    int maxMem = 0;
    float runtime = 0.0;
    int size = static_cast<int>(nodes.size());
    int start = findNode(EAST, EAST, EAST, EAST); // Start node id
    int end = findNode(WEST, WEST, WEST, WEST); // End node id
    
    using namespace chrono;
    auto dfsStart = high_resolution_clock::now(); // Begin time stamp
    
    stack<Node*> dfsStack;
    vector<bool> explored;
    explored.resize(size); // Make room for elements
    
    for(int i = 0; i < size; i++)
        explored[i] = false;
    
    dfsStack.push(nodes[start]); // Add start node to stack
    
    vector<Node*> parent;
    parent.resize(size); // Make room for elements
    
    while(!dfsStack.empty()) {
        Node* u = dfsStack.top();
        dfsStack.pop();
        if(explored[u->nodeId] == false) {
            explored[u->nodeId] = true;
            
            int adjSize = static_cast<int>(u->adjacency.size());
            
            for(int i = 0; i < adjSize; i++) {
                Node* v = u->adjacency[i];
                if(explored[v->nodeId] == false) {
                    dfsStack.push(v);
                    parent[v->nodeId] = u;
                }
                
                if(dfsStack.size() > maxMem)
                    maxMem = static_cast<int>(dfsStack.size());
                
            }
            visitCount++;
        }
    }
    
    /* It uses stack to order print elements since path found by
     DFS can be reach by iterating starting from the End node to
     Start node which is reverse ordered. */
    stack<Node*> printStack;
    
    int solutionCount = 0;
    int visited = end;
    while(visited != start) {
        printStack.push(nodes[visited]);
        visited = parent[visited]->nodeId;
        solutionCount++;
    }
    printStack.push(nodes[visited]); // Add start node
    
    auto dfsEnd = high_resolution_clock::now(); // Begin time stamp
    // Get the elapsed time in unit microseconds
    runtime = duration_cast<microseconds>(dfsEnd - dfsStart).count();
    runtime /= 1000;
    
    cout << "Algorithm: DFS" << endl;
    cout << "Number of the visited nodes: " << visitCount << endl;
    cout << "Maximum number of nodes kept in the memory: " << maxMem << endl;
    cout << "Running time: " << fixed << setprecision(3) << runtime << " milliseconds" << endl;
    cout << "Solution move count: " << solutionCount << endl;
    
    // Print moves and states
    while(!printStack.empty()) {
        Node* current = printStack.top();
        printStack.pop();
        current->printNode();
        if(!printStack.empty())
            current->printMove(printStack.top());
    }
}
