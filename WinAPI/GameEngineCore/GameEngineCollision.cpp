#include "GameEngineCollision.h"

GameEngineCollision::GameEngineCollision(const float4& _Pos, const float4& _Scale)
{
	Pos = _Pos;
	Scale = _Scale;
}

GameEngineCollision::~GameEngineCollision()
{
}

bool GameEngineCollision::CollisionCheck(GameEngineCollision* _Col1, GameEngineCollision* _Col2)
{
	if (_Col1->Left() > _Col2->Right() ||
		_Col1->Right() < _Col2->Left() ||
		_Col1->Top() > _Col2->Bottom() ||
		_Col1->Bottom() < _Col2->Top())
	{
		return false;
	}

	return true;
}
