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
	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		// ���������� ���� ������ؼ� �� �ٽ�ã���ϱ�
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

struct PQNode
{
	// �� �� �� ������ ���� ������ ����
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }
	int32	f;
	int32	g;
	Pos		ps;

};

void Player::AStar()
{
	// ���ͽ�Ʈ���� ����ġ �ű�� ó��
	// A* ������ F = G + H , ���� �� F�� ���� ���� ���� ��ο� ���� �޶��� ��
	// G : ���� ������ �ش� ��ǥ���� �̵��ϴµ� ��� ���, ���� �� �� ���� ��ο� ���� ���� �� ��
	// H(Heuristic) = ���������� �󸶳� ������� (���� ���� ����, ����)
	// ���ͽ�Ʈ����� �������� �ܼ� ����ġ ����� �ƴ� Heuristic �� �� �������� �������� ���� ������ ����� �ִ� ��ǥ�� �����ϵ���
	// ������ִ� �˰���

	Pos start = _pos;
	
	Pos dest = _board->GetExitPos();
	enum
	{
		// DIR_COUNT = 4
		DIR_COUNT = 8
	}; // �밢�� ������ �� => 4, ����� �� => 8

	Pos front[] =
	{
		Pos {-1,0},//UP
		Pos {0,-1},//Left
		Pos {1,0},//Down
		Pos {0,1},//Right
		// �밢�� �߰�
		Pos { -1, -1}, // UP_LEFT
		Pos { 1, -1}, // DOWN_LEFT
		Pos { 1, 1}, // DOWN_RIGHT
		Pos { -1, 1}, // UP_RIGHT
	};

	// �̵� ���
	int32 cost[] =
	{
		10,
		10,
		10,
		10, // �� �� �� �� �� 10��
		14,
		14,
		14,
		14 // �밢�� �̵��� 14
	};

	const int32 size = _board->GetSize();

	// ClosedList, ���ݱ��� �湮�� ���
	// closed[y][x] => ((y,x)�� ���� �湮�ߴ��� ����
	vector<vector<bool>> closed(size, vector<bool>(size, false));


	// 2���� �迭 ���� �� �ʱ�ȭ
	// best[y][x] -> ���ݱ��� �߰��� (y,x) �� ���� ���� ���� ���(���� ���� ����)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// �θ� ������ 
	map<Pos, Pos> parent;

	// Open List
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
	// F�� ���� ������ ���� ��
	
	
	// 1) ����, �߰� �ý��� ����
	// - �̹� �� ���� ��θ� ã�Ҵٸ� ��ŵ
	// 2) �ڴʰ� �� ������ΰ� �߰� �� �� ������ ���� ó���� �ʼ�
	// - OpenList���� ���� ã�Ƽ� ����
	// - �߰��������ɼ�: PQ���� pop�Ѵ��� �����ϱ�, PQ�� �ƴ� ������ ���� LIST���ٸ� ��������
	// pair<int , POS> �� ������ ��ǥ�� �Բ� ������ ���� ����
	
	// �ʱⰪ
	{
		int32 g = 0;

		// ���� H �� ������
		// ���������� ��ǥ������ y,x ��ǥ ���� ���밪�� �� �Ѵ���
		// �̵� ������ 10���� �������Ƿ� 10�� ���Ѵ�.
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
		pq.push(PQNode{ g+h, g, start}); // int f, int g, Pos pos
		best[start.y][start.x] = g + h; // ��� ����
		parent[start] = start; // �θ� ��� ����
	}
	// ����� Ŀ���� ���꿡 �δ��� ����� vector�� �ƴ� map������ �����غ�����

	// Ž�� ���� ����� �������� 
	while (pq.empty() == false)
	{
		// ���� ���� �ĺ� ã��
		// greater<PQNode> ���ڸ� �־���� ������ top���� ������ root���� ���� ���� F����
		// �� ���� ��
		PQNode node = pq.top();
		pq.pop();

		// ���� ��ǥ��  ���� ��η� ã�Ƽ�, ������ ��η� �̹� �湮�Ȼ����� ���
		// Closed�� ���� �湮 ��ŵ�� �ؾ���(�߿�)
		// Closed�� ����ϵ� best�� ����ϵ� ��� ����
		// ��¼��  ������ ����ִ� best�� ���� ���� ���� ������ �۴ٸ� �̹� �湮�� ���� �ǹǷ�.....
		
		// 1: Closed ���
		if (closed[node.ps.y][node.ps.x])
			continue;

		// 2: best�� ���
		// ���� ��ǥ�� ����ִ� F ���� ��� ������� ����� F���� ���� ���
		if (best[node.ps.y][node.ps.x] < node.f) 
			continue;

		// �湮 ���� üũ
		closed[node.ps.y][node.ps.x] = true;

		//������ ���������� �ٷ� ����
		if (node.ps == dest)
			break;

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.ps + front[dir];
			// ���� �̵� ��ǥ ���
			// �� �� �ִ���?
			if (CanGo(nextPos) == false)
				continue;
			// �湮 üũ
			if (closed[nextPos.y][nextPos.x])
				continue;

			// ��� ���
			// nextPos(���� ��ǥ) �߰��� ���� ���(�θ���)�� node�� g����, ������ ������ ��ǥ�� ���� �̵� ���� �� �ϱ�
			int32 g = node.g + cost[dir];
			int32 h =  10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			// �������� ���� ��ǥ���� �󸶳� �־����ֳ�?

			// �ٸ� ��ο��� �� ���� ���� ã�Ҵٸ� ��ŵ
			if (best[nextPos.y][nextPos.x] <= g + h) // ������ ������ ó��
				continue;

			// �������� ���ݲ��� ���� ������ �´�!
			// �׷��ٸ� ���� ����
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{g+h,g,nextPos});
			parent[nextPos] = node.ps;

		}
	}


	// ��� ��� �ڵ�
	Pos pos = dest;

	_path.clear();
	_pathIndex = 0;

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
