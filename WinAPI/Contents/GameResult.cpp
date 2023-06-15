#include "GameResult.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

GameResult::GameResult()
{
}

GameResult::~GameResult()
{
}

void GameResult::RendererOn()
{
	FindRenderer("GameResult.bmp")->On();
}

void GameResult::Start()
{
	Pos = GameEngineWindow::GetPos();

	AddPos({ -84, -22 });

	CreateRenderer("GameResult.bmp", ZOrder::UI_GameResult, RenderOrder::None);
	FindRenderer("GameResult.bmp")->SetAlphaRender(true);
	FindRenderer("GameResult.bmp")->SetAlphaValue(150);
	FindRenderer("GameResult.bmp")->Off();
}
