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
	void Start() override;
	void Update(float _Delta) override;
};