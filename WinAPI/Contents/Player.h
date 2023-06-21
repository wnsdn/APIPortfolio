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
	void Stop();

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

	int GetKill() const
	{
		return Kill;
	}
	void SetKill(const int _Kill)
	{
		Kill = _Kill;
	}
	void AddKill(const int _Kill)
	{
		Kill += _Kill;
	}
	int GetRank() const
	{
		return Rank;
	}
	void SetRank(const int _Rank)
	{
		Rank = _Rank;
	}
	void AddRank(const int _Rank)
	{
		Rank += _Rank;
	}

	int GetPreExp() const
	{
		return PreExp;
	}
	void SetPreExp(const int _PreExp)
	{
		PreExp = _PreExp;
	}
	int GetCurExp() const
	{
		return CurExp;
	}
	void SetCurExp(const int _CurExp)
	{
		if (Rank == 19)
		{
			return;
		}

		PreExp = CurExp;
		CurExp = _CurExp;
	}
	void AddCurExp(const int _CurExp)
	{
		if (Rank == 19)
		{
			return;
		}

		PreExp = CurExp;
		CurExp += _CurExp;
	}
	int GetMaxExp() const
	{
		return MaxExp;
	}
	void SetMaxExp(const int _MaxExp)
	{
		MaxExp = _MaxExp;
	}
	int GetExpDelta() const
	{
		if (CurExp > PreExp)
		{
			return CurExp - PreExp;
		}

		return 0;
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

	int Kill = 0;
	int Rank = 0;
	int PreExp = 0;
	int CurExp = 15;
	int MaxExp = 133;

	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void StateUpdate(float _Delta);
	void DirCheck();
	void ReadyUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void CaptureUpdate(float _Delta);
	void FreeUpdate(float _Delta);
	void StopUpdate(float _Delta);

	float MoveDist = 0.f;
	float MaxDist = 8.f;
	float MoveSpeed = 10.f;
	float MoveDir = -1.f;

	const float TrimRatio = 0.6f;
	const float SpeedRatio = 0.8f;
	
	void CollisionCheck(float _Delta);
	void ChangeAnimation();
	void BombSet();
	void ExpUpdate();
};