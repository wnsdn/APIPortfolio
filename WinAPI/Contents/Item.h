#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Item : public GameEngineActor
{
public:
	Item();
	~Item();
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	void Init(const int2& _Index, const float4& _Type);
private:
	float4 Type = {};
	float MoveDist = 0.f;
	float MaxDist = 8.f;
	float MoveSpeed = 10.f;
	float MoveDir = -1.f;

	void Update(float _Delta) override;
	void Render() override;
};