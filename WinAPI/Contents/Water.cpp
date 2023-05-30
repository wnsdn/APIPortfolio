#include "Water.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Tile.h"

Water::Water()
{
}

Water::~Water()
{
}

void Water::Init(const int2& _Index, int _Length)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	int2 DirPos[4] = { int2::Left, int2::Up, int2::Right, int2::Down };
	std::string DirStr[4] = { "Left", "Up", "Right", "Down" };
	bool DirOn[4] = { true, true, true, true };

	for (int i = 1; i <= _Length; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (!DirOn[j])
			{
				continue;
			}

			int2 CurIndex = Index + DirPos[j] * i;

			if (CurIndex.X < IndexLeft ||
				CurIndex.X >= IndexRight ||
				CurIndex.Y < IndexTop ||
				CurIndex.Y >= IndexBottom)
			{
				continue;
			}
			if (!Tile::GetTile(CurIndex)->GetIsEmpty())
			{
				DirOn[j] = false;
				for (auto Ptr : Level->FindActor(UpdateOrder::Object))
				{
					if (CurIndex.X == Ptr->GetIndex().X &&
						CurIndex.Y == Ptr->GetIndex().Y)
					{
						Tile::GetTile(CurIndex)->Empty();
						Ptr->Off();
						Ptr->ResetLiveTime();
						Ptr->FindRenderer("Main")->Off();
						Ptr->FindRenderer("Death")->On();
						Ptr->FindRenderer("Death")->ChangeAnimation("Death");
					}
				}
				for (auto Ptr : Level->FindActor(UpdateOrder::Bomb))
				{
					if (CurIndex.X == Ptr->GetIndex().X &&
						CurIndex.Y == Ptr->GetIndex().Y &&
						GetLiveTime() <= 0.1f &&
						Ptr->GetLiveTime() >= 0.3f)
					{
						Ptr->Death();
					}
				}
				continue;
			}

			for (auto Ptr : Level->FindActor(UpdateOrder::Water))
			{
				if (CurIndex.X == Ptr->GetIndex().X &&
					CurIndex.Y == Ptr->GetIndex().Y)
				{
					DirOn[j] = false;
					continue;
				}
			}

			Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
			WaterPtr->Index = CurIndex;
			WaterPtr->Pos = IndexToPos(WaterPtr->Index);
			WaterPtr->FindRenderer("Main")->ChangeAnimation(DirStr[j]);
		}
	}
}

void Water::Start()
{
	CreateRenderer("Bomb\\water", "Main", RenderOrder::Water, true, { 0, 0 }, { 8, 5 });
	FindRenderer("Main")->CreateAnimation("Mid", 0, 0, 3, Duration / 8, true);
	FindRenderer("Main")->CreateAnimation("Up", 0, 1, 8, Duration / 8, false);
	FindRenderer("Main")->CreateAnimation("Down", 0, 2, 8, Duration / 8, false);
	FindRenderer("Main")->CreateAnimation("Left", 0, 3, 8, Duration / 8, false);
	FindRenderer("Main")->CreateAnimation("Right", 0, 4, 8, Duration / 8, false);

	FindRenderer("Main")->ChangeAnimation("Mid");
}

void Water::Update(float _Delta)
{
	if (LiveTime >= Duration)
	{
		Death();
	}
}

void Water::Render()
{
	DrawRect(IndexToPos(Index), Scale);
}
