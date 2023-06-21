#include "Menu.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Button.h"

void Menu::MenuRender()
{
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();

	if (MousePos.X >= CurRenderer->Left() && MousePos.X < CurRenderer->Right() &&
		MousePos.Y >= CurRenderer->Top() && MousePos.Y < CurRenderer->Bottom())
	{
		switch (State)
		{
		case static_cast<int>(MenuState::Tile):
			DrawRect(PosToIndexPos(MousePos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 40 }),
				{ 40, 40 }, Rgb(0, 0, 255));
			break;
		case static_cast<int>(MenuState::Block):
			DrawRect(PosToIndexPos(MousePos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 80 }),
				{ 40, 80 }, Rgb(0, 0, 255));
			break;
		case static_cast<int>(MenuState::Object):
			DrawRect(PosToIndexPos(MousePos, { CurRenderer->Left(), CurRenderer->Top() }, { 46, 80 }),
				{ 46, 80 }, Rgb(0, 0, 255));
			break;
		case static_cast<int>(MenuState::Item):
			DrawRect(PosToIndexPos(MousePos, { CurRenderer->Left(), CurRenderer->Top() }, { 38, 38 }),
				{ 38, 38 }, Rgb(0, 0, 255));
			break;
		case static_cast<int>(MenuState::Position):
			DrawRect(PosToIndexPos(MousePos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 40 }),
				{ 40, 40 }, Rgb(0, 0, 255));
			break;
		}
	}

	if (MenuIsClick)
	{
		switch (State)
		{
		case static_cast<int>(MenuState::Tile):
			DrawRect(PosToIndexPos(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 40 }),
				{ 40, 40 }, Rgb(0, 255, 0));
			break;
		case static_cast<int>(MenuState::Block):
			DrawRect(PosToIndexPos(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 80 }),
				{ 40, 80 }, Rgb(0, 255, 0));
			break;
		case static_cast<int>(MenuState::Object):
			DrawRect(PosToIndexPos(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 46, 80 }),
				{ 46, 80 }, Rgb(0, 255, 0));
			break;
		case static_cast<int>(MenuState::Item):
			DrawRect(PosToIndexPos(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 38, 38 }),
				{ 38, 38 }, Rgb(0, 255, 0));
			break;
		case static_cast<int>(MenuState::Position):
			DrawRect(PosToIndexPos(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 40 }),
				{ 40, 40 }, Rgb(0, 255, 0));
			break;
		}
	}

}

void Menu::GridRender()
{
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();

	if (BtnGrid->IsClick)
	{
		for (float x = 0; x < 16; ++x)
		{
			DrawLine({ 42 * x, 0 }, { 42 * x, 42 * 13 });
		}
		for (float y = 0; y < 14; ++y)
		{
			DrawLine({ 0, 42 * y }, { 42 * 15, 42 * y });
		}
	}

	if (MousePos.X >= 0 && MousePos.X < 42 * 15 &&
		MousePos.Y >= 0 && MousePos.Y < 42 * 13)
	{
		DrawRect(PosToIndexPos(MousePos, {}, { 42, 42 }),
			{ 42, 42 }, Rgb(R, G, B));
	}
}
