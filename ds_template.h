#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <set>
template <typename T, typename C>
class unique_priority_queue
{
private:
	std::priority_queue<T, std::vector<T>, C> m_queue;
	std::set<T> m_set;
public:
	bool push(const T& t)
	{
		if (m_set.insert(t).second)
		{
			m_queue.push(t);
			return true;
		}
		return false;
	}

	unsigned int size() {
		return m_queue.size();
	}

	bool empty() {
		return m_queue.empty();
	}

	T top() {
		return m_queue.top();
	}

	void pop() {
		m_queue.pop();
	}
};

template <typename T>
class unique_stack
{
private:

	std::stack<T> m_stack;
	std::set<T> m_set;
public:
	bool push(const T& t)
	{
		if (m_set.insert(t).second)
		{
			m_stack.push(t);
			return true;
		}
		return false;
	}

	unsigned int size() {
		return m_stack.size();
	}

	bool empty() {
		return m_stack.empty();
	}

	T top() {
		return m_stack.top();
	}

	void pop() {
		m_stack.pop();
	}
};


template <typename T>
class unique_queue
{
private:

	std::queue<T> m_queue;
	std::set<T> m_set;
public:
	bool push(const T& t)
	{
		if (m_set.insert(t).second)
		{
			m_queue.push(t);
			return true;
		}
		return false;
	}

	unsigned int size() {
		return m_queue.size();
	}

	bool empty() {
		return m_queue.empty();
	}

	T front() {
		return m_queue.front();
	}

	void pop() {
		m_queue.pop();
	}
};
