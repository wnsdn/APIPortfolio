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

	for (int i = 1; i <= _Length; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (!DirOn[j])
			{
				continue;
			}

			int2 CurIndex = Index + DirIdx[j] * i;
			if (CurIndex.X < IndexLeft ||
				CurIndex.X >= IndexRight ||
				CurIndex.Y < IndexTop ||
				CurIndex.Y >= IndexBottom)
			{
				DirOn[j] = false;
			}

			CollisionCheck(CurIndex, j);

			if (!DirOn[j])
			{
				continue;
			}

			Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
			WaterPtr->Index = CurIndex;
			WaterPtr->Pos = IndexToPos(WaterPtr->Index);
			WaterPtr->FindRenderer("BubbleWater.bmp")->ChangeAnimation(DirStr[j]);
		}
	}
}

void Water::Start()
{
	CreateRenderer("BubbleWater.bmp", ZOrder::InGameObject, RenderOrder::Water, { 0, 0 }, { 8, 5 });
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Mid", 0, 0, 3, Duration / 8, true);
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Up", 0, 1, 8, Duration / 8, false);
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Down", 0, 2, 8, Duration / 8, false);
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Left", 0, 3, 8, Duration / 8, false);
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Right", 0, 4, 8, Duration / 8, false);
	FindRenderer("BubbleWater.bmp")->ChangeAnimation("Mid");
}

void Water::Update(float _Delta)
{
	if (LiveTime >= Duration)
	{
		Death();
	}
}
