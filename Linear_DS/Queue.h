#pragma once
#include <vector>
#include <list>
#include <queue>

using namespace std;

// �迭 ��� ť
// ������ �������� Ȯ�� �� �� ���� �����ϴ� front������ �� ���� ������
// vector�� ���� ���� ���Ҵ� ��� ���� ���� �����ϰ�
// ���� ������ Array�� ������ �� ���� Queue�� ��� ���� ��������
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
			// ������ ���� ����
			int newSize = max(1, _size * 2);// �¿� ���� ū���� �־���;
			vector<T> newData;
			newData.resize(newSize);
			
			// ���� ������ ������ �Ҵ� �ϱ�
			for (int i = 0; i < _size; i++)
			{
				int index = (_front + i) % _container.size();
				newData[i] = _container[index];
			}

			_container.swap(newData);
			_front = 0;
			_back = _size;
		}
		// ���� �ľ�
		_container[_back] = value;
		_back = (_back + 1) % _container.size();
		// �������� ����Ű�°����� �־��ְ� ������ ��ġ�� ����
		// ������ ��ġ�� �ִ� size���� Ŀ�� �� ������ ��ü ũ��� ������

		_size++;

	}


	void pop()
	{
		_front = (_front + 1);
		_size--;
	}

	// ������ ���� ����ó�� ��ŵ
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
		// ��� �ð� ���⵵ ����
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

// Queue (FIFO First-In-First-Out ���Լ���)

// vector�����̳� ����
// �տ� �ִ� ������ ������ ��� ���꿡 ���� ����
// ���ͷ����� ����ص� Pop�� ����� �տ� ��Ҹ� ����
// �� ������ ��ĭ���Űܾ��Ѵ�
// list�� �������