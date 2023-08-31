#include "pch.h"
#include "Player.h"
#include "Board.h"


void Player::Init(Board* board)
{
	// 시작 지점 배치
	_pos = board->GetEnterPos();
	_board = board;
	
	// 길찾기 수행
	//RightHand();
	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		// 마지막까지 가면 재생성해서 길 다시찾게하기
		_board->GenerateMap();
		Init(_board);
		return;
	}
	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;
	}
	_pos = _path[_pathIndex];
	_pathIndex++;

}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{


	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// 목적지 좌표 도착전까지 계속 실행
	Pos dest = _board->GetExitPos();
	Pos front[4] =
	{
		Pos {-1,0},//UP
		Pos {0,-1},//Left
		Pos {1,0},//Down
		Pos {0,1},//Right
	};

	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{

			// 오른쪽 방향으로 90도 회전
		/*	switch (_dir)
			{
			case DIR_UP:
				_dir = DIR_RIGHT;
				break;
			case DIR_LEFT:
				_dir = DIR_UP;
				break;
			case DIR_DOWN:
				_dir = DIR_LEFT;
				break;
			case DIR_RIGHT:
				_dir = DIR_DOWN;
				break;
			}*/
			_dir = newDir;
			// 앞으로 전진
			pos += front[_dir];
			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진 할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 전진 
			pos += front[_dir];
			_path.push_back(pos);
		}
		else
		{
			// 왼쪽으로 90도 회전;
			_dir = (_dir + 1) % DIR_COUNT;
			/*switch (_dir)
			{
			case DIR_UP:
				_dir = DIR_LEFT;
				break;
			case DIR_LEFT:
				_dir = DIR_DOWN;
				break;
			case DIR_DOWN:
				_dir = DIR_RIGHT;
				break;
			case DIR_RIGHT:
				_dir = DIR_UP;
				break;
			}*/
		}
	}

	// 걸어왔던 길 복기
	stack<Pos> trail;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		// Stack 공백 체크 후, 내가 다음으로 가야할 길과 일치하는지 체크
		if (trail.empty() == false && trail.top() == _path[i + 1])
		{
			// 돌아온 길과 가야할 길이 일치한다면 저장했던 진로에서 Pop 시켜주자
			trail.pop();
		}
		else
			trail.push(_path[i]);
	}

	// 목적지 도착
	if (_path.empty() == false)
	{
		trail.push(_path.back());
	} // 연산 순서상 도착하면 끝나기때문에 일단 넣자

	// 스택에 거꾸로 저장되어있기때문에 출력을 위해 옮겨서 저장
	vector<Pos> temppath;
	while (trail.empty() == false)
	{
		temppath.push_back(trail.top());
		trail.pop();
	}

	std::reverse(temppath.begin(), temppath.end());

	_path = temppath;

}

void Player::Bfs()
{
	Pos pos = _pos;

	
	// 목적지 좌표 도착전까지 계속 실행
	Pos dest = _board->GetExitPos();
	Pos front[4] =
	{
		Pos {-1,0},//UP
		Pos {0,-1},//Left
		Pos {1,0},//Down
		Pos {0,1},//Right
	};

	// BFS로 구현하면서 필요한점
	// 1. 다음 갈 길을 이미 발견했는가 기록하는 자료구조
	// 2. 다음 탐색 대상을 넣을 큐
	// 3. dest(도착지점)을 찾을 때까지 

	// 보드의 전체적인 사이즈를 계산한 뒤(새롭게 구현)
	// 그 크기만큼 발견 여부 저장 변수 선언
	const int32 size = _board->GetSize();

	// 크기가 size x size인 bool형 이차원 배열 자료형을 false로 전부 초기화
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	// 목적지까지의 좌표의 이전 좌표를 기록할 2차원 배열
	map<Pos, Pos> parent;

	// 이때 주의할 점이 Map은 데이터를 받을때마다
	// 레드 블랙 트리를 사용하여 데이터를 정렬된 상태로 유지하기 때문에 비교 연산이 필요해진다.
	// 직접 만든 자료형인 Pos에 대해 <(비교) 연산자를 만들어줘야한다.

	// 정점 정보를 Queue에 저장
	queue<Pos> q;

	q.push(pos);
	discovered[pos.y][pos.x] = true;
	// 시작점은 자기자신이 부모로 설정

	parent[pos] = pos;


	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		// 방문!
		if (pos == dest)
		{
			// 목적지 도착 탈출
			break;
		}
		// 아직 길찾기
		// 4개의 방향에 대해 하나씩 시도
		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];

			// 갈 수 있는 지역이 맞는지 확인
			if (CanGo(nextPos) == false)
			{
				continue;
			}

			// 갈 수 있다면
			// 이미 발견한 지역이면 Queue에 넣을 필요가 없음
			if (discovered[nextPos.y][nextPos.x])
			{
				continue;
			}

			// 갈 수 있고 모른다면 Queue에 넣고 발견했다고 표시
			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;


		}
	}

	// 경로 계산 코드
	_path.clear();

	// 저장해놨던 경로인 Parent를 역으로
	pos = dest;
	while (true)
	{
		_path.push_back(pos);

		// 시작점으로 도착하면 종료
		if (pos == parent[pos])
			break;
		// pos =dest
		// 한칸씩 뒤로 거슬러 올라간다.
		pos = parent[pos];
	}
	// 다시 역순으로 배열
	// 이때 
	std::reverse(_path.begin(), _path.end());
}

struct PQNode
{
	// 값 비교 후 저장을 위한 연산자 구현
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }
	int32	f;
	int32	g;
	Pos		ps;

};

