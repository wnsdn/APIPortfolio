#include "GameResultText.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

GameResultText::GameResultText()
{
}

GameResultText::~GameResultText()
{
}

void GameResultText::Init(bool _Win)
{
	Pos = GameEngineWindow::GetPos();

	if (_Win)
	{
		CreateRenderer("Win.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ -215, -233 - Pos.Y });
		CreateRenderer("Win_W.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ -215, -233 - Pos.Y });
		CreateRenderer("Win_I.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ -141, -233 - Pos.Y });
		CreateRenderer("Win_N.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ -69, -233 - Pos.Y });
		CreateRenderer("Win_!.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ 0, -233 - Pos.Y });

		State = "Win_";
	}
	else
	{
		CreateRenderer("Lose_L.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ -215, -233 - Pos.Y });
		CreateRenderer("Lose_O.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ -141, -233 - Pos.Y });
		CreateRenderer("Lose_S.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ -69, -233 - Pos.Y });
		CreateRenderer("Lose_E.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ 0, -233 - Pos.Y });
		CreateRenderer("Lose_!.bmp", RenderOrder::UI_Text, {}, { 2, 1 })->
			AddPos({ 65, -233 - Pos.Y });

		State = "Lose_";
	}

	InsertRenderer();
}

void GameResultText::Start()
{
}

void GameResultText::Update(float _Delta)
{
	std::string Result{};
	if (State == "Win_")
	{
		Result = "WIN!";
	}
	else
	{
		Result = "LOSE!";
	}
	int Size = static_cast<int>(Result.size());

	if (LiveTime <= 0.12f * Size)
	{
		for (int i = 0; i < Size; ++i)
		{
			std::string Path = State;
			Path += Result[i];
			Path += ".bmp";
			if (FindRenderer(Path)->GetPos().Y < -233)
			{
				if (LiveTime >= 0.12f * i)
				{
					FindRenderer(Path)->AddPos({ 0, Speed * _Delta });
				}
			}
			else if (FindRenderer(Path)->GetPos().Y > -233)
			{
				FindRenderer(Path)->SetPos({ FindRenderer(Path)->GetPos().X, -233 });
			}
		}
	}
	else
	{
		if (Count >= Size)
		{
			return;
		}

		Timer += _Delta;

		if (Timer <= 0.1f)
		{
			for (int i = 0; i < Size; ++i)
			{
				std::string Path = State;
				Path += Result[i];
				Path += ".bmp";
				FindRenderer(Path)->SetCopyPos({ 1, 0 });
			}
		}
		else if (Timer <= 0.2f)
		{
			for (int i = 0; i < Size; ++i)
			{
				std::string Path = State;
				Path += Result[i];
				Path += ".bmp";
				FindRenderer(Path)->SetCopyPos({ 0, 0 });
			}
		}
		else
		{
			Timer = 0.0f;
			++Count;
		}
	}
}
