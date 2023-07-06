#pragma once
#include "GameEngineObject.h"
#include "GameEngineSubObject.h"

class GameEngineCollision : public GameEngineObject, public GameEngineSubObject
{
public:
	GameEngineCollision(const float4& _Pos, const float4& _Scale);
	~GameEngineCollision();
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	static bool CollisionCheck(class GameEngineCollision* _Col1, class GameEngineCollision* _Col2);
private:
};