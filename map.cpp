#include "pch.h"
#include "map.h"


Map::Map()
{
}

Map::Map(int w, int h, int** map, Agent* agent, Coordinate co)
	:width(w), height(h), matrix(map), agent(agent), target(co)
{

}


Map::~Map()
{
	if (matrix) {
		for (int i = 0; i < width; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
}


bool Map::IsValid(int x, int y) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

bool Map::IsPassable(int x, int y)
{
	return IsValid(x, y) && matrix[x][y];
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
			if (i == agent->GetX() && j == agent->GetY()) {
				std::cout << "A";
			}
			else if (i == target.x && j == target.y) {
				std::cout << "D";
			}
			else if (!matrix[i][j]) {
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
