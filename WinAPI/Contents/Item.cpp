#include "Item.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Init(const int2& _Index, const std::string& _Path)
{
	Index = _Index;
	Pos = IndexToPos(Index);

	CreateRenderer(_Path, "Main", RenderOrder::Item, true);
}

void Item::Update(float _Delta)
{
	float MoveDist = 0.f;
	float MoveDir = -1.f;

	Pos.Y += MoveDir * 5.f * _Delta;
	MoveDist += 5.f * _Delta;

	if (MoveDist >= 10.f)
	{
		MoveDir *= -1.f;
		MoveDist -= 10.f;
		Pos.Y += MoveDir * MoveDist;
	}
}

void Item::Render()
{
	DrawRect(Pos, TileSize);
}
