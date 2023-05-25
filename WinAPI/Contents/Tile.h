#pragma once
#include <list>
#include <GameEngineCore/GameEngineActor.h>

class Tile : public GameEngineActor
{
public:
	Tile();
	~Tile();
	Tile(const Tile& _Other) = delete;
	Tile(Tile&& _Other) noexcept = delete;
	Tile& operator=(const Tile& _Other) = delete;
	Tile& operator=(Tile&& _Other) noexcept = delete;

	void Init(const int2& _Index, const float4& _Type);

	static Tile* GetTile(const int2& _Index);
	bool GetIsEmpty() const
	{
		return IsEmpty;
	}
	void Empty()
	{
		IsEmpty = true;
	}
	void Full()
	{
		IsEmpty = false;
	}

	bool GetIsBomb() const
	{
		return IsBomb;
	}
	void SetIsBomb(const bool _IsBomb)
	{
		IsBomb = _IsBomb;
	}
private:
	static std::list<Tile*> AllTile;

	bool IsEmpty = true;
	bool IsBomb = false;

	void Render() override;
};