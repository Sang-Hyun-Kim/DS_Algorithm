#pragma once
#include <vector>
#include <list>
#include <queue>

using namespace std;

// 배열 기반 큐
// 공간을 고정으로 확보 한 후 앞을 지정하는 front변수가 맨 앞을 추적함
// vector에 의한 공간 재할당 기능 같은 것은 제외하고
// 실제 고정된 Array로 만들어야 할 때의 Queue의 기능 만을 구현하자
template<class T>
class ArrayQueue
{
public:

	ArrayQueue()
	{
		_container.resize(100);
	}


	void push(const T& value)
	{
		if (_size == _container.size())
		{
			// 데이터 공간 증설
			int newSize = max(1, _size * 2);// 좌우 비교후 큰값을 넣어줌;
			vector<T> newData;
			newData.resize(newSize);
			
			// 증설 공간에 데이터 할당 하기
			for (int i = 0; i < _size; i++)
			{
				int index = (_front + i) % _container.size();
				newData[i] = _container[index];
			}

			_container.swap(newData);
			_front = 0;
			_back = _size;
		}
		// 공간 파악
		_container[_back] = value;
		_back = (_back + 1) % _container.size();
		// 마지막을 가르키는공간에 넣어주고 마지막 위치를 증가
		// 마지막 위치가 최대 size보다 커질 수 있으니 전체 크기로 나누기

		_size++;

	}


	void pop()
	{
		_front = (_front + 1);
		_size--;
	}

	// 데이터 유무 예외처리 스킵
	T& front()
	{
		return _container[_front];
	}

	bool empty() { return _size==0; }
	int size() { return _size; }

private:

	vector<T> _container;
	int _front = 0;
	int _back = 0;
	int _size = 0;

};


template<class T>
class ListQueue
{
public:

	void push(const T& value)
	{
		_container.push_back(value);
	}
	void pop()
	{
		_container.pop_front();
		// 상수 시간 복잡도 가능
	}
	T& front()
	{
		return _container.front();
	}

	bool empty() { return _container.empty(); }
	int size() { return _container.size(); }

private:
	
	list<T> _container;

};

// Queue (FIFO First-In-First-Out 선입선출)

// vector컨테이너 사용시
// 앞에 넣는 동작을 수행할 경우 연산에 좋지 못함
// 이터레이터 사용해도 Pop을 수행시 앞에 요소를 빼고
// 다 앞으로 한칸씩옮겨야한다
// list를 사용하자