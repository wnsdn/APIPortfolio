#include "Cursor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

void Cursor::Start()
{
	Pos = GameEngineWindow::GetInst().GetMousePos();

	CreateRenderer("Cursor.bmp", ZOrder::UI_Cursor, RenderOrder::None, {}, { 2, 1 });
	FindRenderer("Cursor.bmp")->CreateAnimation("NotClick", 0, 0, 1, 0.f, false);
	FindRenderer("Cursor.bmp")->CreateAnimation("Click", 1, 0, 1, 0.f, false);
	FindRenderer("Cursor.bmp")->ChangeAnimation("NotClick");
	FindRenderer("Cursor.bmp")->AddPos({ 14, 17 });

	Scale = FindRenderer("Cursor.bmp")->GetScale();
}

void Cursor::Update(float _Delta)
{
	Pos = GameEngineWindow::GetInst().GetMousePos();

	if (GameEngineInput::IsPress(VK_LBUTTON))
	{
		FindRenderer("Cursor.bmp")->ChangeAnimation("Click");
	}
	else
	{
		FindRenderer("Cursor.bmp")->ChangeAnimation("NotClick");
	}
}
