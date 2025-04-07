
#include <iostream>
#include <string>
#include "directedGraph.h"
using namespace std;

int main()
{
	directedGraph G;

	G.addVertex("A");
	G.addVertex("B");
	G.addVertex("C");
	G.addVertex("D");
	G.addVertex("E");
	G.addVertex("F");
	G.addVertex("G");

	G.addBasicEdge("A", "B");
	G.addBasicEdge("A", "C");
	G.addBasicEdge("A", "D");
	G.addBasicEdge("B", "E");
	G.addBasicEdge("C", "D");
	G.addBasicEdge("D", "F");
	G.addBasicEdge("E", "F");
	G.addBasicEdge("E", "G");
	G.addBasicEdge("F", "G");
	

	cout << "A to G: " << G.shortestPath("A", "G") << endl;
	cout << "E to D: " << G.shortestPath("E", "D") << endl;
	cout << "F to B: " << G.shortestPath("F", "B") << endl;
	cout << "A to E: " << G.shortestPath("A", "E") << endl;
	cout << "C to G: " << G.shortestPath("C", "G") << endl;
	return 0;
}

