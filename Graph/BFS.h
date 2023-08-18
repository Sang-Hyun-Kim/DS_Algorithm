#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ���� ���� �� ����� ��������
// Queue�� ���� ����
// ���� ������� �ٽ� ��� �Լ� ����
// DFS�� �ٸ����� ������ ã�ڸ��� �ٷ� ���� �ʰ�
// ��⿭�� �־���� ã�� ������� �ϳ��� ������ ���� ���ƿ�
class BFS
{
public:


	BFS()
	{
		vertices.resize(6);
		adjacent = vector<vector<int>>(6);
		discovered = vector<bool>(6, false);
		// �湮 ��� �ʱ�ȭ
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
			// �߰��ߴ� ���� ������ ����
			cout << "Visited : " << here << endl;
			for (int there : adjacent[here])
			{
				if (discovered[there])
					continue;
				
				// �߰ߺ�
				q.push(there);
				discovered[there] = true;

				parent[there] = here;
				distance[there] = distance[here] + 1;
			}

		}
	}

	//������Ĺ���
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
			// �߰��ߴ� ���� ������ ����
			cout << "Visited : " << here << endl;
			// ��������� ���Ͷ� �ٸ��� ����� �����鸸 �� ���� ������
			// �ϳ��� �࿡ ���� ���� ������ �ִ� �ݺ������� �������ش�.
			for (int there=0 ; there < 6 ;there++)
			{
				// �������� ���鿡 ���� continue;
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

	// �߰߱��
	vector<bool> discovered;

	// �߰��� ������ ��� �߰ߵǾ�����

	vector<int> parent = vector<int>(6, -1);
	// ���������� �󸶳� �̵��ߴ���

	vector<int> distance = vector<int>(6,-1);
};

