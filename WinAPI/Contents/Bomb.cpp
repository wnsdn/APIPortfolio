#include "Bomb.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Global.h"
#include "Tile.h"
#include "Water.h"
#include "Player.h"

#include "MonsterLevel.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

void Bomb::Init(const int2& _Index, int _Length, class Player* _Owner, bool _Push)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	Length = _Length;
	Owner = _Owner;

	CreateRenderer("Bubble.bmp", RenderOrder::InGameObject, { 0, 0 }, { 3, 1 });
	FindRenderer("Bubble.bmp")->CreateAnimation("Bubble", 0, 0, 3, 0.2f, true);
	FindRenderer("Bubble.bmp")->ChangeAnimation("Bubble");

	if (!_Push)
	{
		GameEngineSound::FindSound("BombSet.mp3")->Play();
	}
	else
	{
		GameEngineSound::FindSound("PlayerKick.mp3")->Play();
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (Ptr && Index == Ptr->GetIndex())
		{
			dynamic_cast<Tile*>(Ptr)->Full();
		}
	}
	InsertRenderer();

	CreateRenderer("BubbleShadow.bmp", RenderOrder::Shadow);
	FindRenderer("BubbleShadow.bmp")->SetPos({ -3.f, 16.5f });
	FindRenderer("BubbleShadow.bmp")->InsertSingleRenderer();
}

void Bomb::Update(float _Delta)
{
	if (LiveTime >= 2.4f)
	{
		Death();
	}

	/*if (Player::MainPlayer && Player::MainPlayer->GetState() == "Death")
	{
		LiveTime = 0.0f;
	}*/
	if (dynamic_cast<MonsterLevel*>(Level)->GetState() == "Win" ||
		dynamic_cast<MonsterLevel*>(Level)->GetState() == "Lose")
	{
		LiveTime = 0.0f;
	}

	StateUpdate(_Delta);
	CollisionCheck(_Delta);
}

void Bomb::Render(float _Delta)
{
	/*DrawRect(Pos, Scale, Rgb(255, 0, 0));
	DrawRect(IndexToPos(Index), Scale, Rgb(0, 255, 0));*/
}

void Bomb::Release()
{
	if (Owner)
	{
		Owner->AddCount(1);
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (Ptr && Index == Ptr->GetIndex())
		{
			dynamic_cast<Tile*>(Ptr)->Empty();
		}
	}

	Level->CreateActor<Water>(UpdateOrder::Water)->Init(Index, Length, Owner);
}
