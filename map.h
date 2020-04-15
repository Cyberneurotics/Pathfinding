#pragma once
#include <iostream>
#include <vector>

struct Coordinate {
	int x;
	int y;

	Coordinate() {};
	Coordinate(int x, int y) :x(x), y(y) {};
};

struct Node {
	Coordinate co;
	bool passable;	
	Node* parent;
	bool visited;
	double f, g;

	friend bool operator<(Node a, Node b) {
		return a.f > b.f;
	}
};


class Map
{
public:
	int width, height;
	std::vector<std::vector<Node>> matrix;
	Coordinate agent, target;


	Map();
	Map(int width, int height, int** map, Coordinate agent, Coordinate co);
	~Map();

	bool IsValid(int x, int y);
	bool IsPassable(int x, int y);
	bool IsPassable(Coordinate);
	void DisplayMap();
	
};


