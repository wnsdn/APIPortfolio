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

	static Player* MainPlayer;

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
	float GetSpeed() const
	{
		return Speed;
	}

	std::string GetDir() const
	{
		return Dir;
	}
	std::string GetState() const
	{
		return State;
	}
private:
	std::string Main = "";

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

	void Update(float _Delta) override;

	void StateUpdate(float _Delta);
	void DirCheck();
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void CaptureUpdate(float _Delta);

	float MoveDist = 0.f;
	float MaxDist = 8.f;
	float MoveSpeed = 10.f;
	float MoveDir = -1.f;
	
	void CollisionCheck(float _Delta);
};