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

	// ������ ��ǥ ���������� ��� ����
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
		// 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{

			// ������ �������� 90�� ȸ��
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
			// ������ ����
			pos += front[_dir];
			_path.push_back(pos);
		}
		// 2. ���� �ٶ󺸴� ������ �������� ���� �� �� �ִ��� Ȯ��
		else if (CanGo(pos + front[_dir]))
		{
			// ������ ���� 
			pos += front[_dir];
			_path.push_back(pos);
		}
		else
		{
			// �������� 90�� ȸ��;
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

	// �ɾ�Դ� �� ����
	stack<Pos> trail;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		// Stack ���� üũ ��, ���� �������� ������ ��� ��ġ�ϴ��� üũ
		if (trail.empty() == false && trail.top() == _path[i + 1])
		{
			// ���ƿ� ��� ������ ���� ��ġ�Ѵٸ� �����ߴ� ���ο��� Pop ��������
			trail.pop();
		}
		else
			trail.push(_path[i]);
	}

	// ������ ����
	if (_path.empty() == false)
	{
		trail.push(_path.back());
	} // ���� ������ �����ϸ� �����⶧���� �ϴ� ����

	// ���ÿ� �Ųٷ� ����Ǿ��ֱ⶧���� ����� ���� �Űܼ� ����
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
