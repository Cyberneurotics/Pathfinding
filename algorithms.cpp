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

	int length = 0;
	//cout << "Path length: " << route.size() << endl;
	while (!ReachTarget())
	{
		length += abs(map->agent.x - route.top().x) + abs(map->agent.y - route.top().y) == 1 ? 10 : 14;
		map->agent = route.top();
		route.pop();
		map->DisplayMap();
	}

	cout << "Path length: " << length / 10 << endl;
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

	unique_stack<Node*> stk;

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

			Coordinate{node_ptr->co.x + 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y - 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y - 1}
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

	bool found = IDDFS(INT_MAX);
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

			Coordinate{node_ptr->co.x + 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y - 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y - 1}
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

			Coordinate{node_ptr->co.x + 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y - 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y - 1}
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

			Coordinate{node_ptr->co.x + 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y - 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y - 1}
		};

		for (auto adj : adjs) {
			if (map->IsPassable(adj)) {
				Node *adj_node = &map->matrix[adj.x][adj.y];
				int weight = abs(adj_node->co.x - node_ptr->co.x) + abs(adj_node->co.y - node_ptr->co.y) == 1 ? 10 : 14;
				if (!adj_node->visited && adj_node->f > node_ptr->f + weight) {
					adj_node->f= node_ptr->f + weight;
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
	return (abs(a.x - b.x) + abs(a.y - b.y)) * 10;
}

inline double Euclidean(Coordinate a, Coordinate b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
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

			Coordinate{node_ptr->co.x + 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x + 1, node_ptr->co.y - 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y + 1},
			Coordinate{node_ptr->co.x - 1, node_ptr->co.y - 1}
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
					int weight = abs(adj_node->co.x - node_ptr->co.x) + abs(adj_node->co.y - node_ptr->co.y) == 1 ? 10 : 14;
					if (adj_node->g > node_ptr->g + weight) {
						adj_node->g = node_ptr->g + weight;
					}
					adj_node->f = adj_node->g + Manhattan(adj_node->co, map->target);
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

	int delta_x = map->target.x - map->agent.x;
	int delta_y = map->target.y - map->agent.y;

	int x = delta_x / abs(delta_x);
	int y = delta_y / abs(delta_y);
	Coordinate next{ map->agent.x + x, map->agent.y + y };

	bool is_astar = true;
	while (map->IsPassable(next)) {
		if (ReachTarget()) {
			is_astar = false;
			break;
		}
		nodes++;
		map->agent = next;
		next.x += x;
		next.y += y;

		//map->DisplayMap();
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;

	if (is_astar) {
		Astar *astar = new Astar(map);
		astar->MoveToTarget();
		nodes += astar->nodes;
		delete astar;
	}

	cout << "Search time: " << (clock() - clk) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "Nodes expanded: " << nodes << endl;
	return true;
}

void DDAstar::MoveToTarget() {
	FindPath();
}

bool IAstar::FindPath()
{
	clock_t clk = clock();

	Node* start = &map->matrix[map->agent.x][map->agent.y];
	start->f = 2 * Manhattan(start->co, map->target);
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
					int weight = abs(adj_node->co.x - node_ptr->co.x) + abs(adj_node->co.y - node_ptr->co.y) == 1 ? 10 : 14;
					if (adj_node->g > node_ptr->g + weight) {
						adj_node->g = node_ptr->g + weight;
					}
					adj_node->f = adj_node->g + 2 * Manhattan(adj_node->co, map->target);
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
