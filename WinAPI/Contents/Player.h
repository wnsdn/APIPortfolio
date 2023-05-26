#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Player : public GameEngineActor
{
public:
	Player();
	~Player();
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void Init(const int2& _Index, const std::string& _Path);

	int GetCurCount() const
	{
		return CurCount;
	}
	void SetCurCount(const int _CurCount)
	{
		CurCount = _CurCount;
	}
	void AddCurCount(const int _CurCount)
	{
		CurCount += _CurCount;
	}
private:
	int Count = 0;
	int CurCount = 0;
	int MaxCount = 0;
	int Length = 0;
	int MaxLength = 0;
	float Speed = 0.f;
	float MaxSpeed = 0.f;
	std::string Dir = "";
	std::string State = "";

	void StateUpdate(float _Delta);
	void DirCheck();
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);

	void Update(float _Delta) override;
	void Render() override;
};