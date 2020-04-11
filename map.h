#pragma once
#include <iostream>
#include "Agent.h"

struct Coordinate {
	int x;
	int y;

	Coordinate() {};
	Coordinate(int x, int y) :x(x), y(y) {};
};


class Map
{
public:
	int width, height;
	int** matrix;
	Agent* agent;
	Coordinate target;

	Map();
	Map(int width, int height, int** map, Agent*, Coordinate co);
	~Map();

	bool IsValid(int x, int y);
	bool IsPassable(int x, int y);
	bool IsPassable(Coordinate);
	void DisplayMap();
	
};


