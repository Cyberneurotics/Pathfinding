// Pathfinding.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "algorithms.h"

int **m1 = new int*[4]{
		new int[4]{1, 1, 1, 1},
		new int[4]{1, 0, 0, 1},
		new int[4]{1, 1, 1, 0},
		new int[4]{0, 0, 1, 1}
};
Map *map1 = new Map(4, 4, m1, new Agent(0, 0), Coordinate(3, 3));

int **m2 = new int*[8]{
	new int[8]{1,1,0,1,1,0,1,1},
	new int[8]{1,1,0,1,1,0,1,1},
	new int[8]{1,0,0,1,1,1,1,1},
	new int[8]{1,1,1,1,1,0,1,1},
	new int[8]{0,1,0,1,1,0,1,1},
	new int[8]{1,1,0,1,0,1,1,1},
	new int[8]{1,1,0,1,1,0,1,1},
	new int[8]{1,1,0,0,1,1,1,1},
};
Map* map2 = new Map(8, 8, m2, new Agent(0, 0), Coordinate(7,7));


int **m3 = new int*[16]{
	new int[16]{1,1,0,0,1,0,1,1,1,1,0,1,1,0,1,1},
	new int[16]{1,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1},
	new int[16]{0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
	new int[16]{1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,0},
	new int[16]{0,1,0,0,1,0,1,1,0,1,0,1,1,0,1,1},
	new int[16]{1,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1},
	new int[16]{1,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1},
	new int[16]{1,1,0,1,1,0,1,1,0,1,0,0,1,1,1,1},
	new int[16]{1,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1},
	new int[16]{0,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0},
	new int[16]{1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1},
	new int[16]{1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,1},
	new int[16]{0,0,1,1,1,1,1,0,0,1,0,1,1,0,0,1},
	new int[16]{1,1,1,1,1,0,1,1,1,1,0,1,1,0,0,1},
	new int[16]{1,1,0,0,1,0,1,1,1,1,0,1,1,0,1,1},
	new int[16]{1,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1},

};
Map* map3 = new Map(16, 16, m3, new Agent(0, 0), Coordinate(5, 4));

Algorithm * algo;

void initialize(Map* map) {
	algo = new DFS(map);

	map->DisplayMap();
}

void free() {
	
}

int main()
{
	initialize(map3);
	algo->MoveToTarget();
	delete map2;
	return 0;
}

