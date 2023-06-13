#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Cursor : public GameEngineActor
{
public:
	Cursor();
	~Cursor();
	Cursor(const Cursor& _Other) = delete;
	Cursor(Cursor&& _Other) noexcept = delete;
	Cursor& operator=(const Cursor& _Other) = delete;
	Cursor& operator=(Cursor&& _Other) noexcept = delete;
private:
	void Start() override;
	void Update(float _Delta) override;
};