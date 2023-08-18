#pragma once

#include <iostream>
#include <vector>

using namespace std;

// ���� 6 ���� ¥�� �׷��� �����
class DFS
{
public:
	DFS()
	{

		vertices.resize(6);
		adjacent = vector<vector<int>>(6);
		visited = vector<bool>(6, false);
		// �湮 ��� �ʱ�ȭ
	}


	struct Vertex
	{

	};


	// ���� ����Ʈ
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

	// ���� ���
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

	// �����������κ��� ���� �ִٸ� ��� ���ư�
	void DFS_Search(int here)
	{
		visited[here] = true;// �湮üũ
		cout << "Visited: " << here << endl;

		// ���� ����Ʈ ��ȸ
		for (int i = 0; i < adjacent[here].size(); i++)
		{
			// ���ο� �������� ���� �߽߰� ����
			int there = adjacent[here][i];
			if (visited[there] == false)
			{
				DFS_Search(there);// �ش� ������ ���� �ѹ��� ���ȣ��
			}
		}
	}
	void DFS_Search2(int here)
	{
		visited[here] = true;// �湮üũ
		cout << "Visited: " << here << endl;

		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == 0)
				continue;

			// ���� �湮���� ���� ���� ������ �湮�Ѵ�.
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

	// �湮�� ��� ���
	vector<bool> visited;

};

