#pragma once

struct Coordinate;

class Agent
{
private:
	int x, y;
public:
	enum directions{up, down, left, right};

	Agent();
	Agent(int x, int y);
	~Agent();

	inline int GetX() {
		return x;
	}

	inline int GetY() {
		return y;
	}

	void MoveAgent(directions direction);
	void MoveAgent(Coordinate co);
};

