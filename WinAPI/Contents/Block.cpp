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

void Block::Init(const int2& _Index, const float4& _Type)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	CreateRenderer("1x1_1.bmp", RenderOrder::InGameObject, _Type, { 10, 9 });
	FindRenderer("1x1_1.bmp")->SetScale({ TileSize.X, TileSize.Y * 2 });
	FindRenderer("1x1_1.bmp")->SetPos({ 0, -TileSize.hY() });

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (Ptr && Index == Ptr->GetIndex())
		{
			dynamic_cast<Tile*>(Ptr)->Full();
		}
	}
	InsertRenderer();
}

void Block::Render(float _Delta)
{
	DrawRect(Pos, Scale, Rgb(255, 0, 0));
}