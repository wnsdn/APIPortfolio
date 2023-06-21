#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Monster : public GameEngineActor
{
public:
	Monster();
	~Monster();
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	static int GetCount()
	{
		return Count;
	}
	static void SetCount(int _Count)
	{
		Count = _Count;
	}

	static int GetExp()
	{
		return Exp;
	}
	static void SetExp(const int _Exp)
	{
		Exp = _Exp;
	}

	void Init(const int2& _Index, const std::string& _Path);
	void RandomMove();
	void Stop();
private:
	static int Count;
	static int Exp;

	std::string Main = "";
	float Speed = 0.0f;
	std::string Dir = "";
	std::string State = "";

	void StateUpdate(float _Delta);
	void StartUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void ChangeDir();

	void CollisionCheck();

	void Update(float _Delta) override;
	void Render(float _Delta) override;
};