#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Global.h"
#include "Bomb.h"
#include "Tile.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
	Player::MainPlayer = nullptr;
}

void Player::Init(const int2& _Index, const std::string& _Path)
{
	Main = _Path;

	Count = 1 + 1;
	MaxCount = 6;
	Length = 1 + 0;
	MaxLength = 7;
	StdSpeed = 33.f;
	CurSpeed = 5.f + 0;
	Speed = CurSpeed * StdSpeed;
	MaxSpeed = 9.f;
	Dir = "Down";
	State = "Idle";

	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize - 2;

	CreateRenderer("PlayerShadow.bmp", RenderOrder::InGameObject);
	FindRenderer("PlayerShadow.bmp")->SetPos({ -1.f, -1.4f });

	CreateRenderer(Main, RenderOrder::InGameObject, { 0, 0 }, { 5, 7 });
	FindRenderer(Main)->CreateAnimation("UpRun", 1, 0, 4, 0.15f, true);
	FindRenderer(Main)->CreateAnimation("DownRun", 1, 1, 4, 0.15f, true);
	FindRenderer(Main)->CreateAnimation("RightRun", 1, 2, 3, 0.15f, true);
	FindRenderer(Main)->CreateAnimation("LeftRun", 0, 3, 3, 0.15f, true);
	FindRenderer(Main)->CreateAnimation("UpIdle", 0, 0, 1, 0.0f, false);
	FindRenderer(Main)->CreateAnimation("DownIdle", 0, 1, 1, 0.0f, false);
	FindRenderer(Main)->CreateAnimation("RightIdle", 0, 2, 1, 0.0f, false);
	FindRenderer(Main)->CreateAnimation("LeftIdle", 3, 3, 1, 0.0f, false);
	FindRenderer(Main)->SetPos({ 0, -11 });
	FindRenderer(Main)->ChangeAnimation(Dir + State);

	FindRenderer(Main)->CreateAnimation("Capture", 0, 4, 4, 1.5f, false);
	FindRenderer(Main)->CreateAnimation("Free", 0, 5, 5, 0.1f, false);
	FindRenderer(Main)->CreateAnimation("Death", 0, 6, 5, 0.1f, false);
}

void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
	CollisionCheck(_Delta);
	if (State == "Capture")
	{
		FindRenderer(Main)->ChangeAnimation(State);
	}
	else
	{
		FindRenderer(Main)->ChangeAnimation(Dir + State);
	}

	if (State == "Capture" || State == "Death")
	{
		return;
	}

	if (Count > 0 && GameEngineInput::IsDown(VK_SPACE))
	{
		if (Tile::GetTile(Index)->GetIsEmpty())
		{
			Level->CreateActor<Bomb>(UpdateOrder::Bomb)->Init(Index, Length, this);
			FindRenderer("PlayerShadow.bmp")->SetOrderChange(true);
			FindRenderer(Main)->SetOrderChange(true);
			--Count;
		}
	}
}
