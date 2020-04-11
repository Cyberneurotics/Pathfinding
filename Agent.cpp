#include "pch.h"
#include "Agent.h"
#include "map.h"

Agent::Agent()
{
}

Agent::Agent(int x, int y)
	:x(x), y(y)
{
}


Agent::~Agent()
{
}

void Agent::MoveAgent(directions direction)
{
	switch (direction) {
	case up:
		x++;
		break;
	case down:
		x--;
		break;
	case left:
		y--;
		break;
	case right:
		y++;
		break;
	}
}

void Agent::MoveAgent(Coordinate co)
{
	x = co.x;
	y = co.y;
}


