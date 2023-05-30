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
private:
	bool CanMove = false;

	void Update(float _Delta) override;
	void Render() override;
};