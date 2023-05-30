#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object : public GameEngineActor
{
public:
	Object();
	~Object();
	Object(const Object& _Other) = delete;
	Object(Object&& _Other) noexcept = delete;
	Object& operator=(const Object& _Other) = delete;
	Object& operator=(Object&& _Other) noexcept = delete;

	void Init(const int2& _Index, const float4& _Type);

	bool GetIsMove() const
	{
		return IsMove;
	}
	void SetIsMove(const bool _IsMove)
	{
		IsMove = _IsMove;
	}

	float GetTime() const
	{
		return Timer;
	}
	void ResetTime()
	{
		Timer = 0.0f;
	}
	void AddTime(float _Delta)
	{
		Timer += _Delta;
	}
private:
	bool IsMove = false;
	float Timer = 0.f;
	float MoveDist = 0.f;
	bool Moving = false;

	void Update(float _Delta) override;
	void Render() override;
};