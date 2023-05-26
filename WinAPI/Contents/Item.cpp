#include "Item.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"

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

	CreateRenderer("Item\\Item", "Main", RenderOrder::Item, true, _Type, {6, 4});
	FindRenderer("Main")->SetRenderPos({ 0, -18.f });
	FindRenderer("Main")->SetRenderScale(TileSize);

	CreateRenderer("Item\\ItemShadow", "Shadow", RenderOrder::Shadow, true, {}, { 2, 1 });
	FindRenderer("Shadow")->SetRenderPos({0, 5});
	FindRenderer("Shadow")->SetRenderScale({25, 25});
	FindRenderer("Shadow")->CreateAnimation("Big", 0, 0, 1, 0, false);
	FindRenderer("Shadow")->CreateAnimation("Small", 1, 0, 1, 0, false);
	FindRenderer("Shadow")->ChangeAnimation("Big");
}

void Item::Update(float _Delta)
{
	FindRenderer("Main")->SetRenderPos({ 0, FindRenderer("Main")->GetRenderPos().Y + MoveDir * MoveSpeed * _Delta });
	MoveDist += MoveSpeed * _Delta;

	if (MoveDist >= MaxDist)
	{
		MoveDir *= -1.f;
		MoveDist -= MaxDist;
		FindRenderer("Main")->SetRenderPos({ 0, FindRenderer("Main")->GetRenderPos().Y + MoveDir * MoveDist * _Delta });
		
		if (MoveDir == -1)
		{
			FindRenderer("Shadow")->ChangeAnimation("Big");
		}
		else
		{
			FindRenderer("Shadow")->ChangeAnimation("Small");
		}
	}

	for (auto Ptr : Level->GetActorGroup(UpdateOrder::Player))
	{
		if (Index.X == Ptr->GetIndex().X && Index.Y == Ptr->GetIndex().Y)
		{
			Death();
		}
	}
}

void Item::Render()
{
	DrawRect(Pos, TileSize);
}