void Player::AStar()
{
	// 다익스트라의 가중치 매기기 처럼
	// A* 에서는 F = G + H , 최종 값 F가 작을 수록 좋고 경로에 따라 달라질 것
	// G : 시작 점에서 해당 좌표까지 이동하는데 드는 비용, 작을 수 록 좋고 경로에 따라 변경 될 것
	// H(Heuristic) = 목적지에서 얼마나 가까운지 (작을 수록 좋음, 고정)
	// 다익스트라와의 차이점은 단순 가중치 계산이 아닌 Heuristic 이 들어가 목적지를 기준으로 점점 가깝게 만들어 주는 좌표를 선택하도록
	// 만들어주는 알고리즘

	Pos start = _pos;
	
	Pos dest = _board->GetExitPos();
	enum
	{
		// DIR_COUNT = 4
		DIR_COUNT = 8
	}; // 대각선 사용안할 때 => 4, 사용할 때 => 8

	Pos front[] =
	{
		Pos {-1,0},//UP
		Pos {0,-1},//Left
		Pos {1,0},//Down
		Pos {0,1},//Right
		// 대각선 추가
		Pos { -1, -1}, // UP_LEFT
		Pos { 1, -1}, // DOWN_LEFT
		Pos { 1, 1}, // DOWN_RIGHT
		Pos { -1, 1}, // UP_RIGHT
	};

	// 이동 비용
	int32 cost[] =
	{
		10,
		10,
		10,
		10, // 상 좌 하 우 는 10씩
		14,
		14,
		14,
		14 // 대각선 이동은 14
	};

	const int32 size = _board->GetSize();

	// ClosedList, 지금까지 방문한 목록
	// closed[y][x] => ((y,x)에 대해 방문했는지 여부
	vector<vector<bool>> closed(size, vector<bool>(size, false));


	// 2차원 배열 구현 후 초기화
	// best[y][x] -> 지금까지 발견한 (y,x) 에 대한 가장 좋은 비용(작을 수록 좋음)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// 부모 추적용 
	map<Pos, Pos> parent;

	// Open List
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
	// F가 작은 순으로 나올 것
	
	
	// 1) 예약, 발견 시스템 구현
	// - 이미 더 좋은 경로를 찾았다면 스킵
	// 2) 뒤늦게 더 좋은경로가 발견 될 수 있으니 예외 처리가 필수
	// - OpenList에서 직접 찾아서 제거
	// - 추가구현가능성: PQ에서 pop한다음 무시하기, PQ가 아닌 접근이 쉬운 LIST였다면 가능해짐
	// pair<int , POS> 로 점수와 좌표를 함께 관리할 수도 있음
	
	// 초기값
	{
		int32 g = 0;

		// 임의 H 값 지정식
		// 시작지점과 목표지점의 y,x 좌표 값의 절대값을 더 한다음
		// 이동 단위가 10으로 떨어지므로 10을 곱한다.
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g+h, g, start}); // int f, int g, Pos pos
		best[start.y][start.x] = g + h; // 비용 갱신
		parent[start] = start; // 부모 노드 저장
	}
	// 사이즈가 커지면 연산에 부담이 생기니 vector가 아닌 map등으로 구현해보세요

	// 탐색 예약 목록이 빌때까지 
	while (pq.empty() == false)
	{
		// 제일 좋은 후보 찾기
		// greater<PQNode> 인자를 넣어줬기 때문에 top으로 나오는 root에는 가장 작은 F값이
		// 들어가 있을 것
		PQNode node = pq.top();
		pq.pop();

		// 동일 좌표를  여러 경로로 찾아서, 더빠른 경로로 이미 방문된상태인 경우
		// Closed를 통해 방문 스킵을 해야함(중요)
		// Closed를 사용하든 best를 사용하든 상관 없음
		// 어쩌피  기존에 들어있는 best의 값이 현재 구한 값보다 작다면 이미 방문한 것이 되므로.....
		
		// 1: Closed 사용
		if (closed[node.ps.y][node.ps.x])
			continue;

		// 2: best를 사용
		// 현재 좌표가 들어있는 F 값이 방금 계산한의 노드의 F보다 작을 경우
		if (best[node.ps.y][node.ps.x] < node.f) 
			continue;

		// 방문 여부 체크
		closed[node.ps.y][node.ps.x] = true;

		//목적지 도착했으면 바로 종료
		if (node.ps == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.ps + front[dir];
			// 다음 이동 좌표 계산
			// 갈 수 있는지?
			if (CanGo(nextPos) == false)
				continue;
			// 방문 체크
			if (closed[nextPos.y][nextPos.x])
				continue;

			// 비용 계산
			// nextPos(다음 좌표) 발견전 기존 노드(부모노드)인 node의 g값에, 방향이 결정된 좌표에 대한 이동 값을 더 하기
			int32 g = node.g + cost[dir];
			int32 h =  10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			// 목적지가 다음 좌표에서 얼마나 멀어져있나?

			// 다른 경로에서 더 빠른 길을 찾았다면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h) // 동점은 선착순 처리
				continue;

			// 이정도면 지금꺼가 제일 작은게 맞다!
			// 그렇다면 예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{g+h,g,nextPos});
			parent[nextPos] = node.ps;

		}
	}


	// 경로 계산 코드
	Pos pos = dest;

	_path.clear();
	_pathIndex = 0;

	while (true)
	{
		_path.push_back(pos);

		// 시작점으로 도착하면 종료
		if (pos == parent[pos])
			break;
		// pos =dest
		// 한칸씩 뒤로 거슬러 올라간다.
		pos = parent[pos];
	}
	// 다시 역순으로 배열
	// 이때 
	std::reverse(_path.begin(), _path.end());
}
