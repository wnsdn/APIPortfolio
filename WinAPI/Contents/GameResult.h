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

	void Init(bool _Win);
private:
	int Rank = 0;
	int Kill = 0;
	int ExpDelta = 0;
	int PreExp = 0;
	int CurExp = 0;
	int MaxExp = 0;
	bool Once = false;
	bool JobDone = false;

	float ExpStart = 0.0f;
	float ExpEnd = 0.0f;
	float GaugeMax = 0.0f;

	void Update(float _Delta) override;
};