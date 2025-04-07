#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class directedGraph
{
private:
	class vertex
	{
	public:
		string data;
		vector<vertex*> neighbors;

		vertex(string x)
		{
			data = x;
		}
	};

	unordered_map<string, vertex*> vertexMap;

	void breadthFirstSearch(vertex* s, unordered_map<vertex*, vertex*>& bc)
	{
		//setup:
		queue<vertex*> Q;
		unordered_set<vertex*> marked;

		//step 0: mark s, put s into Q
		marked.insert(s);
		Q.push(s);

		//step 1: bfs loop
		while (!Q.empty())
		{
			//step 1.1: get item from Q
			vertex* x = Q.front();
			Q.pop();

			//step 1.2: visit x's unmarked neighs
			for (auto y : x->neighbors)
			{
				if (marked.find(y) == marked.end())
				{
					marked.insert(y);
					Q.push(y);

					//augmentation: set breadcrumb
					bc[y] = x;
				}
			}
		}
	}

	string traceBreadCrumbs(vertex* s, vertex* d, unordered_map<vertex*, vertex*>& bc)
	{
		vertex* current = d;
		string path;

		while (current != s)
		{
			path = current->data + ", " + path;
			current = bc[current];
		}
		path = current->data + ", " + path;
		return path;
	}

public:

	void addVertex(string x)
	{
		vertexMap[x] = new vertex(x);
	}


	void addDirectedEdge(string x, string y)
	{
		vertex* xVert = vertexMap[x];
		vertex* yVert = vertexMap[y];

		xVert->neighbors.push_back(yVert);
	}

	void addBasicEdge(string x, string y)
	{
		addDirectedEdge(x, y);
		addDirectedEdge(y, x);
	}

	string shortestPath(string start, string dest)
	{
		//step 0: get vertices of start and dest
		vertex* sVert = vertexMap[start];
		vertex* dVert = vertexMap[dest];

		//step 1: create a breadcrumb map
		unordered_map<vertex*, vertex*> breadCrumbs;

		//step 2:
		breadthFirstSearch(sVert,breadCrumbs);

		//step 3: follow breadcrumb trail from
		//dest back to start to get shortest path
		string path;
		path = traceBreadCrumbs(sVert, dVert, breadCrumbs);

		return path;
	}

};

