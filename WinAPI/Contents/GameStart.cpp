#include "GameStart.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

GameStart::GameStart()
{
}

GameStart::~GameStart()
{
}

void GameStart::Start()
{
	Pos = GameEngineWindow::GetPos();

	CreateRenderer("G.bmp", RenderOrder::UI_GameStart);
	FindRenderer("G.bmp")->AddPos({ -176, -45 - Pos.Y });
	CreateRenderer("A.bmp", RenderOrder::UI_GameStart);
	FindRenderer("A.bmp")->AddPos({ -112, -45 - Pos.Y });
	CreateRenderer("M.bmp", RenderOrder::UI_GameStart);
	FindRenderer("M.bmp")->AddPos({ -47, -45 - Pos.Y });
	CreateRenderer("E.bmp", RenderOrder::UI_GameStart);
	FindRenderer("E.bmp")->AddPos({ 16, -45 - Pos.Y });

	CreateRenderer("S.bmp", RenderOrder::UI_GameStart);
	FindRenderer("S.bmp")->AddPos({ -267, 25 });
	FindRenderer("S.bmp")->AddScale({ -3.33f, -10 });
	FindRenderer("S.bmp")->Off();
	CreateRenderer("T.bmp", RenderOrder::UI_GameStart);
	FindRenderer("T.bmp")->AddPos({ -202, 25 });
	FindRenderer("T.bmp")->AddScale({ -3.33f, -10 });
	FindRenderer("T.bmp")->Off();
	CreateRenderer("A1.bmp", RenderOrder::UI_GameStart);
	FindRenderer("A1.bmp")->AddPos({ -135, 25 });
	FindRenderer("A1.bmp")->AddScale({ -3.33f, -10 });
	FindRenderer("A1.bmp")->Off();
	CreateRenderer("R.bmp", RenderOrder::UI_GameStart);
	FindRenderer("R.bmp")->AddPos({ -43, 25 });
	FindRenderer("R.bmp")->AddScale({ -3.33f, -10 });
	FindRenderer("R.bmp")->Off();
	CreateRenderer("T1.bmp", RenderOrder::UI_GameStart);
	FindRenderer("T1.bmp")->AddPos({ 39, 25 });
	FindRenderer("T1.bmp")->AddScale({ -3.33f, -10 });
	FindRenderer("T1.bmp")->Off();
	CreateRenderer("EM.bmp", RenderOrder::UI_GameStart);
	FindRenderer("EM.bmp")->AddPos({ 115, 25 });
	FindRenderer("EM.bmp")->AddScale({ -3.33f, -10 });
	FindRenderer("EM.bmp")->Off();
}

void GameStart::Update(float _Delta)
{
	if (LiveTime >= 4.0f)
	{
		return;
	}

	std::string Game[4] = { "G", "A", "M", "E" };
	std::string Start[6] = { "S", "T", "A1", "R", "T1", "EM" };
	if (LiveTime <= 0.8f)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (FindRenderer(Game[i] + ".bmp")->GetPos().Y < -45)
			{
				if (LiveTime >= 0.2f * i)
				{
					FindRenderer(Game[i] + ".bmp")->AddPos({ 0, 3200.0f * _Delta });
				}
			}
			else if (FindRenderer(Game[i] + ".bmp")->GetPos().Y > -45)
			{
				FindRenderer(Game[i] + ".bmp")->SetPos({ FindRenderer(Game[i] + ".bmp")->GetPos().X, -45 });
			}
		}
	}

	if (LiveTime >= 1.0f)
	{
		FindRenderer("S.bmp")->On();
		FindRenderer("T.bmp")->On();
		FindRenderer("A1.bmp")->On();
		FindRenderer("R.bmp")->On();
		FindRenderer("T1.bmp")->On();
		FindRenderer("EM.bmp")->On();
	}

	for (int i = 0; i < 6; ++i)
	{
		if (LiveTime >= 2.0f + 0.2f * i)
		{
			if (i <= 4 && i >= 1)
			{
				FindRenderer(Game[i - 1] + ".bmp")->AddPos({ 0, -3200.0f * _Delta });
			}
			FindRenderer(Start[i] + ".bmp")->AddPos({ 0, 3200.0f * _Delta });
		}
	}

	if (FindRenderer("EM.bmp")->GetPos().Y >= 900)
	{
		Death();
	}
}
