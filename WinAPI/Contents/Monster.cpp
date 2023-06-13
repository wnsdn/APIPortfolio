#include "Monster.h"
#include <iostream>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Player.h"

int Monster::Count = 0;

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Init(const int2& _Index, const std::string& _Path)
{
	RandomMove();

	Main = _Path;

	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	int Pos = static_cast<int>(Main.find('.'));
	std::string TmpStr = Main.substr(0, Pos);

	CreateRenderer(TmpStr + "Shadow.bmp", RenderOrder::InGameObject);
	FindRenderer(TmpStr + "Shadow.bmp")->SetPos({ 0.f, 5.f });

	CreateRenderer(_Path, RenderOrder::InGameObject, {2, 0}, {11, 1});
	FindRenderer(_Path)->CreateAnimation("Up", 0, 0, 2, 0.35f, true);
	FindRenderer(_Path)->CreateAnimation("Down", 2, 0, 2, 0.35f, true);
	FindRenderer(_Path)->CreateAnimation("Right", 6, 0, 2, 0.35f, true);
	FindRenderer(_Path)->CreateAnimation("Left", 4, 0, 2, 0.35f, true);
	FindRenderer(_Path)->CreateAnimation("Death", 8, 0, 3, 0.2f, true);
	FindRenderer(_Path)->ChangeAnimation("Up");

	++Count;
}

void Monster::Update(float _Delta)
{
	if (IsRelease)
	{
		if (GetLiveTime() >= 0.5f)
		{
			Death();
			--Count;
		}

		return;
	}

	StateUpdate(_Delta);
	FindRenderer(Main)->ChangeAnimation(Dir);

	for (auto Ptr : Level->FindActor(UpdateOrder::Water))
	{
		if (Index.X == Ptr->GetIndex().X && Index.Y == Ptr->GetIndex().Y)
		{
			IsRelease = true;
			LiveTime = 0.0f;
			FindRenderer(Main)->ChangeAnimation("Death");
			GameEngineSound::FindSound("Death.wav")->Play();
		}
	}
}

void Monster::Reset()
{
	Dir = "Down";
	Speed = 0.0f;

	FindRenderer(Main)->ChangeAnimation(Dir);
}

void Monster::RandomMove()
{
	Speed = 50.f;
	switch (rand() % 4)
	{
	case 0:
		Dir = "Left";
		break;
	case 1:
		Dir = "Right";
		break;
	case 2:
		Dir = "Up";
		break;
	case 3:
		Dir = "Down";
		break;
	}
	State = "Run";
}