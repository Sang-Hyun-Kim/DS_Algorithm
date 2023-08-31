#pragma once

// 우선순위 큐 구현

#include <vector>
#include <stack>
#include <queue>

// 힙 구조 조건
// #1. 부모는 무조건 큰 숫자
// #2. 이진 트리
// 
using namespace std;

template<class T, class Container = vector<T>, class  Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data)
	{
		// 힙 구조 만들기
		_heap.push_back(data);

		// 도장 깨기 시작
		int now = static_cast<int>(_heap.size()) - 1;

		// 가장 위에 도달
		// 루트 노드까지 비교
		while (now > 0)
		{
			// 부모 노드의 데이터와 비교해서 더 작으면 종료
			int next = (now - 1) / 2; // 이진트리에서 현재 노드 위치에서 1을 빼고 2로 나눈 몫이 부모의 위치
			//if (_heap[now] < _heap[next]) // 이미 부모보다 작다.
			//	break;
			if (_predicate(_heap[now], _heap[next])) // class  Predicate = less<T> 통해 기본은 높은 값부터, greater<t>를 넣어주면 제일 작은 값이 부모노드가 되도록 한다.
				// 선언을 보면 return Left< Right이고 now가 작다면 빠져나온다.
				break;
			
			// 데이터 교체
			::swap(_heap[now], _heap[next]);

			now = next; // 부모위치에 넣어줬으니 현재 위치 값을 수정

		}
	}

	void pop()
	{
		// 최상위 데이터를 꺼낸다음
		// 힙의 구조를 유지하기위해 가장 뒷 값을 root로 올린 다음 값 비교를 시작 함
		_heap[0] = _heap.back();
		_heap.pop_back(); 
		int now = 0;

		// 현재 위치에서 자식노드 두 값과 비교, 작다면 그쪽으로 내려간다.
		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			// 리프에 도달한 경우
			if (left >= _heap.size()) 
				break;
			int next = now;

			// 왼쪽 자식노드와 비교
			if (_predicate(_heap[next], _heap[left]))
				next = left; // 다음 이동해야할 index 를 변경
			
			
			
			// 다음엔 오른쪽과 비교, 비교 대상은 위에서 나온 것 중 큰 것과 비교
			if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
				next = right;

			// 왼쪽, 오른쪽 둘다 현재 가르키는 값보다 작을 경우 = > 종료
			if (next == now)
				break;

			// 바꿔야 할 값으로 변경
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

// 시간 복잡도는 push, pop 둘다 O(logN), 부모와 비교되는 횟수가 성능에 가장 주요한 영향을 끼친다. 