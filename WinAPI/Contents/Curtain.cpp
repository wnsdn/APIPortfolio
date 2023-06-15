#include "Curtain.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

Curtain::Curtain()
{
}

Curtain::~Curtain()
{
}

void Curtain::Start()
{
	Pos = GameEngineWindow::GetPos();
	Scale = GameEngineWindow::GetScale();

	CreateRenderer("Black", ZOrder::UI_Curtain, RenderOrder::None, Scale, RGB(0, 0, 0));
	FindRenderer("Black")->SetAlphaRender(true);
}

void Curtain::Reset()
{
	Dark = 0.0f;
	Bright = 255.0f;
	FindRenderer("Black")->SetAlphaValue(static_cast<unsigned char>(0));
}

void Curtain::SetDark(float _Delta, float _Time)
{
	if (Dark < 255.0f)
	{
		Dark += 255.0f / _Time * _Delta;

		if (Dark > 255.0f)
		{
			Dark = 255.0f;
		}

		FindRenderer("Black")->SetAlphaValue(static_cast<unsigned char>(Dark));
	}
}

void Curtain::SetBright(float _Delta, float _Time, float Min)
{
	if (Bright > 0.0f + Min)
	{
		Bright -= (255.0f - Min) / _Time * _Delta;

		if (Bright < 0.0f + Min)
		{
			Bright = 0.0f + Min;
		}

		FindRenderer("Black")->SetAlphaValue(static_cast<unsigned char>(Bright));
	}
}