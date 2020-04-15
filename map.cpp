#include "pch.h"
#include "map.h"
#include <limits>

Map::Map()
{
}

Map::Map(int w, int h, int** map, Coordinate agent, Coordinate target)
	:width(w), height(h)
{
	matrix.resize(width);
	for (auto &node : matrix) {
		node.resize(height);
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			matrix[i][j] = Node{ Coordinate{i,j} , (bool)map[i][j], NULL, false, std::numeric_limits<double>::max(), std::numeric_limits<double>::max() };
		}
	}

	this->agent = agent;
	this->target = target;
}


Map::~Map()
{
}


bool Map::IsValid(int x, int y) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

bool Map::IsPassable(int x, int y)
{
	return IsValid(x, y) && matrix[x][y].passable;
}

bool Map::IsPassable(Coordinate co)
{
	return IsPassable(co.x, co.y);
}

void Map::DisplayMap()
{
	std::cout << "©°";
	for (int i = 0; i < height-1; i++) {
		std::cout << "©¤©¤©Ð";
	}
	std::cout << "©¤©¤©´" << std::endl;

	for (int i = 0; i < width; i++) {
		std::cout << "©¦";
		for (int j = 0; j < height; j++) {
			std::cout << " ";
			if (i == agent.x && j == agent.y) {
				std::cout << "A";
			}
			else if (i == target.x && j == target.y) {
				std::cout << "D";
			}
			else if (!matrix[i][j].passable) {
				std::cout << "+";
			}
			else {
				std::cout << " ";
			}
			std::cout << "©¦";
		}
		//std::cout << "  ©¦" << std::endl;
		std::cout << std::endl;
		if (i != width - 1) {
			std::cout << "©À";
			for (int j = 0; j < height-1; j++) {
				std::cout << "©¤©¤©à";
			}
			std::cout << "©¤©¤©È" << std::endl;
		}
		else {
			std::cout << "©¸";
			for (int i = 0; i < height-1; i++) {
				std::cout << "©¤©¤©Ø";
			}
			std::cout << "©¤©¤©¼" << std::endl;
		}
	}

	std::cout << std::endl;
}
