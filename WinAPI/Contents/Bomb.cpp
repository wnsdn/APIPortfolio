#include "Bomb.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Tile.h"
#include "Water.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
	Tile::GetTile(Index)->Empty();

	Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
	WaterPtr->Init(Index);
}

void Bomb::Init(const int2& _Index, const std::string& _Path)
{
	Index = _Index;
	Pos = IndexToPos(Index);

	CreateRenderer("Bomb\\BombShadow", "Shadow", RenderOrder::Shadow, true);
	FindRenderer("Shadow")->SetRenderPos({ -3.f, 16.5f });

	CreateRenderer(_Path, "Main", RenderOrder::Bomb, true, {0, 0}, {3, 1});
	FindRenderer("Main")->CreateAnimation("bubble", 0, 0, 3, 0.2f, true);
	FindRenderer("Main")->ChangeAnimation("bubble");

	Tile::GetTile(Index)->Full();
}

void Bomb::Update(float _Delta)
{
	if (LiveTime >= 2.4f)
	{
		Death();
	}
}

void Bomb::Render()
{
	DrawRect(Pos, TileSize);
}
