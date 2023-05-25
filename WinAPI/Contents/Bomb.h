#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Bomb : public GameEngineActor
{
public:
	Bomb();
	~Bomb();
	Bomb(const Bomb& _Other) = delete;
	Bomb(Bomb&& _Other) noexcept = delete;
	Bomb& operator=(const Bomb& _Other) = delete;
	Bomb& operator=(Bomb&& _Other) noexcept = delete;

	void Init(const int2& _Index, const std::string& _Path, int _Length);
private:
	int Length = 0;

	void Update(float _Delta) override;
	void Render() override;
};