#include "solve.h"
#include <queue>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

// Add a vertex to the graph with the given identifier
void mazeGraph::addVertex(string x, char data) {
    size_t commaPos = x.find(',');
    int row = stoi(x.substr(0, commaPos));
    int col = stoi(x.substr(commaPos + 1));
    
    Vertex *v = new Vertex(row, col);
    v->data = data;
    vertexMap[x] = v;
}

// Add a directed edge from vertex x to vertex y
void mazeGraph::addDirectedEdge(string x, string y) {
    Vertex *from = vertexMap[x];
    Vertex *to = vertexMap[y];
    from->neighs.push_back(to);
}

string mazeGraph::solve(string maze) {
    istringstream mazeStream(maze);
    
    // Read the maze lines
    vector<string> mazeLines;
    string line;
    
    while (getline(mazeStream, line)) {
        mazeLines.push_back(line);
    }
    
    int rows = mazeLines.size();
    int cols = 0;
    for (int i = 0; i < mazeLines.size(); i++) {
        cols = max(cols, static_cast<int>(mazeLines[i].length()));
    }
    
    // Create and initialize the maze data
    vector<vector<char>> mazeData(rows, vector<char>(cols, ' '));
    
    // Fill the maze grid
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < mazeLines[r].length(); c++) {
            mazeData[r][c] = mazeLines[r][c];
        }
    }
    
    // Clean any existing vertices
    for (unordered_map<string, Vertex*>::iterator it = vertexMap.begin(); it != vertexMap.end(); ++it) {
        delete it->second;
    }
    vertexMap.clear();
    
    // Create vertices for non-wall cells
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (mazeData[r][c] != '#') {
                string key = to_string(r) + "," + to_string(c);
                addVertex(key, mazeData[r][c]);
            }
        }
    }
    
    // Add edges between adjacent non-wall cells
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (mazeData[r][c] == '#') continue;
            
            string current = to_string(r) + "," + to_string(c);
            
            // Check all four directions
            int dr[] = {-1, 1, 0, 0};  // up, down, left, right
            int dc[] = {0, 0, -1, 1};
            
            for (int i = 0; i < 4; i++) {
                int newR = r + dr[i];
                int newC = c + dc[i];
                
                // Check if new position is valid and not a wall
                if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && 
                    mazeData[newR][newC] != '#') {
                    string neighbor = to_string(newR) + "," + to_string(newC);
                    addDirectedEdge(current, neighbor);
                }
            }
        }
    }
    
    // Find the start vertex (a non-wall cell on the edge)
    Vertex *start = nullptr;
    for (int r = 0; r < rows && !start; r++) {
        for (int c = 0; c < cols && !start; c++) {
            // Check if it's on the edge and not a wall
            if ((r == 0 || r == rows-1 || c == 0 || c == cols-1) && 
                mazeData[r][c] != '#') {
                string key = to_string(r) + "," + to_string(c);
                if (vertexMap.find(key) != vertexMap.end()) {
                    start = vertexMap[key];
                }
            }
        }
    }
    
    // No start found
    if (!start) return maze;  // Return original maze if no path
    
    // BFS to find shortest path
    queue<Vertex*> q;
    unordered_set<Vertex*> visited;
    unordered_map<Vertex*, Vertex*> parent;
    
    q.push(start);
    visited.insert(start);
    
    Vertex *end = nullptr;
    
    // Run BFS
    while (!q.empty() && !end) {
        Vertex *current = q.front();
        q.pop();
        
        // Check if this is another edge point (potential end) different from start
        if (current != start && 
            (current->row == 0 || current->row == rows-1 || 
             current->col == 0 || current->col == cols-1)) {
            end = current;
            break;
        }
        
        // Process neighbors
        for (size_t i = 0; i < current->neighs.size(); i++) {
            Vertex *next = current->neighs[i];
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
                parent[next] = current;
            }
        }
    }
    
    // No path found
    if (!end) return maze;  // Return original maze if no path
    
    // Create a path map to store all cells in the path
    unordered_set<string> pathCells;
    
    // Trace back from end to start
    Vertex *current = end;
    while (current != nullptr) {
        string key = to_string(current->row) + "," + to_string(current->col);
        pathCells.insert(key);
        if (current == start) break;
        
        unordered_map<Vertex*, Vertex*>::iterator it = parent.find(current);
        if (it == parent.end()) break;
        current = it->second;
    }
    
    // Create result string
    string result = "";
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < mazeLines[r].length(); c++) {
            string key = to_string(r) + "," + to_string(c);
            if (pathCells.find(key) != pathCells.end()) {
                result += 'o';
            } else {
                result += mazeLines[r][c];
            }
        }
        result += "\n";  // Add newline after each row
    }
    
    // Remove the last newline if the original maze doesn't have it
    if (!maze.empty() && maze.back() != '\n') {
        result.pop_back();
    }
    
    return result;
}

// Global solve function - what main.cpp calls
string solve(string maze) {
    // Create a mazeGraph instance and delegate to its solve method
    mazeGraph graph;
    return graph.solve(maze);
}