#pragma once

// �켱���� ť ����

#include <vector>
#include <stack>
#include <queue>

// �� ���� ����
// #1. �θ�� ������ ū ����
// #2. ���� Ʈ��
// 
using namespace std;

template<class T, class Container = vector<T>, class  Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data)
	{
		// �� ���� �����
		_heap.push_back(data);

		// ���� ���� ����
		int now = static_cast<int>(_heap.size()) - 1;

		// ���� ���� ����
		// ��Ʈ ������ ��
		while (now > 0)
		{
			// �θ� ����� �����Ϳ� ���ؼ� �� ������ ����
			int next = (now - 1) / 2; // ����Ʈ������ ���� ��� ��ġ���� 1�� ���� 2�� ���� ���� �θ��� ��ġ
			//if (_heap[now] < _heap[next]) // �̹� �θ𺸴� �۴�.
			//	break;
			if (_predicate(_heap[now], _heap[next])) // class  Predicate = less<T> ���� �⺻�� ���� ������, greater<t>�� �־��ָ� ���� ���� ���� �θ��尡 �ǵ��� �Ѵ�.
				// ������ ���� return Left< Right�̰� now�� �۴ٸ� �������´�.
				break;
			
			// ������ ��ü
			::swap(_heap[now], _heap[next]);

			now = next; // �θ���ġ�� �־������� ���� ��ġ ���� ����

		}
	}

	void pop()
	{
		// �ֻ��� �����͸� ��������
		// ���� ������ �����ϱ����� ���� �� ���� root�� �ø� ���� �� �񱳸� ���� ��
		_heap[0] = _heap.back();
		_heap.pop_back(); 
		int now = 0;

		// ���� ��ġ���� �ڽĳ�� �� ���� ��, �۴ٸ� �������� ��������.
		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			// ������ ������ ���
			if (left >= _heap.size()) 
				break;
			int next = now;

			// ���� �ڽĳ��� ��
			if (_predicate(_heap[next], _heap[left]))
				next = left; // ���� �̵��ؾ��� index �� ����
			
			
			
			// ������ �����ʰ� ��, �� ����� ������ ���� �� �� ū �Ͱ� ��
			if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
				next = right;

			// ����, ������ �Ѵ� ���� ����Ű�� ������ ���� ��� = > ����
			if (next == now)
				break;

			// �ٲ�� �� ������ ����
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	T& top()
	{
		return _heap[0];
	}

	bool empty()
	{
		return _heap.empty();
	}
private:
	Container _heap = {};
	Predicate _predicate = {};

};

// �ð� ���⵵�� push, pop �Ѵ� O(logN), �θ�� �񱳵Ǵ� Ƚ���� ���ɿ� ���� �ֿ��� ������ ��ģ��. 