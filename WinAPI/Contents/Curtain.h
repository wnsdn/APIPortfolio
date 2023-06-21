#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Curtain : public GameEngineActor
{
public:
	Curtain();
	~Curtain();
	Curtain(const Curtain& _Other) = delete;
	Curtain(Curtain&& _Other) noexcept = delete;
	Curtain& operator=(const Curtain& _Other) = delete;
	Curtain& operator=(Curtain&& _Other) noexcept = delete;

	void SetDark(float _Delta, float _Time);
	void SetBright(float _Delta, float _Time, float Min = 0.0f);
	void Reset();
private:
	float Dark = 0.0f;
	float Bright = 255.0f;
	bool IsDark = false;
	bool IsBright = false;

	void Start() override;
};