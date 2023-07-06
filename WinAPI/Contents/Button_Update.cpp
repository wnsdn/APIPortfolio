#include "Button.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>


void Button::ActiveUpdate(float _Delta)
{
	float4 Pt = GameEngineWindow::GetInst().GetMousePos();

	if (Pt.X > Left() && Pt.X < Right() &&
		Pt.Y > Top() && Pt.Y < Bottom())
	{
		if (!IsMouseOnButton)
		{
			GameEngineSound::FindSound("ButtonOn.wav")->Play();
			FindRenderer(Main)->ChangeAnimation("Before");
			IsMouseOnButton = true;
		}

		if (GameEngineInput::IsDown(VK_LBUTTON) && !IsClick)
		{
			GameEngineSound::FindSound("ButtonClick.wav")->Play();
			LiveTime = 0.f;
			IsClick = true;
		}
	}
	else
	{
		IsMouseOnButton = false;
		FindRenderer(Main)->ChangeAnimation("After");
	}
}

void Button::ClickUpdate(float _Delta)
{
	float4 Pt = GameEngineWindow::GetInst().GetMousePos();

	if (Pt.X > Left() && Pt.X < Right() &&
		Pt.Y > Top() && Pt.Y < Bottom())
	{
		if (!IsMouseOnButton)
		{
			GameEngineSound::FindSound("ButtonOn.wav")->Play();
			IsMouseOnButton = true;
		}

		if (GameEngineInput::IsDown(VK_LBUTTON) && !IsClick)
		{
			GameEngineSound::FindSound("ButtonClick.wav")->Play();
			FindRenderer(Main)->ChangeAnimation("After");
			LiveTime = 0.f;
			IsClick = true;
		}
		if (GameEngineInput::IsUp(VK_LBUTTON))
		{
			FindRenderer(Main)->ChangeAnimation("Before");
		}
	}
	else
	{
		IsMouseOnButton = false;
		FindRenderer(Main)->ChangeAnimation("Before");
	}
}