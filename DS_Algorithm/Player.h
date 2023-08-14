#pragma once

class Board;

class Player
{
	// 이동하는것을 직접 보기위한 지연시간
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

	// 방향값: 초기 윗방향
	int32 _dir = DIR_UP;
	// 현재 위치
	Board* _board = nullptr;

	vector<Pos> _path;
	// 경로를 어디까지 이동했는지 기록하는 변수
	uint32 _pathIndex = 0;
	uint64 _sumTick = 0;
};

