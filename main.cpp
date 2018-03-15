/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 18.03.2018
 * * * * * * * * * * * * * * * * * *
 
 Compile command: g++ -std=c++11 main.cpp -o 150140117
 
 * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>

#include "Graph.h"

using namespace std;

#ifndef type_enum
#define type_enum
typedef enum Algorithm {
    NONE = 0, BFS, DFS
} ALGORITHM;
#endif

int main(int argc, const char * argv[]) {
    // All arguments must be passed with run command
    if (argc != 2) {
        cout << "Missing arguments to proceed." << endl << endl;
        return 0;
    }
    
    string algorithmInput(argv[1]);
    ALGORITHM algorithmSelection = NONE;
    
    if (algorithmInput.compare("bfs") == 0)
        algorithmSelection = BFS;
    else if (algorithmInput.compare("dfs") == 0)
        algorithmSelection = DFS;
    else {
        cout << "Please select either 'bfs' or 'dfs' algorithms." << endl << endl;
        return 0;
    }
    
    return 0;
}
