#ifndef SOLVE_H
#define SOLVE_H


#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>

using namespace std;

class mazeGraph
{
private:
    class Vertex
    {
    public:
        Vertex(int r, int c)
        {
            row = r;
            col = c;
        }

        // Corresponding row and column location in maze
        int row;
        int col;

        char data;

        // List of neighboring vertices
        vector<Vertex*> neighs;
    };

    unordered_map<string, Vertex*> vertexMap;

public:
    // Constructor and destructor
    mazeGraph() {}
    ~mazeGraph() {
        // Clean up vertices
        for (auto& pair : vertexMap) {
            delete pair.second;
        }
        vertexMap.clear();
    }

    // Helper methods
    void addVertex(string x, char data = ' ');
    void addDirectedEdge(string x, string y);
    
    // Main solver method for the class
    string solve(string maze);
};

// For the mandatory running time, assume that the time for
// operations of queue, unordered_set, and map are O(1). 
// (They are for average-case, but not worst-case).
//
// For the mandatory running time below, s is the length of 
// the input string representing the maze.
// 
// For a complete description of the maze string 
// and maze solution formats, see the assignment pdf.

// Global solve function - this is what main.cpp calls
// Has undefined behavior if the maze is not valid or has no solution.
// Must run in O(s) time.
string solve(string maze);

#endif 

