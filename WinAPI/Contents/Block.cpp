#include "Block.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Tile.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Init(const int2& _Index, const std::string& _Path, const float4& _Type)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	CreateRenderer(_Path, RenderOrder::InGameObject, _Type, { 10, 9 });
	FindRenderer(_Path)->SetScale({TileSize.X, TileSize.Y * 2});
	FindRenderer(_Path)->SetPos({0, -TileSize.hY()});

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (Ptr && Index == Ptr->GetIndex())
		{
			dynamic_cast<Tile*>(Ptr)->Full();
		}
	}
}
