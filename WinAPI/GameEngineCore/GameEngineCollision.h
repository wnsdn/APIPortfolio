#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

enum class CollisionType
{
	Point,
	Rect,
	Circle,
	
	None,
};

class GameEngineCollision : public GameEngineObject
{
	friend class CollisionInitClass;
	static bool (*CollisionFunction[static_cast<int>(CollisionType::None)][static_cast<int>(CollisionType::None)])(GameEngineCollision* _Left, GameEngineCollision* _Right);
public:
	GameEngineCollision();
	~GameEngineCollision();
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	static bool PointToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool PointToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool PointToCircle(GameEngineCollision* _Left, GameEngineCollision* _Right);

	static bool RectToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool RectToCircle(GameEngineCollision* _Left, GameEngineCollision* _Right);

	static bool CircleToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool CircleToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool CircleToCircle(GameEngineCollision* _Left, GameEngineCollision* _Right);

	template <typename EnumType>
	bool Collision(EnumType _Order, 
		std::vector<GameEngineCollision*>& _Result,
		CollisionType _ThisType = CollisionType::Circle,
		CollisionType _OtherType = CollisionType::Circle)
	{
		return Collision(static_cast<int>(_Order), _Result, _ThisType, _OtherType);
	}
	bool Collision(int _Order,
		std::vector<GameEngineCollision*>& _Result,
		CollisionType _ThisType = CollisionType::Circle,
		CollisionType _OtherType = CollisionType::Circle);

	bool CollisionCheck(GameEngineCollision* _Other,
		CollisionType _ThisType,
		CollisionType _OtherType);

	class GameEngineActor* GetMaster() const
	{
		return Master;
	}
	float4 GetCollisionPos() const
	{
		return CollisionPos;
	}
	void SetCollisionPos(const float4& _CollisionPos)
	{
		CollisionPos = _CollisionPos;
	}
	float4 GetCollisionScale() const
	{
		return CollisionScale;
	}
	void SetCollisionScale(const float4& _CollisionScale)
	{
		CollisionScale = _CollisionScale;
	}
private:
	class GameEngineActor* Master = nullptr;
	float4 CollisionPos;
	float4 CollisionScale;
};