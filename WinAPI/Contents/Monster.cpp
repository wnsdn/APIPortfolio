#include "Monster.h"
#include <iostream>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Global.h"
#include "Player.h"
#include "Water.h"

#include <format>

int Monster::Count = 0;
int Monster::Exp = 11;

Monster::Monster()
{
}

Monster::~Monster()
{
	--Count;

	if (Collider)
	{
		delete Collider;
		Collider = nullptr;
	}
}

void Monster::Init(const int2& _Index, const std::string& _Path)
{
	Main = _Path;
	Dir = "";
	State = "Start";

	Collider = new GameEngineCollision(Pos, { 30, 30 });

	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	CreateRenderer(Main, RenderOrder::InGameObject, { 2, 0 }, { 6, 2 });
	FindRenderer(Main)->CreateAnimation("UpRun", 0, 0, 2, 0.35f, true);
	FindRenderer(Main)->CreateAnimation("DownRun", 2, 0, 2, 0.35f, true);
	FindRenderer(Main)->CreateAnimation("LeftRun", 4, 0, 2, 0.35f, true);
	FindRenderer(Main)->CreateAnimation("RightRun", 4, 1, 2, 0.35f, true);
	FindRenderer(Main)->CreateAnimation("Start", 0, 1, 4, 0.2f, false);
	FindRenderer(Main)->CreateAnimation("Death", 3, 1, 4, 0.1f, false, true);
	FindRenderer(Main)->CreateAnimation("Run", 3, 1, 1, 0.0f, false);

	++Count;
	InsertRenderer();

	CreateRenderer("OctopusShadow.bmp", RenderOrder::Shadow);
	FindRenderer("OctopusShadow.bmp")->SetPos({ 0.f, 5.f });
	FindRenderer("OctopusShadow.bmp")->InsertSingleRenderer();
}

void Monster::Update(float _Delta)
{
	StateUpdate(_Delta);
	CollisionCheck();
	if (State != "Stop")
	{
		FindRenderer(Main)->ChangeAnimation(Dir + State);
	}
	else
	{
		FindRenderer(Main)->ChangeAnimation("Run");
	}
}

void Monster::Render(float _Delta)
{
	/*DrawRect(Pos, { 30, 30 }, (255 | (0 << 8)) | (0 << 16));
	DrawRect(IndexToPos(Index), Scale, (0 | (255 << 8)) | (0 << 16));*/
	//DrawRect(Collider->GetPos(), Collider->GetScale(), Rgb(255, 0, 0));
}

void Monster::RandomMove()
{
	Speed = 50.f;
	switch (GameEngineRandom::RandomInt(3, 0))
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

void Monster::Stop()
{
	Dir = "";
	State = "Stop";
}

void Monster::Kill()
{
	if (State != "Death")
	{
		GameEngineSound::FindSound("MonsterDeath.wav")->Play();
		if (Player::MainPlayer)
		{
			Player::MainPlayer->AddKill(1);
		}
	}

	Dir = "";
	State = "Death";
}
