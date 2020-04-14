﻿// Pathfinding.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
Map *map1 = new Map(4, 4, m1, Coordinate(0, 0), Coordinate(3, 3));

int **m2 = new int*[8]{
	new int[8]{1,1,1,1,1,0,1,1},
	new int[8]{1,1,0,1,1,0,1,1},
	new int[8]{1,0,0,1,1,1,1,1},
	new int[8]{1,1,1,1,1,0,1,1},
	new int[8]{0,1,0,1,1,0,1,1},
	new int[8]{1,1,0,1,0,1,1,1},
	new int[8]{1,1,0,1,1,0,1,1},
	new int[8]{1,1,0,0,1,1,1,1},
};
Map* map2 = new Map(8, 8, m2, Coordinate(0, 0), Coordinate(3, 3));


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
Map* map3 = new Map(16, 16, m3, Coordinate(0, 0), Coordinate(15, 15));

int **m4 = new int*[16]{

	new int[16]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[16]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[16]{1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1},
	new int[16]{1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1},	
	new int[16]{1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
	new int[16]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[16]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[16]{1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},	
	new int[16]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[16]{1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1},
	new int[16]{1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1},
	new int[16]{1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1},	
	new int[16]{1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1},
	new int[16]{1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1},
	new int[16]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[16]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},


};
Map* map4 = new Map(16, 16, m4, Coordinate(8, 8), Coordinate(15, 15));

int **m5 = new int*[32]{
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},
	new int[32]{1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},
	new int[32]{1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
	new int[32]{1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
	new int[32]{1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1},
	new int[32]{1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	new int[32]{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

Map* map5 = new Map(32, 32, m5, Coordinate(16, 16), Coordinate(0, 0));

Algorithm * algo;

int main()
{
	algo = new Astar(map4);
	algo->MoveToTarget();
	delete map3;
	getchar();
	return 0;
}

