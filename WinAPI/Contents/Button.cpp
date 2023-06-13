#include "Button.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init(const std::string& _Path, const float4& _Pos, bool _IsActive, float _Time)
{
	Main = _Path;

	Pos = _Pos;
	IsActiveButton = _IsActive;
	Time = _Time;

	CreateRenderer(_Path, RenderOrder::FrontUI, {}, { 2, 1 });
	FindRenderer(_Path)->CreateAnimation("Before", 0, 0, 1, 0.f, false);
	FindRenderer(_Path)->CreateAnimation("After", 1, 0, 1, 0.f, false);

	if (IsActiveButton)
	{
		FindRenderer(_Path)->ChangeAnimation("After");
	}
	else
	{
		FindRenderer(_Path)->ChangeAnimation("Before");
	}

	Scale = FindRenderer(_Path)->GetScale();
}

void Button::Update(float _Delta)
{
	if (IsActiveButton)
	{
		ActiveUpdate(_Delta);
	}
	else
	{
		ClickUpdate(_Delta);
	}
}

void Button::Reset()
{
	IsMouseOnButton = false;
	IsClick = false;
}