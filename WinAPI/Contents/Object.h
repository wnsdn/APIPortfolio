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
	void SetBeforeDeath(bool _B)
	{
		BeforeDeath = _B;
	}
private:
	bool CanMove = false;
	bool HasItem = false;
	bool BeforeDeath = false;
	bool TimeReset = false;
	std::string MoveDir = "";
	float MoveLeft = 0.f;
	float MoveRight = 0.f;
	float MoveUp = 0.f;
	float MoveDown = 0.f;
	float MoveDist = 0.f;
	float MoveSpeed = 120.0f;
	float4 Type = {};

	void Update(float _Delta) override;
	void Release() override;

	void CollisionCheck(float _Delta);
};