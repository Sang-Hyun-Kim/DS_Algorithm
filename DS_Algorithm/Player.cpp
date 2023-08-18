#include "pch.h"
#include "Player.h"
#include "Board.h"


void Player::Init(Board* board)
{
	// ���� ���� ��ġ
	_pos = board->GetEnterPos();
	_board = board;
	
	// ��ã�� ����
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

	// ������ ��ǥ ���������� ��� ����
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

void Player::Bfs()
{
	Pos pos = _pos;

	
	// ������ ��ǥ ���������� ��� ����
	Pos dest = _board->GetExitPos();
	Pos front[4] =
	{
		Pos {-1,0},//UP
		Pos {0,-1},//Left
		Pos {1,0},//Down
		Pos {0,1},//Right
	};

	// BFS�� �����ϸ鼭 �ʿ�����
	// 1. ���� �� ���� �̹� �߰��ߴ°� ����ϴ� �ڷᱸ��
	// 2. ���� Ž�� ����� ���� ť
	// 3. dest(��������)�� ã�� ������ 

	// ������ ��ü���� ����� ����� ��(���Ӱ� ����)
	// �� ũ�⸸ŭ �߰� ���� ���� ���� ����
	const int32 size = _board->GetSize();

	// ũ�Ⱑ size x size�� bool�� ������ �迭 �ڷ����� false�� ���� �ʱ�ȭ
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	// ������������ ��ǥ�� ���� ��ǥ�� ����� 2���� �迭
	map<Pos, Pos> parent;

	// �̶� ������ ���� Map�� �����͸� ����������
	// ���� �� Ʈ���� ����Ͽ� �����͸� ���ĵ� ���·� �����ϱ� ������ �� ������ �ʿ�������.
	// ���� ���� �ڷ����� Pos�� ���� <(��) �����ڸ� ���������Ѵ�.

	// ���� ������ Queue�� ����
	queue<Pos> q;

	q.push(pos);
	discovered[pos.y][pos.x] = true;
	// �������� �ڱ��ڽ��� �θ�� ����

	parent[pos] = pos;


	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		// �湮!
		if (pos == dest)
		{
			// ������ ���� Ż��
			break;
		}
		// ���� ��ã��
		// 4���� ���⿡ ���� �ϳ��� �õ�
		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];

			// �� �� �ִ� ������ �´��� Ȯ��
			if (CanGo(nextPos) == false)
			{
				continue;
			}

			// �� �� �ִٸ�
			// �̹� �߰��� �����̸� Queue�� ���� �ʿ䰡 ����
			if (discovered[nextPos.y][nextPos.x])
			{
				continue;
			}

			// �� �� �ְ� �𸥴ٸ� Queue�� �ְ� �߰��ߴٰ� ǥ��
			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;


		}
	}

	// ��� ��� �ڵ�
	_path.clear();

	// �����س��� ����� Parent�� ������
	pos = dest;
	while (true)
	{
		_path.push_back(pos);

		// ���������� �����ϸ� ����
		if (pos == parent[pos])
			break;
		// pos =dest
		// ��ĭ�� �ڷ� �Ž��� �ö󰣴�.
		pos = parent[pos];
	}
	// �ٽ� �������� �迭
	// �̶� 
	std::reverse(_path.begin(), _path.end());
}
