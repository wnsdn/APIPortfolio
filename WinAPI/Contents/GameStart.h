#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameStart : public GameEngineActor
{
public:
	GameStart();
	~GameStart();
	GameStart(const GameStart& _Other) = delete;
	GameStart(GameStart&& _Other) noexcept = delete;
	GameStart& operator=(const GameStart& _Other) = delete;
	GameStart& operator=(GameStart&& _Other) noexcept = delete;
private:
	float Speed = 6400.0f;

	void Start() override;
	void Update(float _Delta) override;
};