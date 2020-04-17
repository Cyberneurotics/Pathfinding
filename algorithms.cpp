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

		if (node_ptr->visited) {
			continue;
		}
		node_ptr->visited = true;

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


	if (!p) {
		return false;
	}

	if (!GenerateRoute()) {
		cout << "no path found!" << endl;
		return false;
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;
	return true;
}

bool IDS::DLS(Node *node_ptr, int limit)
{
	if (ReachTarget(*node_ptr))
		return true;

	if (node_ptr->visited) {
		return false;
	}
	node_ptr->visited = true;

	if (limit <= 0)
		return false;

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
				nodes++;
				adj_node->parent = node_ptr;

				if (DLS(&map->matrix[adj.x][adj.y], limit - 1) == true)
					return true;
			}
		}
	}

	return false;
}

bool IDS::IDDFS(int max_depth)
{
	for (int i = 0; i <= max_depth; i++) {
		nodes = 0;
		for (auto &row : map->matrix) {
			for (auto &node : row) {
				node.visited = false;
			}
		}
		if (DLS(&map->matrix[map->agent.x][map->agent.y], i) == true)
			return true;
	}
	return false;
}

bool BFS::FindPath()
{
	clock_t clk = clock();

	Node* start = &map->matrix[map->agent.x][map->agent.y];
	queue.push(start);
	while (!queue.empty()) {
		auto node_ptr = queue.front();
		queue.pop();

		if (ReachTarget(*node_ptr)) {
			break;
		}

		if (node_ptr->visited) {
			continue;
		}
		node_ptr->visited = true;

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
					queue.push(adj_node);
					adj_node->parent = node_ptr;
				}
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

	Node* start = &map->matrix[map->agent.x][map->agent.y];
	queue.push(start);
	start->f = 0;
	while (!queue.empty()) {
		auto node_ptr = queue.top();
		queue.pop();

		if (ReachTarget(*node_ptr))
			break;

		if (node_ptr->visited) {
			continue;
		}
		node_ptr->visited = true;

		Coordinate adjs[] = {
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y},
			Coordinate{node_ptr->co.x , node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x , node_ptr->co.y - 1},
		};

		for (auto adj : adjs) {
			if (map->IsPassable(adj)) {
				Node *adj_node = &map->matrix[adj.x][adj.y];
				if (!adj_node->visited && adj_node->g > node_ptr->g+1) {
					adj_node->f = node_ptr->f + 1;
					queue.push(adj_node);
					adj_node->parent = node_ptr;
				}
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

inline int Manhattan(Coordinate a, Coordinate b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool BestFirst::FindPath()
{
	clock_t clk = clock();

	Node* start = &map->matrix[map->agent.x][map->agent.y];
	start->f = Manhattan(start->co, map->target);
	queue.push(start);
	
	while (!queue.empty()) {
		auto node_ptr = queue.top();
		queue.pop();

		if (ReachTarget(*node_ptr))
			break;

		if (node_ptr->visited) {
			continue;
		}
		node_ptr->visited = true;

		Coordinate adjs[] = {
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y},
			Coordinate{node_ptr->co.x , node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x , node_ptr->co.y - 1},
		};

		for (auto adj : adjs) {
			if (map->IsPassable(adj)) {
				Node *adj_node = &map->matrix[adj.x][adj.y];
				adj_node->f = Manhattan(adj_node->co, map->target);
				if (!adj_node->visited) {
					queue.push(adj_node);
					adj_node->parent = node_ptr;
				}
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

bool Astar::FindPath()
{
	clock_t clk = clock();

	Node* start = &map->matrix[map->agent.x][map->agent.y];
	start->f = Manhattan(start->co, map->target);
	start->g = 0;
	queue.push(start);

	while (!queue.empty()) {
		auto node_ptr = queue.top();
		queue.pop();

		if (ReachTarget(*node_ptr))
			break;

		if (node_ptr->visited) {
			continue;
		}
		node_ptr->visited = true;

		Coordinate adjs[] = {
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y},
			Coordinate{node_ptr->co.x , node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x , node_ptr->co.y - 1},

			Coordinate{node_ptr->co.x + 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y - 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y - 1}
		};

		for (auto adj : adjs) {
			if (map->IsPassable(adj)) {
				Node *adj_node = &map->matrix[adj.x][adj.y];
				if (!adj_node->visited) {
					double weight = abs(adj_node->co.x - node_ptr->co.x) + abs(adj_node->co.y - node_ptr->co.y) == 1 ? 1 : 1.4;
					if (adj_node->g > node_ptr->g + weight) {
						adj_node->g = node_ptr->g + weight;
					}
					adj_node->f = adj_node->g + Euclidean(adj_node->co, map->target);
					adj_node->parent = node_ptr;
					queue.push(adj_node);				
				}
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

bool DDAstar::FindPath()
{
	clock_t clk = clock();

	double m = (map->agent.y - map->target.y) / (map->agent.x - map->target.x);

	bool astar = false;

	Node* start = &map->matrix[map->agent.x][map->agent.y];
	start->f = Euclidean(start->co, map->target);
	start->g = 0;
	start->visited = true;
	queue.push(start);

	while (!queue.empty()) {
		auto node_ptr = queue.top();
		queue.pop();

		cout << node_ptr->co.x << "," << node_ptr->co.y << endl;
		if (ReachTarget(*node_ptr))
			break;

		if (node_ptr->visited) {
			continue;
		}
		node_ptr->visited = true;


		if (!astar) {

		}
		else {

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
						if (adj_node->g > node_ptr->g + 1) {
							adj_node->g = node_ptr->g + 1;
						}
						adj_node->f = adj_node->g + Manhattan(adj_node->co, map->target);
						adj_node->parent = node_ptr;
						queue.push(adj_node);
					}
				}
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
