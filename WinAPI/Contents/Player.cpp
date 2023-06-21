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

	Count = 1;
	MaxCount = 6;
	Length = 1;
	MaxLength = 7;
	StdSpeed = 33.f;
	CurSpeed = 5.0f;
	Speed = CurSpeed * StdSpeed;
	MaxSpeed = 9.f;
	Dir = "";
	State = "Ready";

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
	FindRenderer(Main)->CreateAnimation("Capture", 0, 4, 4, 1.5f, false);
	FindRenderer(Main)->CreateAnimation("Free", 0, 5, 5, 0.05f, false);
	FindRenderer(Main)->CreateAnimation("Death", 0, 6, 5, 0.1f, false);
	FindRenderer(Main)->SetPos({ 0, -11 });
	FindRenderer(Main)->Off();

	CreateRenderer("BazziReady.bmp", RenderOrder::InGameObject, {}, { 18, 1 });
	FindRenderer("BazziReady.bmp")->CreateAnimation("Ready", 0, 0, 18, 0.07f, false);
	FindRenderer("BazziReady.bmp")->SetPos({ 0, -13 });
	FindRenderer("BazziReady.bmp")->AddScale({ 3, 0 });
	FindRenderer("BazziReady.bmp")->ChangeAnimation("Ready");

	InsertRenderer();
}

void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
	CollisionCheck(_Delta);
	ChangeAnimation();

	BombSet();
	ExpUpdate();
}

void Player::Render(float _Delta)
{
	DrawRect(Pos, Scale, RGB(255, 0, 0));
	DrawRect(IndexToPos(Index), Scale, RGB(0, 255, 0));

	DrawRect(IndexToPos(Index + int2::Left), Scale, RGB(0, 0, 255));
	DrawRect(IndexToPos(Index + int2::UpLeft), Scale, RGB(0, 0, 255));
	DrawRect(IndexToPos(Index + int2::Up), Scale, RGB(0, 0, 255));
	DrawRect(IndexToPos(Index + int2::UpRight), Scale, RGB(0, 0, 255));
	DrawRect(IndexToPos(Index + int2::Right), Scale, RGB(0, 0, 255));
	DrawRect(IndexToPos(Index + int2::DownRight), Scale, RGB(0, 0, 255));
	DrawRect(IndexToPos(Index + int2::Down), Scale, RGB(0, 0, 255));
	DrawRect(IndexToPos(Index + int2::DownLeft), Scale, RGB(0, 0, 255));
}

void Player::Stop()
{
	Dir = "";
	State = "Stop";
	FindRenderer(Main)->SetPos({ 0, -11 });
}
