#include "pch.h"
#include "map.h"
#include "algorithms.h"
#include <time.h>
#include <math.h>

inline void PrintCo(Coordinate co) {
	cout << "(" << co.x << ", " << co.y << ")" << endl;
}


bool Algorithm::ReachTarget()
{
	return map->agent->GetX() == map->target.x && map->agent->GetY() == map->target.y;
}

bool Algorithm::ReachTarget(Coordinate co)
{
	return co.x == map->target.x && co.y == map->target.y;
}


Algorithm::Algorithm(Map* map)
	:map(map)
{
}


bool DFS::FindPath()
{
	clock_t clk = clock();

	stack<Coordinate> stk;
	vector<vector<bool>> visited(map->width, vector<bool>(map->height));

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

		Coordinate adjs[] = {
			Coordinate{node.x + 1, node.y},
			Coordinate{node.x - 1, node.y},
			Coordinate{node.x, node.y + 1},
			Coordinate{node.x, node.y - 1}
		};

		for (auto adj : adjs) {
			if (map->IsPassable(adj) && !visited[adj.x][adj.y]) {
				stk.push(adj);
				parent_map[adj.x][adj.y] = node;
			}
		}

		if (stk.size() > nodes) {
			nodes = stk.size();
		}
	}

	auto p = parent_map[map->target.x][map->target.y];
	if (p.x == -1) {
		cout << "no path found" << endl;
		return false;
	}



	//PrintCo(map->target);
	route.push(map->target);
	while (!(p.x == map->agent->GetX() && p.y == map->agent->GetY())) {
		//PrintCo(p);
		route.push(p);
		p = parent_map[p.x][p.y];
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;

	return true;
}

void DFS::MoveToTarget()
{
	if (route.empty())
		if (!FindPath()) {
			cout << "failed to find path" << endl;
			return;
		}

	map->DisplayMap();
	while (!(map->agent->GetX() == map->target.x  && map->agent->GetY() == map->target.y))
	{
		map->agent->MoveAgent(route.top());
		route.pop();
		map->DisplayMap();
	}
}

bool IDS::FindPath()
{
	clock_t clk = clock();

	bool found = IDDFS(map->height + map->width);
	if (!found) {
		cout << "no path found" << endl;
		return false;
	}

	auto p = parent_map[map->target.x][map->target.y];

	//PrintCo(map->target);
	route.push(map->target);
	while (!(p.x == map->agent->GetX() && p.y == map->agent->GetY())) {
		//PrintCo(p);
		route.push(p);
		p = parent_map[p.x][p.y];
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;
	return true;
}

void IDS::MoveToTarget()
{
	if (route.empty())
		if (!FindPath()) {
			cout << "failed to find path" << endl;
			return;
		}

	map->DisplayMap();
	while (!(map->agent->GetX() == map->target.x  && map->agent->GetY() == map->target.y))
	{
		map->agent->MoveAgent(route.top());
		route.pop();
		map->DisplayMap();
	}
}

bool IDS::DLS(Coordinate src, int limit)
{
	if (ReachTarget(src))
		return true;

	if (!visited[src.x][src.y]) {
		visited[src.x][src.y] = true;
	}
	// If reached the maximum depth, stop recursing. 
	if (limit <= 0)
		return false;

	// Recur for all the vertices adjacent to source vertex 

	Coordinate adjs[] = {
		Coordinate{src.x + 1, src.y},
		Coordinate{src.x - 1,src.y},
		Coordinate{src.x, src.y + 1},
		Coordinate{src.x, src.y - 1}
	};
	for (auto adj : adjs) {
		if (map->IsPassable(adj) && !visited[adj.x][adj.y]) {
			parent_map[adj.x][adj.y] = src;
			nodes++;
			if (DLS(adj, limit - 1) == true)
				return true;
		}
	}

	return false;
}

bool IDS::IDDFS(int max_depth)
{
	for (int i = 0; i <= max_depth; i++) {
		visited.resize(i+1);
		for (int j = 0; j < i + 1; j++) {
			visited[j].resize(i + 1);
			fill(visited[j].begin(), visited[j].end(), false);
		}
		
		nodes = 0;
		if (DLS(Coordinate{ map->agent->GetX(), map->agent->GetY() },  i) == true)
			return true;
	}
	return false;
}
