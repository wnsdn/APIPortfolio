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
	Pos = GameEngineWindow::GetPos();
	Scale = GameEngineWindow::GetScale();

	CreateRenderer(_Path, RenderOrder::BackGround);
	FindRenderer(_Path)->SetScale(Scale);

	InsertRenderer();
}
