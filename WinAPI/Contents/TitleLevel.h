#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;
private:
	class Button* StartButton = nullptr;
	class Button* ExitButton = nullptr;
	class Curtain* CurtainPtr = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	void StartButtonUpdate(float _Delta);
	void ExitButtonUpdate(float _Delta);
};