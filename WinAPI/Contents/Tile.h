#pragma once
#include <list>
#include <GameEngineCore/GameEngineActor.h>

class Block;
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

	Block* GetBlock() const
	{
		return BlockPtr;
	}
	void SetBlock(Block* const _BlockPtr)
	{
		BlockPtr = _BlockPtr;
	}
private:
	static std::list<Tile*> AllTile;

	Block* BlockPtr = nullptr;

	bool IsEmpty = true;

	void Update(float _Delta) override;
	void Render() override;
};