# Maze Solver Using BFS and Graph Representation

This program solves the problem of finding the shortest path through a maze. Given any maze represented as a string with '#' as walls and spaces as paths, the program finds the shortest path from one edge to another edge, using a breadth-first search algorithm on a graph representation of the maze.

This maze solver is implemented in C++ using object-oriented design principles and standard library containers. Here's an overview of the implementation:

# Visualization of Maze Solver Execution

Let's trace through the execution of each function for the simple maze:

```
##### #
#     #
# #####
```

## 1. Global solve(maze) Function

The main function receives this maze string and creates a `mazeGraph` object to solve it:

```cpp
string solve(string maze) {
    mazeGraph graph;
    return graph.solve(maze);
}
```

## 2. mazeGraph::solve(maze) Function

### Step 1: Parse the maze string
```
Reading lines:
Line 1: "##### #"
Line 2: "#     #"
Line 3: "# #####"

Determined dimensions: rows=3, cols=7
```

### Step 2: Create 2D grid representation
```
Maze grid:
['#', '#', '#', '#', '#', ' ', '#']
['#', ' ', ' ', ' ', ' ', ' ', '#']
['#', ' ', '#', '#', '#', '#', '#']
```

### Step 3: Create vertices for non-wall cells

```cpp
// Clean any existing vertices
vertexMap cleared

// Create vertices for each open cell (non-wall)
Creating vertex at (0,5) with key "0,5"
Creating vertex at (1,1) with key "1,1"
Creating vertex at (1,2) with key "1,2"
Creating vertex at (1,3) with key "1,3"
Creating vertex at (1,4) with key "1,4"
Creating vertex at (1,5) with key "1,5"
Creating vertex at (2,1) with key "2,1"
```

### Step 4: Add edges between adjacent cells

For each vertex, checking neighbors in all 4 directions (up, down, left, right):

```
For vertex (0,5):
  - Adding edge to (1,5) (down)

For vertex (1,1):
  - Adding edge to (1,2) (right)
  - Adding edge to (2,1) (down)

For vertex (1,2):
  - Adding edge to (1,1) (left)
  - Adding edge to (1,3) (right)

For vertex (1,3):
  - Adding edge to (1,2) (left)
  - Adding edge to (1,4) (right)

For vertex (1,4):
  - Adding edge to (1,3) (left)
  - Adding edge to (1,5) (right)

For vertex (1,5):
  - Adding edge to (0,5) (up)
  - Adding edge to (1,4) (left)

For vertex (2,1):
  - Adding edge to (1,1) (up)
```

Resulting graph structure:
```
vertexMap = {
  "0,5": Vertex(row=0, col=5, neighs=[(1,5)]),
  "1,1": Vertex(row=1, col=1, neighs=[(1,2), (2,1)]),
  "1,2": Vertex(row=1, col=2, neighs=[(1,1), (1,3)]),
  "1,3": Vertex(row=1, col=3, neighs=[(1,2), (1,4)]),
  "1,4": Vertex(row=1, col=4, neighs=[(1,3), (1,5)]),
  "1,5": Vertex(row=1, col=5, neighs=[(0,5), (1,4)]),
  "2,1": Vertex(row=2, col=1, neighs=[(1,1)])
}
```

### Step 5: Find start vertex (an edge cell)

```
Checking edge cells:
- Found (0,5) as an edge cell
- Set start = Vertex at (0,5)
```

### Step 6: Run BFS to find shortest path

```
Initialize:
- Queue: [(0,5)]
- Visited: {(0,5)}
- Parent: {}

Iteration 1:
- Current = (0,5)
- Neighbors: [(1,5)]
- Add (1,5) to queue and visited
- Parent[(1,5)] = (0,5)
- Queue: [(1,5)]
- Visited: {(0,5), (1,5)}

Iteration 2:
- Current = (1,5)
- Neighbors: [(0,5), (1,4)]
- (0,5) already visited, skip
- Add (1,4) to queue and visited
- Parent[(1,4)] = (1,5)
- Queue: [(1,4)]
- Visited: {(0,5), (1,5), (1,4)}

Iteration 3:
- Current = (1,4)
- Neighbors: [(1,3), (1,5)]
- (1,5) already visited, skip
- Add (1,3) to queue and visited
- Parent[(1,3)] = (1,4)
- Queue: [(1,3)]
- Visited: {(0,5), (1,5), (1,4), (1,3)}

Iteration 4:
- Current = (1,3)
- Neighbors: [(1,2), (1,4)]
- (1,4) already visited, skip
- Add (1,2) to queue and visited
- Parent[(1,2)] = (1,3)
- Queue: [(1,2)]
- Visited: {(0,5), (1,5), (1,4), (1,3), (1,2)}

Iteration 5:
- Current = (1,2)
- Neighbors: [(1,1), (1,3)]
- (1,3) already visited, skip
- Add (1,1) to queue and visited
- Parent[(1,1)] = (1,2)
- Queue: [(1,1)]
- Visited: {(0,5), (1,5), (1,4), (1,3), (1,2), (1,1)}

Iteration 6:
- Current = (1,1)
- Neighbors: [(1,2), (2,1)]
- (1,2) already visited, skip
- Add (2,1) to queue and visited
- Parent[(2,1)] = (1,1)
- Queue: [(2,1)]
- Visited: {(0,5), (1,5), (1,4), (1,3), (1,2), (1,1), (2,1)}

Iteration 7:
- Current = (2,1)
- Edge cell found! This is our end point
- Exit BFS loop
```




