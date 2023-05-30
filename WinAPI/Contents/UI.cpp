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
	CreateUIRenderer("UI\\Frame", "Frame", RenderOrder::BackUI, false);
	FindRenderer("Frame")->SetRenderPos(GameEngineWindow::GetInst().GetScale().Half());
	FindRenderer("Frame")->SetRenderScale(GameEngineWindow::GetInst().GetScale());
}
