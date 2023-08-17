#pragma once
#include <vector>

using namespace std;

template<class T>
class Stack
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}
	void pop()
	{
		_container.pop_back();
	}

	T& top()
	{
		return _container.back();
	}

	bool empty()	{ return _container.empty(); }
	int size()	{ return _container.size(); }

private:
	vector<T> _container;
	
};


//Stack (LIFO Last-In-First-Out ���Լ���)
// STL�� Stack�� default Container�� Deque�� �����