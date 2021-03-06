#pragma once

#include "map.h"
#include "ds_template.h"
#include <vector>
#include <stack>
#include <queue>
#include <set>

using namespace std;


class Algorithm
{
public:
	Map* map;
	unsigned int nodes = 0;

	virtual void MoveToTarget() = 0;
	virtual bool FindPath() = 0;

	bool ReachTarget();
	bool ReachTarget(Coordinate);
	bool ReachTarget(Node);
	Algorithm(Map*);
};

class MultiAgent {
	vector<Coordinate> agents;
};

class NonRealTime : public Algorithm {
public:
	stack<Coordinate> route;

	NonRealTime(Map *map) : Algorithm(map) {}

	void MoveToTarget();
	bool GenerateRoute();
};

class RealTime : public Algorithm {
	Coordinate next_dir;
};

//depth first search
class DFS : public NonRealTime {
public:
	bool FindPath();
	DFS(Map *map) : NonRealTime(map) {}
};


//iterative deepening search
class IDS : public NonRealTime {
public:
	bool FindPath();

	bool DLS(Node *node_ptr, int limit);
	bool IDDFS(int max_depth);
	IDS(Map *map) : NonRealTime(map) {}
};

//breadth first search
class BFS : public NonRealTime {
public:
	unique_queue<Node*> queue;

	bool FindPath();

	BFS(Map *map) :NonRealTime(map) {}
};

class Dijkstra : public NonRealTime {
public:
	unique_priority_queue<Node*, Node> queue;
	bool FindPath();

	Dijkstra(Map *map) : NonRealTime(map) {}
};


class BestFirst : public NonRealTime {
public:
	unique_priority_queue<Node*, Node> queue;
	bool FindPath();

	BestFirst(Map *map) : NonRealTime(map) {}
};

class Astar : public NonRealTime {
public:
	unique_priority_queue<Node*, Node> queue;

	bool FindPath();

	Astar(Map *map) : NonRealTime(map) {}
};

//depth direction astar
class DDAstar : public Astar {
public:
	bool FindPath();
	void MoveToTarget();
	DDAstar(Map *map) : Astar(map) {}
};

//improved astar
class IAstar : public Astar {
public :
	bool FindPath();

	IAstar(Map *map) : Astar(map) {}
};

