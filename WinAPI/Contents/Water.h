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

	void Init(const int2& _Index, int _Length, class Player* _Owner);
	void Rect(const int2& _Index, int _Length);

	class Player* GetOwner() const
	{
		return Owner;
	}
	void SetOwner(class Player* const _Owner)
	{
		Owner = _Owner;
	}
private:
	class Player* Owner = nullptr;
	float Duration = 0.5f;

	int2 DirIdx[4] = { int2::Left, int2::Up, int2::Right, int2::Down };
	std::string DirStr[4] = { "Left", "Up", "Right", "Down" };
	bool DirOn[4] = { true, true, true, true };

	void Start() override;
	void Update(float _Delta) override;

	void CollisionCheck(const int2 _CurIndex, int _Dir);
	void CollisionCheck2(const int2 _CurIndex, bool& _Check);
};