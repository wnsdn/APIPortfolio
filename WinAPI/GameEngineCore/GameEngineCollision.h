#pragma once
#include "GameEngineObject.h"

class GameEngineCollision : public GameEngineObject
{
public:
	static bool CollisionCheck(class GameEngineActor* _Left, class GameEngineActor* _Right);
private:
	GameEngineCollision();
	~GameEngineCollision();
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;
};