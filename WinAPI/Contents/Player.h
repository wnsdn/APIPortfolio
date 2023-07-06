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
	void WriteData();
	void ReadData();

	int GetCount() const
	{
		return Count;
	}
	int GetLength() const
	{
		return Length;
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

	bool GetCanKick() const
	{
		return CanKick;
	}
	bool GetCanThrow() const
	{
		return CanThrow;
	}
	int GetItemNeedle() const
	{
		return ItemNeedle;
	}
	int GetItemShield() const
	{
		return ItemShield;
	}
	int GetItemJump() const
	{
		return ItemJump;
	}
	std::string GetCurItem() const
	{
		return CurItem;
	}

	bool GetGodMode() const
	{
		return GodMode;
	}
private:
	std::string Main = "";
	class GameEngineCollision* Collider = nullptr;

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

	bool CanKick = false;
	bool CanThrow = false;
	int ItemNeedle = 0;
	int ItemShield = 0;
	int ItemJump = 0;
	std::string CurItem = "";
	bool ShieldOn = false;

	bool GodMode = false;

	int Kill = 0;
	int Rank = 0;
	int PreExp = 0;
	int CurExp = 0;
	int MaxExp = (Rank + 1) * 100;

	float MoveDist = 0.f;
	float MaxDist = 6.f;
	float MoveSpeed = 7.f;
	float MoveDir = -1.f;

	float JumpDist = 0.0f;
	float JumpMaxDist = 0.0f;
	float JumpSpeed = 0.0f;
	float RendererDist = 0.0f;
	float RendererSpeed = 0.0f;
	bool JumpDown = false;

	const float TrimRatio = 0.6f;
	const float SpeedRatio = 0.8f;

	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void StateUpdate(float _Delta);
	void CollisionCheck(float _Delta);
	void AllUpdate(float _Delta);

	void DirCheck();
	void ReadyUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void CaptureUpdate(float _Delta);
	void FreeUpdate(float _Delta);
	void StopUpdate(float _Delta);
	void JumpUpdate(float _Delta);

	void BombSet();
	void ItemUseUpdate();
	void ItemUpdate();
	void ShieldUpdate();
	void ExpUpdate();
	void ChangeAnimation();
};