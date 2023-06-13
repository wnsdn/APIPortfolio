#include "Tile.h"
#include <GameEngineCore/GameEngineRenderer.h>

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

	CreateRenderer("Tile1x1.bmp", RenderOrder::Tile, _Type, { 10, 10 });
	FindRenderer("Tile1x1.bmp")->SetScale(TileSize);
	AllTile.emplace_back(this);
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
