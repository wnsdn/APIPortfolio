#include "Tile.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"

std::list<Tile*> Tile::AllTile;

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Init(const int2& _Index, const float4& _Type)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	CreateRenderer("Tile\\Tile1x1", "Main", RenderOrder::Tile, false, _Type, { 10, 10 });
	FindRenderer("Main")->SetRenderScale(TileSize);
	AllTile.emplace_back(this);
}

void Tile::Render()
{
	if(!IsEmpty)
	{
		DrawRect(Pos, TileSize);
	}
	//char Buffer[30] = {};
	//sprintf_s(Buffer, "%d, %d", Index.X, Index.Y);
	//DrawStr(Pos, Buffer);
}

Tile* Tile::GetTile(const int2& _Index)
{
	for (auto& TilePtr : AllTile)
	{
		if (TilePtr->Index == _Index)
		{
			return TilePtr;
		}
	}

	return nullptr;
}
