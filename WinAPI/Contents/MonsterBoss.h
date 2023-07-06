#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MonsterBoss : public GameEngineActor
{
public:
	MonsterBoss();
	~MonsterBoss();
	MonsterBoss(const MonsterBoss& _Other) = delete;
	MonsterBoss(MonsterBoss&& _Other) noexcept = delete;
	MonsterBoss& operator=(const MonsterBoss& _Other) = delete;
	MonsterBoss& operator=(MonsterBoss&& _Other) noexcept = delete;
	
	void Init(const int2& _Pos);

	class GameEngineCollision* GetCollider() const
	{
		return Collider;
	}
	std::string GetState() const
	{
		return State;
	}
	void SetState(const std::string& _State)
	{
		State = _State;
	}
private:
	std::string State = "";
	std::string Dir = "";
	std::string PState = "";
	int CurHp = 10;
	int MaxHp = 10;
	float CurHpBar = 0.0f;
	float MaxHpBar = 0.0f;
	int Pattern = 0;
	float Timer = 0.0f;
	float HitTimer = 0.0f;
	int2 MidIdx{};
	class GameEngineCollision* Collider = nullptr;

	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void RandomMove();
	void ChangeDir();

	void StateUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void CaptureUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void PatternUpdate(float _Delta);

	void CollisionCheck();

	void ChangeAnimation();
};