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

	int GetCount() const
	{
		return Count;
	}
	void SetCount(const int _Count)
	{
		Count = _Count;
	}
	void AddCount(const int _Count)
	{
		Count += _Count;
	}

	int GetLength() const
	{
		return Length;
	}
	void SetLength(const int _Length)
	{
		Length = _Length;
	}
	void AddLength(const int _Length)
	{
		Length += _Length;
	}

	float GetCurSpeed() const
	{
		return CurSpeed;
	}
	void SetCurSpeed(const float _CurSpeed)
	{
		CurSpeed = _CurSpeed;
	}
	void AddCurSpeed(const float _CurSpeed)
	{
		CurSpeed += _CurSpeed;
	}

	std::string GetDir() const
	{
		return Dir;
	}
private:
	int Count = 0;
	int MaxCount = 0;
	int Length = 0;
	int MaxLength = 0;
	float StdSpeed = 0.f;
	float CurSpeed = 0.f;
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