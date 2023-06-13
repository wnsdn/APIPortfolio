#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Button : public GameEngineActor
{
public:
	Button();
	~Button();
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;

	void Init(const std::string& _Path, const float4& _Pos, bool _IsActive, float _Time = 0.2f);
	void Reset();

	bool GetAction() const
	{
		return IsClick && LiveTime >= Time;
	}
	bool GetIsClick() const
	{
		return IsClick && LiveTime <= Time;
	}
	float GetTime() const
	{
		return Time;
	}
private:
	std::string Main = "";

	bool IsActiveButton = false;
	bool IsMouseOnButton = false;
	bool IsClick = false;
	float Time = 0.f;

	void ActiveUpdate(float _Delta);
	void ClickUpdate(float _Delta);

	void Update(float _Delta) override;
};