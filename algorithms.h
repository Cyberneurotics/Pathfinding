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

	virtual void MoveToTarget() = 0;
	virtual void FindPath() = 0;

	Algorithm(Map*);
};

class MultiAgent {
	vector<Agent> agents;
};

class NonRealTime : public Algorithm {
public:
	stack<Coordinate> route;

	NonRealTime(Map *map) : Algorithm(map) {}
};

class RealTime : public Algorithm {
	Agent::directions next_dir;
};

class DFS : public NonRealTime {

public:
	void FindPath();
	void MoveToTarget();
	DFS(Map *map) : NonRealTime(map) {}
};

class IDA : public NonRealTime {

public:
	void FindPath();
	void MoveToTarget();
	IDA(Map *map) : NonRealTime(map) {}
};



