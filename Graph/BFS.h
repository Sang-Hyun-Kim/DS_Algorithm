#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 정점 시작 후 연결된 정점을을
// Queue에 담은 다음
// 넣은 순서대로 다시 재귀 함수 진행
// DFS랑 다른점은 정점을 찾자마자 바로 들어가지 않고
// 대기열에 넣어놓고 찾은 순서대로 하나씩 수행한 다음 돌아옴
class BFS
{
public:


	BFS()
	{
		vertices.resize(6);
		adjacent = vector<vector<int>>(6);
		discovered = vector<bool>(6, false);
		// 방문 기록 초기화
	}

	struct Vertex
	{

	};

	void CreateGraph()
	{
		adjacent[0].push_back(1);
		adjacent[0].push_back(3);
		adjacent[1].push_back(0);
		adjacent[1].push_back(2);
		adjacent[1].push_back(3);
		adjacent[3].push_back(4);
		adjacent[5].push_back(4);
	}


	void CreateGraph2()
	{
		adjacent = vector<vector<int>>
		{

		{ 0, 1, 0, 1, 0, 0},
		{ 1, 0, 1, 1, 0, 0},
		{ 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 1, 0},
		{ 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 1, 0}

		};

	}

	void BFSearch(int here)
	{
		queue<int> q;
		q.push(here);
		discovered[here] = true;
		parent[here] = here;
		distance[here] = 0;

		while (q.empty() == false)
		{
			here = q.front();
			q.pop();
			// 발견했던 곳을 꺼내서 수행
			cout << "Visited : " << here << endl;
			for (int there : adjacent[here])
			{
				if (discovered[there])
					continue;
				
				// 발견부
				q.push(there);
				discovered[there] = true;

				parent[there] = here;
				distance[there] = distance[here] + 1;
			}

		}
	}

	//인접행렬버전
	void BFSearch_2(int here)
	{
		queue<int> q;
		q.push(here);
		discovered[here] = true;
		parent[here] = here;
		distance[here] = 0;

		while (q.empty() == false)
		{
			here = q.front();
			q.pop();
			// 발견했던 곳을 꺼내서 수행
			cout << "Visited : " << here << endl;
			// 인접행렬은 벡터랑 다르게 연결된 정점들만 들어가 있지 않으니
			// 하나의 행에 대해 전부 실행해 주는 반복문으로 수정해준다.
			for (int there=0 ; there < 6 ;there++)
			{
				// 연관없는 노드들에 대해 continue;
				if (adjacent[here][there] == 0)
				{
					continue;
				}
				if (discovered[there])
					continue;

				q.push(there);
				discovered[there] = true;

				parent[there] = here;
				distance[there] = distance[here] +1;

			}

		}
	}
	void BFSearch_All()
	{
		for (int i = 0; i < 6; i++)
		{
			if (discovered[i] == false)
			{
				BFSearch(i);
			}
		}
	}

public:
	vector<Vertex> vertices;
	vector<vector<int>> adjacent;

	// 발견기록
	vector<bool> discovered;

	// 발견한 정점이 어디서 발견되었는지

	vector<int> parent = vector<int>(6, -1);
	// 시작점에서 얼마나 이동했는지

	vector<int> distance = vector<int>(6,-1);
};

