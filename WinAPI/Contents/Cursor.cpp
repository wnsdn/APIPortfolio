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

	CreateRenderer("Cursor.bmp", RenderOrder::UI_Cursor, {}, { 2, 1 });
	FindRenderer("Cursor.bmp")->CreateAnimation("NotClick", 0, 0, 1, 0.f, false);
	FindRenderer("Cursor.bmp")->CreateAnimation("Click", 1, 0, 1, 0.f, false);
	FindRenderer("Cursor.bmp")->ChangeAnimation("NotClick");
	FindRenderer("Cursor.bmp")->AddPos({ 14, 17 });

	//CreateTextRenderer("MousePos", RenderOrder::Text);

	Scale = FindRenderer("Cursor.bmp")->GetScale();
	InsertRenderer();

	ShowCursor(false);
	IsCursorOn = false;
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

	if (Pos.Y <= 0)
	{
		/*FindRenderer("MousePos")->On();
		FindRenderer("MousePos")->SetText(std::to_string(Pos.X) + ", " + std::to_string(Pos.Y), 15);*/
		SetPos({ Pos.X, 0 });
		if (!IsCursorOn)
		{
			ShowCursor(true);
			IsCursorOn = true;
		}
	}

	if (Pos.Y > 0)
	{
		//FindRenderer("MousePos")->Off();
		if (IsCursorOn)
		{
			ShowCursor(false);
			IsCursorOn = false;
		}
	}
}
