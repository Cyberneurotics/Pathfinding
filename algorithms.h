#pragma once

#include "Agent.h"
#include "map.h"
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Algorithm
{
public:
	Map* map;
	int nodes = 0;
	
	virtual void MoveToTarget() = 0;
	virtual bool FindPath() = 0;

	bool ReachTarget();
	bool ReachTarget(Coordinate);
	Algorithm(Map*);
};

class MultiAgent {
	vector<Agent> agents;
};

class NonRealTime : public Algorithm {
public:
	stack<Coordinate> route;
	vector<vector<Coordinate>> parent_map;
	NonRealTime(Map *map) : Algorithm(map) {
		parent_map.resize(map->width);
		for (int i = 0; i < map->width; i++) {
			parent_map[i].resize(map->height);
			fill(parent_map[i].begin(), parent_map[i].end(), Coordinate{ -1, -1 });
		}
	}

	void MoveToTarget();
};

class RealTime : public Algorithm {
	Agent::directions next_dir;
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
	vector<vector<bool>> visited;

	bool FindPath();

	bool DLS(Coordinate src,  int limit);
	bool IDDFS(int max_depth);
	IDS(Map *map) : NonRealTime(map) {}
};

//breadth first search
class BFS : public NonRealTime {
public:
	queue<Coordinate> queue;

	bool FindPath();

	BFS(Map *map) :NonRealTime(map) {}
};



