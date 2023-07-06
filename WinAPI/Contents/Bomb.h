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

	void Init(const int2& _Index, int _Length, class Player* _Owner, bool _Push = false);

	std::string GetDir() const
	{
		return Dir;
	}
	void SetDir(const std::string& _Dir)
	{
		Dir = _Dir;
	}
	std::string GetState() const
	{
		return State;
	}
	void SetState(const std::string& _State)
	{
		State = _State;
	}

	class Player* GetOwner() const
	{
		return Owner;
	}
private:
	class Player* Owner = nullptr;
	int Length = 0;

	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;

	std::string Dir = "";
	std::string State = "";
	float LeftMove = 0.0f;
	float RightMove = 0.0f;
	float UpMove = 0.0f;
	float DownMove = 0.0f;
	float MoveDist = 0.0f;
	float MoveSpeed = 0.0f;

	int MoveIdx = 0;

	float RendererMoveDir = -1.0f;
	float RendererMoveDist = 0.0f;
	float RendererMaxDist = 5.0f;
	float RendererMoveSpeed = 80.0f;

	void StateUpdate(float _Delta);
	void MoveUpdate(float _Delta);
	void FlyUpdate(float _Delta);

	void CollisionCheck(float _Delta);
	void KickUpdate(float _Delta);
};