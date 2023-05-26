#include "Object.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Tile.h"

Object::Object()
{
}

Object::~Object()
{
	Tile::GetTile(Index)->Empty();
}

void Object::Init(const int2& _Index, const float4& _Type)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	CreateRenderer("Object\\Object", "Main", RenderOrder::Object, true, _Type, { 10, 9 });
	FindRenderer("Main")->AddRenderScale({ 2, 2 });
	FindRenderer("Main")->SetRenderPos({ 0, -20 });

	Tile::GetTile(Index)->Full();
	Tile::GetTile(Index)->SetIsObject(true);
}

void Object::Update(float _Delta)
{
	for (auto Ptr : Level->GetActorGroup(UpdateOrder::Water))
	{
		if (Index.X == Ptr->GetIndex().X && Index.Y == Ptr->GetIndex().Y)
		{
			Death();
		}
	}
}

void Object::Render()
{
	//DrawRect(Pos, Scale);
}
