#include "GameEngineCollision.h"
#include <list>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

bool (*GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::None)][static_cast<int>(CollisionType::None)])(GameEngineCollision* _Left, GameEngineCollision* _Right) = {};

bool GameEngineCollision::PointToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

bool GameEngineCollision::PointToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

bool GameEngineCollision::PointToCircle(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

bool GameEngineCollision::RectToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

bool GameEngineCollision::RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

bool GameEngineCollision::RectToCircle(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

bool GameEngineCollision::CircleToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

bool GameEngineCollision::CircleToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

bool GameEngineCollision::CircleToCircle(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

class CollisionInitClass
{
public:
	CollisionInitClass()
	{
		GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::Point)][static_cast<int>(CollisionType::Point)] = &GameEngineCollision::PointToPoint;
	}
};
CollisionInitClass Inst = CollisionInitClass();

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

bool GameEngineCollision::Collision(int _Order, std::vector<GameEngineCollision*>& _Result, CollisionType _ThisType, CollisionType _OtherType)
{
	if (!IsUpdate())
	{
		return false;
	}

	std::list<GameEngineCollision*>& OtherCollision = Master->GetLevel()->GetAllCollision()[_Order];
	if (!OtherCollision.size())
	{
		return false;
	}

	bool Check = false;
	for (auto Collision : OtherCollision)
	{
		if (!Collision)
		{
			MsgBoxAssert("Collision(), !Collision");
		}

		if (!Collision->IsUpdate())
		{
			return false;
		}

		if (CollisionCheck(Collision, _ThisType, _OtherType))
		{
			_Result.push_back(Collision);
			Check = true;
		}
	}
	return Check;
}

bool GameEngineCollision::CollisionCheck(GameEngineCollision* _Other, CollisionType _ThisType, CollisionType _OtherType)
{
	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](this, _Other);
}