## Visualization of BFS Queue Processing

Here's a more visual representation of the BFS queue processing:

```
START: (0,5)
  |
  v
(1,5) -----> (1,4) -----> (1,3) -----> (1,2) -----> (1,1) -----> (2,1) END
```

The parent relationships are:
```
(2,1) ← (1,1) ← (1,2) ← (1,3) ← (1,4) ← (1,5) ← (0,5)
```

And when we trace back, we get the path:
```
(0,5) → (1,5) → (1,4) → (1,3) → (1,2) → (1,1) → (2,1)
```

This creates our solution with all these cells marked as 'o':
```
#####o#
#ooooo#
#o#####
```


### Step 7: Trace back the path from end to start

## How the hashmaps look so we can trace back
## Hash Map Structure (parent)

```
Key (Vertex object)             Value (Parent Vertex object)
-----------------              ------------------------
Vertex at (1,5)    →           Vertex at (0,5)
Vertex at (1,4)    →           Vertex at (1,5)
Vertex at (1,3)    →           Vertex at (1,4)
Vertex at (1,2)    →           Vertex at (1,3)
Vertex at (1,1)    →           Vertex at (1,2)
Vertex at (2,1)    →           Vertex at (1,1)
```

```
Starting at end = (2,1)
pathCells = {(2,1)}
Parent[(2,1)] = (1,1)

Current = (1,1)
pathCells = {(2,1), (1,1)}
Parent[(1,1)] = (1,2)

Current = (1,2)
pathCells = {(2,1), (1,1), (1,2)}
Parent[(1,2)] = (1,3)

Current = (1,3)
pathCells = {(2,1), (1,1), (1,2), (1,3)}
Parent[(1,3)] = (1,4)

Current = (1,4)
pathCells = {(2,1), (1,1), (1,2), (1,3), (1,4)}
Parent[(1,4)] = (1,5)

Current = (1,5)
pathCells = {(2,1), (1,1), (1,2), (1,3), (1,4), (1,5)}
Parent[(1,5)] = (0,5)

Current = (0,5)
pathCells = {(2,1), (1,1), (1,2), (1,3), (1,4), (1,5), (0,5)}
This is the start vertex, exit the loop
```

### Step 8: Construct the solution string
```
For each cell in the maze:
- If cell is in pathCells, put 'o'
- Otherwise, keep the original character

Original:
##### #
#     #
# #####

Result:
#####o#
#ooooo#
#o#####
```

The BFS algorithm guarantees that this is the shortest possible path between the start and end points in the maze.


(Additonal Information)
## C++ Implementation Details
### Class Structure
- **mazeGraph**: The main class that encapsulates the graph representation of the maze
  - Contains a nested **Vertex** class representing nodes in the graph
  - Provides methods for graph construction and manipulation

### Key Data Structures
- **unordered_map<string, Vertex*> vertexMap**: Maps coordinate strings (e.g., "1,2") to Vertex pointers
- **vector<Vertex*> neighs**: Each Vertex contains a vector of pointers to its neighbors
- **queue<Vertex*>**: Used for BFS traversal
- **unordered_set<Vertex*>**: Tracks visited vertices during BFS
- **unordered_map<Vertex*, Vertex*> parent**: Maps vertices to their parent in the BFS path

### Memory Management
- Dynamic memory allocation is used for Vertex objects
- Proper cleanup is implemented in the mazeGraph destructor and during graph rebuilding
- Vertices are allocated with `new` and properly deleted when no longer needed

### Algorithm Implementation
- Graph construction from the maze string is performed in O(n) time where n is the length of the input
- The BFS algorithm runs in O(V+E) time where V is the number of vertices and E is the number of edges
- String parsing and manipulation is used to extract coordinates and build the graph

### Interface
- A global `solve(string maze)` function provides a simple interface to the solver
- This function creates a mazeGraph instance internally and delegates to its solve method
- The returned string represents the maze with 'o' characters marking the shortest path

