#include "Bomb.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Global.h"
#include "Tile.h"
#include "Water.h"
#include "Player.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

void Bomb::Init(const int2& _Index, int _Length, class Player* _Owner)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;
	
	Length = _Length;
	Owner = _Owner;

	CreateRenderer("BubbleShadow.bmp", RenderOrder::InGameObject);
	FindRenderer("BubbleShadow.bmp")->SetPos({ -3.f, 16.5f });

	CreateRenderer("Bubble.bmp", RenderOrder::InGameObject, { 0, 0 }, { 3, 1 });
	FindRenderer("Bubble.bmp")->CreateAnimation("Bubble", 0, 0, 3, 0.2f, true);
	FindRenderer("Bubble.bmp")->ChangeAnimation("Bubble");

	GameEngineSound::FindSound("BombSet.mp3")->Play();

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (Ptr && Index == Ptr->GetIndex())
		{
			dynamic_cast<Tile*>(Ptr)->Full();
		}
	}
	InsertRenderer();
}

void Bomb::Update(float _Delta)
{
	if (LiveTime >= 2.4f)
	{
		Death();
	}
}

void Bomb::Release()
{
	Owner->AddCount(1);

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (Ptr && Index == Ptr->GetIndex())
		{
			dynamic_cast<Tile*>(Ptr)->Empty();
		}
	}

	Level->CreateActor<Water>(UpdateOrder::Water)->Init(Index, Length, Owner);

	GameEngineSound::FindSound("BombExplode.wav")->Play();
}
