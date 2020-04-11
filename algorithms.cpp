#include "pch.h"
#include "map.h"
#include "algorithms.h"
#include <time.h>
#include <math.h>

inline void PrintCo(Coordinate co) {
	cout << "(" << co.x << ", " << co.y << ")" << endl;
}


Algorithm::Algorithm(Map* map)
	:map(map)
{
}


void DFS::FindPath()
{
	clock_t clk = clock();
	int nodes = 0;

	stack<Coordinate> stk;
	vector<vector<bool>> visited(map->width, vector<bool>(map->height));
	vector<vector<Coordinate>> parent(map->width, vector<Coordinate>(map->height, Coordinate{ -1, -1 }));

	Coordinate start = { map->agent->GetX(), map->agent->GetY() };
	stk.push(start);
	while (!stk.empty()) {
		auto node = stk.top();
		stk.pop();

		if (node.x == map->target.x && node.y == map->target.y) {
			break;
		}
		if (!visited[node.x][node.y]) {
			visited[node.x][node.y] = true;
		}


		if (map->IsPassable(Coordinate(node.x + 1, node.y)) && !visited[node.x + 1][node.y]) {
			stk.push(Coordinate(node.x + 1, node.y));
			parent[node.x + 1][node.y] = node;
			nodes++;
		}
		if (map->IsPassable(Coordinate(node.x - 1, node.y)) && !visited[node.x - 1][node.y]) {
			stk.push(Coordinate(node.x - 1, node.y));
			parent[node.x - 1][node.y] = node;
			nodes++;
		}
		if (map->IsPassable(Coordinate(node.x, node.y + 1)) && !visited[node.x][node.y + 1]) {
			stk.push(Coordinate(node.x, node.y + 1));
			parent[node.x][node.y + 1] = node;
			nodes++;
		}
		if (map->IsPassable(Coordinate(node.x, node.y - 1)) && !visited[node.x][node.y - 1]) {
			stk.push(Coordinate(node.x, node.y - 1));
			parent[node.x][node.y - 1] = node;
			nodes++;
		}
	}

	auto p = parent[map->target.x][map->target.y];
	if (p.x == -1) {
		cout << "no path found" << endl;
		return;
	}



	//PrintCo(map->target);
	route.push(map->target);
	while (!(p.x == map->agent->GetX() && p.y == map->agent->GetY())) {
		//PrintCo(p);
		route.push(p);
		p = parent[p.x][p.y];
	}
	
	cout << "Search time: " <<(clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" <<endl;
	cout << "Nodes expanded: " << nodes << endl;
}

void DFS::MoveToTarget()
{
	if (route.empty())
		FindPath();
	if (route.empty()) {
		cout << "failed to find path" << endl;
		return;
	}
	while (!(map->agent->GetX() == map->target.x  && map->agent->GetY() == map->target.y))
	{
		map->agent->MoveAgent(route.top());
		route.pop();
		map->DisplayMap();
	}
}

void IDA::FindPath()
{
	clock_t clk = clock();
	int nodes = 0;

	int depth = 1;
	stack<Coordinate> stk;
loop:
	vector<vector<bool>> visited(map->width, vector<bool>(map->height));
	vector<vector<Coordinate>> parent(map->width, vector<Coordinate>(map->height, Coordinate{ -1, -1 }));

	Coordinate start = { map->agent->GetX(), map->agent->GetY() };	
	stk.push(start);
	while (!stk.empty()) {
		auto node = stk.top();
		stk.pop();

		if (node.x == map->target.x && node.y == map->target.y) {
			goto finish;
		}
		if (abs(node.x - start.x) + abs(node.y - start.y) > depth)
			continue;

		if (!visited[node.x][node.y]) {
			visited[node.x][node.y] = true;
		}


		if (map->IsPassable(Coordinate(node.x + 1, node.y)) && !visited[node.x + 1][node.y]) {
			stk.push(Coordinate(node.x + 1, node.y));
			parent[node.x + 1][node.y] = node;
			nodes++;
		}
		if (map->IsPassable(Coordinate(node.x - 1, node.y)) && !visited[node.x - 1][node.y]) {
			stk.push(Coordinate(node.x - 1, node.y));
			parent[node.x - 1][node.y] = node;
			nodes++;
		}
		if (map->IsPassable(Coordinate(node.x, node.y + 1)) && !visited[node.x][node.y + 1]) {
			stk.push(Coordinate(node.x, node.y + 1));
			parent[node.x][node.y + 1] = node;
			nodes++;
		}
		if (map->IsPassable(Coordinate(node.x, node.y - 1)) && !visited[node.x][node.y - 1]) {
			stk.push(Coordinate(node.x, node.y - 1));
			parent[node.x][node.y - 1] = node;
			nodes++;
		}
	}

	depth++;
	if (depth > map->height + map->width)
		goto finish;
	goto loop;


	finish:
	auto p = parent[map->target.x][map->target.y];
	if (p.x == -1) {
		cout << "no path found" << endl;
		return;
	}



	//PrintCo(map->target);
	route.push(map->target);
	while (!(p.x == map->agent->GetX() && p.y == map->agent->GetY())) {
		//PrintCo(p);
		route.push(p);
		p = parent[p.x][p.y];
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;
}

void IDA::MoveToTarget()
{
	if (route.empty())
		FindPath();
	if (route.empty()) {
		cout << "failed to find path" << endl;
		return;
	}
	while (!(map->agent->GetX() == map->target.x  && map->agent->GetY() == map->target.y))
	{
		map->agent->MoveAgent(route.top());
		route.pop();
		map->DisplayMap();
	}
}
