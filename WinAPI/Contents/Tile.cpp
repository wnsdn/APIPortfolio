#include "Tile.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Global.h"
#include "Block.h"

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

void Tile::Update(float _Delta)
{
	for (auto Temp : Level->FindActor(UpdateOrder::Block))
	{
		if (Index == Temp->GetIndex())
		{
			BlockPtr = dynamic_cast<Block*>(Temp);
		}
	}
}

void Tile::Render()
{
	//char Buffer[30] = {};
	//if (BlockPtr)
	//{
	//	sprintf_s(Buffer, "true");
	//}
	//else
	//{
	//	sprintf_s(Buffer, "false");
	//}
	//DrawStr(Pos, Buffer);

	/*if (BlockPtr)
	{
		DrawRect(Pos, Scale);
	}*/
}

Tile* Tile::GetTile(const int2& _Index)
{
	for (auto& TilePtr : AllTile)
	{
		if (TilePtr && TilePtr->Index == _Index)
		{
			return TilePtr;
		}
	}

	return nullptr;
}
