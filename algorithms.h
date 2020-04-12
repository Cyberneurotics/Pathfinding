#pragma once

#include "Agent.h"
#include "map.h"
#include <vector>
#include <stack>

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
};

class RealTime : public Algorithm {
	Agent::directions next_dir;
};

//depth first search
class DFS : public NonRealTime {
public:
	bool FindPath();
	void MoveToTarget();
	DFS(Map *map) : NonRealTime(map) {}
};


//iterative deepening search
class IDS : public NonRealTime {
public:
	vector<vector<bool>> visited;

	bool FindPath();
	void MoveToTarget();

	bool DLS(Coordinate src,  int limit);
	bool IDDFS(int max_depth);
	IDS(Map *map) : NonRealTime(map) {}
};



