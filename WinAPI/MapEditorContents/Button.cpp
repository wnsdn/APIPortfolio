#include "Button.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init(const float4& _Pos, const std::string& _Name, bool _IsToggle)
{
	Pos = _Pos;
	Scale = { 100, 40 };

	Name = _Name;
	IsToggle = _IsToggle;

	CreateTextRenderer(_Name, RenderOrder::Text);
	FindRenderer(_Name)->SetText(_Name, 20.0f, 2.0f, "±¼¸²");
	FindRenderer(_Name)->AddPos({ -25, -12 });

	InsertRenderer();
}

void Button::AddTextPos(const float4& _Pos)
{
	FindRenderer(Name)->AddPos(_Pos);
}

void Button::Update(float _Delta)
{
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();

	if (MousePos.X >= Left() && MousePos.X < Right() &&
		MousePos.Y >= Top() && MousePos.Y < Bottom())
	{
		if (GameEngineInput::IsPress(VK_LBUTTON))
		{
			if (!IsToggle)
			{
				G = 255;
				B = 0;
			}
		}
		else
		{
			G = 0;
			B = 255;
		}

		if (GameEngineInput::IsUp(VK_LBUTTON))
		{
			if (!IsToggle)
			{
				IsClick = true;
			}
			else
			{
				if (IsClick)
				{
					IsClick = false;
				}
				else
				{
					IsClick = true;
				}
			}
		}
		else
		{
			if (!IsToggle)
			{
				IsClick = false;
			}
		}
	}
	else
	{
		if (IsToggle)
		{
			if (IsClick)
			{
				G = 255;
			}
			else
			{
				G = 0;
			}
		}
		B = 0;
	}
}

void Button::Render(float _Delta)
{
	DrawRect(Pos, Scale, Rgb(R, G, B));
}