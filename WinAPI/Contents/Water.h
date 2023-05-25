#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Water : public GameEngineActor
{
public:
	Water();
	~Water();
	Water(const Water& _Other) = delete;
	Water(Water&& _Other) noexcept = delete;
	Water& operator=(const Water& _Other) = delete;
	Water& operator=(Water&& _Other) noexcept = delete;

	void Init(const int2& _Index, int _Length);
private:
	float Duration = 0.5f;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
};