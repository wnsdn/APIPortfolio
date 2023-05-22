#include "BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Init(const std::string& _Path)
{
	Pos = GameEngineWindow::GetInst().GetScale().Half();

	CreateRenderer(_Path, "Main", RenderOrder::BackGround, false);
	FindRenderer("Main")->SetRenderScale(GameEngineWindow::GetInst().GetScale());
}
