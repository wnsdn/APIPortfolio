#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Bomb.h"
#include "Tile.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const int2& _Index, const std::string& _Path)
{
	Speed = 300.f;
	Dir = "Down";
	State = "Idle";

	Index = _Index;
	Pos = IndexToPos(Index);

	CreateRenderer("Player\\PlayerShadow", "Shadow", RenderOrder::Shadow, true);
	FindRenderer("Shadow")->SetRenderPos({ -1.f, -1.4f });

	CreateRenderer(_Path, "Main", RenderOrder::Player, true, {0, 0}, {5, 7});
	FindRenderer("Main")->CreateAnimation("UpRun", 1, 0, 4, 0.15f, true);
	FindRenderer("Main")->CreateAnimation("DownRun", 1, 1, 4, 0.15f, true);
	FindRenderer("Main")->CreateAnimation("RightRun", 1, 2, 3, 0.15f, true);
	FindRenderer("Main")->CreateAnimation("LeftRun", 0, 3, 3, 0.15f, true);
	FindRenderer("Main")->CreateAnimation("UpIdle", 0, 0, 1, 0.1f, false);
	FindRenderer("Main")->CreateAnimation("DownIdle", 0, 1, 1, 0.1f, false);
	FindRenderer("Main")->CreateAnimation("RightIdle", 0, 2, 1, 0.1f, false);
	FindRenderer("Main")->CreateAnimation("LeftIdle", 3, 3, 1, 0.1f, false);
	FindRenderer("Main")->SetRenderPos({ 0, -11 });
}

void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
	FindRenderer("Main")->ChangeAnimation(Dir + State);

	if (GameEngineInput::IsDown(VK_SPACE))
	{
		if (Tile::GetTile(Index)->GetIsEmpty())
		{
			Bomb* NewBomb = Level->CreateActor<Bomb>(UpdateOrder::Bomb);
			NewBomb->Init(Index, "Bomb\\bubble");
		}
	}
}

void Player::Render()
{
	//DrawRect(Pos, TileSize);
	DrawRect(IndexToPos(Index), TileSize);
}
