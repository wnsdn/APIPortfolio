#include "Water.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Tile.h"
#include "Player.h"

Water::Water()
{
}

Water::~Water()
{
}

void Water::Init(const int2& _Index, int _Length, Player* _Owner)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;
	FindRenderer("RectWater.bmp")->Off();

	for (auto Ptr : Level->FindActor(UpdateOrder::Item))
	{
		if (Index == Ptr->GetIndex())
		{
			Ptr->Death();
		}
	}

	Owner = _Owner;

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
			WaterPtr->SetOwner(Owner);
			WaterPtr->FindRenderer("BubbleWater.bmp")->ChangeAnimation(DirStr[j]);
			WaterPtr->FindRenderer("RectWater.bmp")->Off();
		}
	}
	GameEngineSound::FindSound("BombExplode.wav")->Play();
}

void Water::Rect(const int2& _Index, int _Length)
{
	int Left = _Index.X - _Length;
	int Right = _Index.X + _Length;
	int Top = _Index.Y - _Length;
	int Bottom = _Index.Y + _Length;

	for (int x = Left; x <= Right; ++x)
	{
		int y[2] = { Top, Bottom };
		for (auto _Y : y)
		{
			bool Check = false;

			int2 CurIndex = { x, _Y };
			CollisionCheck2(CurIndex, Check);

			if (Check)
			{
				continue;
			}

			Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
			WaterPtr->Index = CurIndex;
			WaterPtr->Pos = IndexToPos(WaterPtr->Index);
			WaterPtr->FindRenderer("BubbleWater.bmp")->Off();
		}
	}
	for (int y = Top + 1; y < Bottom; ++y)
	{
		int x[2] = { Left, Right };
		for (auto _X : x)
		{
			bool Check = false;

			int2 CurIndex = { _X, y };
			CollisionCheck2(CurIndex, Check);

			if (Check)
			{
				continue;
			}

			Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
			WaterPtr->Index = CurIndex;
			WaterPtr->Pos = IndexToPos(WaterPtr->Index);
			WaterPtr->FindRenderer("BubbleWater.bmp")->Off();
		}
	}
	GameEngineSound::FindSound("BombExplode.wav")->Play();
}

void Water::Start()
{
	CreateRenderer("BubbleWater.bmp", RenderOrder::InGameObject, { 0, 0 }, { 8, 5 });
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Mid", 0, 0, 3, Duration / 8, true);
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Up", 0, 1, 8, Duration / 8, false);
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Down", 0, 2, 8, Duration / 8, false);
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Left", 0, 3, 8, Duration / 8, false);
	FindRenderer("BubbleWater.bmp")->CreateAnimation("Right", 0, 4, 8, Duration / 8, false);
	FindRenderer("BubbleWater.bmp")->ChangeAnimation("Mid");

	CreateRenderer("RectWater.bmp", RenderOrder::InGameObject, {}, { 4, 1 });
	FindRenderer("RectWater.bmp")->CreateAnimation("Water", 0, 0, 4, Duration / 4, false);
	FindRenderer("RectWater.bmp")->ChangeAnimation("Water");


	InsertRenderer();
}

void Water::Update(float _Delta)
{
	if (LiveTime >= Duration)
	{
		Death();
	}
}
