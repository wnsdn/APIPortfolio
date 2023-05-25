#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI : public GameEngineActor
{
public:
	UI();
	~UI();
	UI(const UI& _Other) = delete;
	UI(UI&& _Other) noexcept = delete;
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;
private:
	void Start() override;
};