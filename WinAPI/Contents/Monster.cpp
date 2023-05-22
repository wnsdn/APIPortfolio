#include "Monster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Player.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Init(const int2& _Index, const std::string& _Path)
{
	Speed = 50.f;
	Dir = "Down";
	State = "Run";

	Index = _Index;
	Pos = IndexToPos(Index);

	CreateRenderer(_Path + "Shadow", "Shadow", RenderOrder::Shadow, true);
	FindRenderer("Shadow")->SetRenderPos({ 0.f, 5.f });

	CreateRenderer(_Path, "Main", RenderOrder::Monster, true, {2, 0}, {11, 1});
	FindRenderer("Main")->CreateAnimation("Up", 0, 0, 2, 0.35f, true);
	FindRenderer("Main")->CreateAnimation("Down", 2, 0, 2, 0.35f, true);
	FindRenderer("Main")->CreateAnimation("Right", 6, 0, 2, 0.35f, true);
	FindRenderer("Main")->CreateAnimation("Left", 4, 0, 2, 0.35f, true);
	FindRenderer("Main")->CreateAnimation("Death", 8, 0, 3, 0.2f, true);
	FindRenderer("Main")->ChangeAnimation("Up");
}

void Monster::Update(float _Delta)
{
	StateUpdate(_Delta);
	FindRenderer("Main")->ChangeAnimation(Dir);
}

void Monster::Render()
{
	DrawRect(IndexToPos(Index), TileSize);
}