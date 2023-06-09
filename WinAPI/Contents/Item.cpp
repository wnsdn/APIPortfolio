#include "Item.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Player.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Init(const int2& _Index, const float4& _Type)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	Type = _Type;

	CreateRenderer("Item.bmp", RenderOrder::InGameObject, Type, { 2, 5 });
	FindRenderer("Item.bmp")->SetPos({ 0, -17.f });
	FindRenderer("Item.bmp")->SetScale(Scale);

	InsertRenderer();

	CreateRenderer("ItemShadow.bmp", RenderOrder::Shadow, {}, { 2, 1 });
	FindRenderer("ItemShadow.bmp")->SetPos({ 0, 5 });
	FindRenderer("ItemShadow.bmp")->SetScale({ 25, 25 });
	FindRenderer("ItemShadow.bmp")->CreateAnimation("Big", 0, 0, 1, 0, false);
	FindRenderer("ItemShadow.bmp")->CreateAnimation("Small", 1, 0, 1, 0, false);
	FindRenderer("ItemShadow.bmp")->ChangeAnimation("Big");
	FindRenderer("ItemShadow.bmp")->InsertSingleRenderer();
}

void Item::Update(float _Delta)
{
	FindRenderer("Item.bmp")->AddPos({ 0, MoveDir * MoveSpeed * _Delta });
	MoveDist += MoveSpeed * _Delta;

	if (MoveDist >= MaxDist)
	{
		MoveDir *= -1.f;
		MoveDist -= MaxDist;
		FindRenderer("Item.bmp")->AddPos({ 0, MoveDir * MoveDist });

		if (MoveDir == -1)
		{
			FindRenderer("ItemShadow.bmp")->ChangeAnimation("Big");
		}
		else
		{
			FindRenderer("ItemShadow.bmp")->ChangeAnimation("Small");
		}
	}
}
