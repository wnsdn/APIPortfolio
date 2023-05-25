#include "GameEngineCollision.h"
#include "GameEngineActor.h"

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

bool GameEngineCollision::CollisionCheck(GameEngineActor* _Left, GameEngineActor* _Right)
{
	if (_Left->Left() > _Right->Right() ||
		_Left->Right() < _Right->Left() ||
		_Left->Top() > _Right->Bot() ||
		_Left->Bot() < _Right->Top())
	{
		return false;
	}

	return true;
}
