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
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
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
