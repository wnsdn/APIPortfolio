#include "Monster.h"
#include <iostream>
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
	Main = _Path;
	Dir = "";
	State = "Start";

	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	int Pos = static_cast<int>(Main.find('.'));
	std::string TmpStr = Main.substr(0, Pos);

	CreateRenderer(TmpStr + "Shadow.bmp", RenderOrder::InGameObject);
	FindRenderer(TmpStr + "Shadow.bmp")->SetPos({ 0.f, 5.f });

	CreateRenderer(Main, RenderOrder::InGameObject, {2, 0}, {6, 2});
	FindRenderer(Main)->CreateAnimation("UpRun", 0, 0, 2, 0.35f, true);
	FindRenderer(Main)->CreateAnimation("DownRun", 2, 0, 2, 0.35f, true);
	FindRenderer(Main)->CreateAnimation("LeftRun", 4, 0, 2, 0.35f, true);
	FindRenderer(Main)->CreateAnimation("RightRun", 4, 1, 2, 0.35f, true);
	FindRenderer(Main)->CreateAnimation("Start", 0, 1, 4, 0.2f, false);
	FindRenderer(Main)->CreateAnimation("Death", 3, 1, 4, 0.1f, false, true);
	FindRenderer(Main)->CreateAnimation("Run", 3, 1, 1, 0.0f, false);

	++Count;
}

void Monster::Update(float _Delta)
{
	StateUpdate(_Delta);
	CollisionCheck();
	FindRenderer(Main)->ChangeAnimation(Dir + State);
}

void Monster::Render(float _Delta)
{
	DrawRect(Pos, {30, 30}, (255 | (0 << 8)) | (0 << 16));
	DrawRect(IndexToPos(Index), Scale, (0 | (255 << 8)) | (0 << 16));
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