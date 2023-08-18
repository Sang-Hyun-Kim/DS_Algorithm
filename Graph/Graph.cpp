#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

void CreateGraph_1()
{
    struct Vertex
    {
        vector<Vertex*> edges;

       
    };

    vector<Vertex>v;
    v.resize(6);

    v[0].edges.push_back(&v[1]);
    v[0].edges.push_back(&v[3]);
    v[1].edges.push_back(&v[0]);
    v[1].edges.push_back(&v[2]);
    v[1].edges.push_back(&v[3]);
    v[3].edges.push_back(&v[4]);
    v[5].edges.push_back(&v[4]);
   
    bool connected = false;

    // 직접연결확인
    for (Vertex* edge : v[0].edges)
    {
        if (edge == &v[3])
        {
            connected = true;
            break;
        }
    }

}

// 연결된 목록을 따로 관리
void CreateGraph_2()
{
    struct Vertex
    {
        // 데이터

    };

    vector<Vertex>v;
    v.resize(6);
    // 연결된 목록 따로 관리
    // adjacent[n] -> n번째 정점과 연결된 정점 목록을 저장
    vector<vector<int>> adjacent(6); // 2차원 배열

    bool connected = false;

    adjacent[0] = {1,3};
    adjacent[1] = { 0,2,3 };
    adjacent[3] = { 4 };
    adjacent[5] = { 4 };
    
    for (int vertex : adjacent[0])
    {
        if (vertex == 3)
        {
            connected = true;
            break;
        }
    }

    // Loop를 돌지않고 STL을 이용
    vector<int>& adj = adjacent[0];
    bool connected2 = (std::find(adj.begin(), adj.end(), 3) != adj.end());

}
// 전체적인 연결 유무 정보를 저장
void CreateGraph_3()
{
    struct Vertex
    {
        // 데이터

    };

    vector<Vertex>v;
    v.resize(6);
    // 연결된 목록 따로 관리
    //
    // 2차원 배열로 연결 유무를 전부 표현
    //
    vector<vector<bool>> adjacent(6, vector<bool>(6,false)); // 2차원 배열

    adjacent[0][1] = true;
    adjacent[0][3] = true;
    adjacent[1][0] = true;
    adjacent[1][2] = true;
    adjacent[1][3] = true;
    adjacent[3][4] = true;
    adjacent[5][4] = true;


    // 같은 질문, 0과 3이 연결되어있나
    // 좀 더 빠른 반환
    bool connected = adjacent[0][3];

    vector<vector<int>> adjacent2 =
    {
        vector<int> { -1, 15, -1, 35, -1, -1},
        vector<int> { 15, -1, 5, 10, -1, -1},
        vector<int> { -1, -1, -1, -1, -1, -1},
        vector<int> { -1, -1, -1, -1, 5, -1},
        vector<int> { -1, -1, -1, -1, -1, -1},
        vector<int> { -1, -1, -1, -1, 5, -1},
    };
    bool connected2 = adjacent[0][3] != -1;
    int weight = adjacent[0][3];
}

int main()
{
    CreateGraph_1();
    CreateGraph_2();
    CreateGraph_3();
}

// 그래프: 데이터를 담은 정점과 연결 상태, 방향, 가중치 등을 담은 간선으로 이루어짐
// 정점이 많지않고 간선도 적으면 저런방식이 되지만
// SNS처럼 정점도, 간선도 많은 경우엔 알고리즘 개선이 필요