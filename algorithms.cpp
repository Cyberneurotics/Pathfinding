#include "pch.h"
#include "map.h"
#include "algorithms.h"
#include <time.h>
#include <math.h>
#include <climits>

inline void PrintCo(Coordinate co) {
	cout << "(" << co.x << ", " << co.y << ")" << endl;
}

bool Algorithm::ReachTarget()
{
	return map->agent.x == map->target.x && map->agent.y == map->target.y;
}

bool Algorithm::ReachTarget(Coordinate co)
{
	return co.x == map->target.x && co.y == map->target.y;
}

bool Algorithm::ReachTarget(Node node)
{
	return ReachTarget(node.co);
}



Algorithm::Algorithm(Map* map)
	:map(map)
{
}

void NonRealTime::MoveToTarget()
{
	if (route.empty())
		if (!FindPath()) {
			cout << "failed to find path" << endl;
			return;
		}

	while (!ReachTarget())
	{
		map->agent = route.top();
		route.pop();
		map->DisplayMap();
	}
}

bool NonRealTime::GenerateRoute()
{
	auto p = map->matrix[map->target.x][map->target.y].parent;
	if (!p) {
		return false;
	}

	route.push(map->target);
	while (p) {
		route.push(p->co);
		p = p->parent;
	}
	return true;
}


bool DFS::FindPath()
{
	clock_t clk = clock();

	stack<Node*> stk;

	Node start = map->matrix[map->agent.x][map->agent.y];
	stk.push(&start);
	while (!stk.empty()) {
		auto node_ptr = stk.top();
		stk.pop();

		if (ReachTarget(*node_ptr)) {
			break;
		}

		if (!node_ptr->visited) {
			node_ptr->visited = true;
		}

		Coordinate adjs[] = {
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y},
			Coordinate{node_ptr->co.x , node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x , node_ptr->co.y - 1},
		};

		for (auto adj : adjs) {
			if (map->IsPassable(adj)) {
				Node *adj_node = &map->matrix[adj.x][adj.y];
				if (!adj_node->visited) {
					stk.push(adj_node);
					adj_node->parent = node_ptr;
				}
			}
		}

		if (stk.size() > nodes) {
			nodes = stk.size();
		}
	}


	if (!GenerateRoute()) {
		cout << "no path found!" << endl;
		return false;
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;

	return true;
}

bool IDS::FindPath()
{
	clock_t clk = clock();

	bool found = IDDFS(100);
	if (!found) {
		cout << "no path found" << endl;
		return false;
	}

	auto p = map->matrix[map->target.x][map->target.y].parent;

	//PrintCo(map->target);
	route.push(map->target);
	while (!ReachTarget(*p)) {
		//PrintCo(p);
		route.push(p->co);
		p = p->parent;
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;
	return true;
}

bool IDS::DLS(Node node, int limit)
{
	if (ReachTarget(node))
		return true;

	if (!node.visited) {
		node.visited = true;
	}
	// If reached the maximum depth, stop recursing. 
	if (limit <= 0)
		return false;

	// Recur for all the vertices adjacent to source vertex 
	Node adjs[] = {
			map->matrix[node.co.x + 1][node.co.y],
			map->matrix[node.co.x - 1][node.co.y],
			map->matrix[node.co.x][node.co.y + 1],
			map->matrix[node.co.x][node.co.y - 1],
	};

	for (auto adj : adjs) {
		if (adj.passable && !adj.visited) {
			adj.parent = &node;
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

		nodes = 0;
		if (DLS(map->matrix[map->agent.x][map->agent.y], i) == true)
			return true;
	}
	return false;
}

bool BFS::FindPath()
{
	clock_t clk = clock();

	queue.push(map->matrix[map->agent.x][map->agent.y]);
	while (!queue.empty()) {
		auto node = queue.front();
		queue.pop();

		if (ReachTarget(node)) {
			break;
		}

		if (!node.visited) {
			node.visited = true;
		}

		Node adjs[] = {
			map->matrix[node.co.x + 1][node.co.y],
			map->matrix[node.co.x - 1][node.co.y],
			map->matrix[node.co.x][node.co.y + 1],
			map->matrix[node.co.x][node.co.y - 1],
		};
		for (auto adj : adjs) {
			if (adj.passable && !adj.visited) {
				queue.push(adj);
				adj.parent = &node;
			}
		}

		if (queue.size() > nodes)
			nodes = queue.size();
	}

	if (!GenerateRoute()) {
		cout << "no path found!" << endl;
		return false;
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;
	return true;
}

bool Dijkstra::FindPath()
{
	clock_t clk = clock();

	queue.push(map->matrix[map->agent.x][map->agent.y]);
	map->matrix[map->agent.x][map->agent.y].weight = 0;
	while (!queue.empty()) {
		auto node = queue.top();
		queue.pop();

		if (ReachTarget(node))
			break;

		if (!node.visited) {
			node.visited = true;
		}

		Node adjs[] = {
			map->matrix[node.co.x + 1][node.co.y],
			map->matrix[node.co.x - 1][node.co.y],
			map->matrix[node.co.x][node.co.y + 1],
			map->matrix[node.co.x][node.co.y - 1],
		};
		for (auto adj : adjs) {
			if (adj.passable && !adj.visited && adj.weight > node.weight + 1) {
				adj.weight = node.weight + 1;
				queue.push(adj);
				adj.parent = &node;
			}
		}

		if (queue.size() > nodes)
			nodes = queue.size();
	}

	if (!GenerateRoute()) {
		cout << "no path found!" << endl;
		return false;
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;
	return true;
}
