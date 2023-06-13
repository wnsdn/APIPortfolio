#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameResult : public GameEngineActor
{
public:
	GameResult();
	~GameResult();
	GameResult(const GameResult& _Other) = delete;
	GameResult(GameResult&& _Other) noexcept = delete;
	GameResult& operator=(const GameResult& _Other) = delete;
	GameResult& operator=(GameResult&& _Other) noexcept = delete;

	void RendererOn();
private:
	void Start() override;
};