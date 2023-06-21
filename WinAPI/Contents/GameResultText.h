#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameResultText : public GameEngineActor
{
public:
	GameResultText();
	~GameResultText();
	GameResultText(const GameResultText& _Other) = delete;
	GameResultText(GameResultText&& _Other) noexcept = delete;
	GameResultText& operator=(const GameResultText& _Other) = delete;
	GameResultText& operator=(GameResultText&& _Other) noexcept = delete;

	void Init(bool _Win);
private:
	float Speed = 6400.0f;
	float Timer = 0.0f;
	int Count = 0;
	std::string State = "";

	void Start() override;
	void Update(float _Delta) override;
};