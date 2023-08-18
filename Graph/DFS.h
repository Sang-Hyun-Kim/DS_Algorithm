#pragma once

#include <iostream>
#include <vector>

using namespace std;

// 기존 6 정점 짜리 그래프 만들기
class DFS
{
public:
	DFS()
	{

		vertices.resize(6);
		adjacent = vector<vector<int>>(6);
		visited = vector<bool>(6, false);
		// 방문 기록 초기화
	}


	struct Vertex
	{

	};


	// 인접 리스트
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

	// 인접 행렬
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

	// 시작지점으로부터 길이 있다면 계속 나아감
	void DFS_Search(int here)
	{
		visited[here] = true;// 방문체크
		cout << "Visited: " << here << endl;

		// 인접 리스트 순회
		for (int i = 0; i < adjacent[here].size(); i++)
		{
			// 새로운 정점과의 간선 발견시 저장
			int there = adjacent[here][i];
			if (visited[there] == false)
			{
				DFS_Search(there);// 해당 정점에 대해 한번더 재귀호출
			}
		}
	}
	void DFS_Search2(int here)
	{
		visited[here] = true;// 방문체크
		cout << "Visited: " << here << endl;

		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == 0)
				continue;

			// 아직 방문하지 않은 곳이 있으면 방문한다.
			if (visited[there] == false)
				DFS_Search2(there);

		}

	}
	void DFS_ALL()
	{
		visited = vector<bool>(6, false);
		for(int i = 0; i< 6 ; i++)
			if (visited[i] == false)
			{
				DFS_Search(i);
			}
	}

public:
	vector<Vertex> vertices;
	vector<vector<int>> adjacent;

	// 방문한 목록 기록
	vector<bool> visited;

};

