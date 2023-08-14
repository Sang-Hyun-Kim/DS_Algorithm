#pragma once

class Board;

class Player
{
	// �̵��ϴ°��� ���� �������� �����ð�
	enum
	{
		MOVE_TICK = 100
	};
public:

	void Init(Board* board);
	void Update(uint64 deltaTick);


	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

	bool CanGo(Pos pos);
private:
	Pos _pos = {};

	// ���Ⱚ: �ʱ� ������
	int32 _dir = DIR_UP;
	// ���� ��ġ
	Board* _board = nullptr;

	vector<Pos> _path;
	// ��θ� ������ �̵��ߴ��� ����ϴ� ����
	uint32 _pathIndex = 0;
	uint64 _sumTick = 0;
};

