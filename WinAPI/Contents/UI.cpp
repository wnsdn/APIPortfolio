#include "UI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Start()
{
	CreateBackUIRenderer("UI\\Frame", "Frame", RenderOrder::UI, false);
	FindRenderer("Frame")->SetRenderPos(GameEngineWindow::GetInst().GetScale().Half());
	FindRenderer("Frame")->SetRenderScale(GameEngineWindow::GetInst().GetScale());
}
