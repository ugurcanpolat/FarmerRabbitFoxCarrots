/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 18.03.2018
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o project1
 
 * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>

#include "Graph.cpp"

int main(int argc, const char * argv[]) {
    // All arguments must be passed with run command
    if (argc != 2) {
        cout << "Missing arguments to proceed." << endl << endl;
        return 0;
    }
    
    std::string algorithmInput(argv[1]);
    Algorithm algorithmSelection = NONE;
    
    if (algorithmInput.compare("bfs") == 0)
        algorithmSelection = BFS;
    else if (algorithmInput.compare("dfs") == 0)
        algorithmSelection = DFS;
    else {
        cout << "Please select either 'bfs' or 'dfs' algorithms." << endl << endl;
        return 0;
    }
    
    Graph graph;
    
    switch (algorithmSelection) {
        case BFS:
            graph.bfsSolve();
            break;
            
        case DFS:
            graph.dfsSolve();
            break;
            
        default:
            cout << "Invalid algorithm type." << endl << endl;
            return 0;
    }
    
    return 0;
}
