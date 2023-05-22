#include "Water.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"

Water::Water()
{
}

Water::~Water()
{
}

void Water::Init(const int2& _Index)
{
	Index = _Index;
	Pos = IndexToPos(Index);

	int2 DirPos[4] = { int2::Left, int2::Up, int2::Right, int2::Down };
	std::string DirStr[4] = { "Left", "Up", "Right", "Down" };

	for (int i = 1; i <= Length; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (Index + DirPos[j] * i >= IndexLeftTop &&
				Index + DirPos[j] * i < IndexRightBottom)
			{
				Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
				WaterPtr->Index = Index + DirPos[j] * i;
				WaterPtr->Pos = IndexToPos(WaterPtr->Index);
				WaterPtr->FindRenderer("Main")->ChangeAnimation(DirStr[j]);
			}
		}
	}
}

void Water::Start()
{
	CreateRenderer("Bomb\\water", "Main", RenderOrder::Water, true, {0, 0}, {8, 5});
	FindRenderer("Main")->CreateAnimation("Mid", 0, 0, 3, Duration / 8, true);
	FindRenderer("Main")->CreateAnimation("Up", 0, 1, 8, Duration / 8, false);
	FindRenderer("Main")->CreateAnimation("Down", 0, 2, 8, Duration / 8, false);
	FindRenderer("Main")->CreateAnimation("Left", 0, 3, 8, Duration / 8, false);
	FindRenderer("Main")->CreateAnimation("Right", 0, 4, 8, Duration / 8, false);

	FindRenderer("Main")->ChangeAnimation("Mid");
}

void Water::Update(float _Delta)
{
	if (LiveTime >= Duration)
	{
		Death();
	}
}

void Water::Render()
{
	DrawRect(Pos, TileSize);
}