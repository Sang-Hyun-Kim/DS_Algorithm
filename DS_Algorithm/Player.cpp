#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// 목적지 좌표 도착전까지 계속 실행
	Pos dest = board->GetExitPos();
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
