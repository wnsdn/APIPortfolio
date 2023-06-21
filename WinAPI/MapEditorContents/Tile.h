#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Tile : public GameEngineActor
{
public:
	static Tile* TileArr[13][15];

	Tile();
	~Tile();
	Tile(const Tile& _Other) = delete;
	Tile(Tile&& _Other) noexcept = delete;
	Tile& operator=(const Tile& _Other) = delete;
	Tile& operator=(Tile&& _Other) noexcept = delete;

	void Init(const float4& _Pos);

	struct Attribute
	{
		int2 Idx{};
		bool IsSet = false;
	}Attr[5];
	class GameEngineRenderer* Renderer[5]{};
private:
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};