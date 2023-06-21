#include "Menu.h"
#include <format>
#include <fstream>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "ReadMapData.h"
#include "Global.h"
#include "Tile.h"
#include "Button.h"

void Menu::MenuUpdate()
{
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();
	std::string Buffer{};

	switch (State)
	{
	case static_cast<int>(MenuState::Tile):
		CurRenderer = FindRenderer("Tile1x1.bmp");
		FindRenderer("Tile1x1.bmp")->On();
		break;
	case static_cast<int>(MenuState::Block):
		CurRenderer = FindRenderer("1x1_1.bmp");
		FindRenderer("1x1_1.bmp")->On();
		break;
	case static_cast<int>(MenuState::Object):
		CurRenderer = FindRenderer("Object.bmp");
		FindRenderer("Object.bmp")->On();
		break;
	case static_cast<int>(MenuState::Item):
		CurRenderer = FindRenderer("Item.bmp");
		FindRenderer("Item.bmp")->On();
		break;
	case static_cast<int>(MenuState::Position):
		CurRenderer = FindRenderer("Position.bmp");
		FindRenderer("Position.bmp")->On();
		break;
	}

	if (MousePos.X >= CurRenderer->Left() && MousePos.X < CurRenderer->Right() &&
		MousePos.Y >= CurRenderer->Top() && MousePos.Y < CurRenderer->Bottom())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			SelectPos = MousePos;
			MenuIsClick = true;
			Erase->IsClick = false;

			switch (State)
			{
			case static_cast<int>(MenuState::Tile):
				SelectIndex = PosToIndex(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 40 });
				break;
			case static_cast<int>(MenuState::Block):
				SelectIndex = PosToIndex(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 80 });
				break;
			case static_cast<int>(MenuState::Object):
				SelectIndex = PosToIndex(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 46, 80 });
				break;
			case static_cast<int>(MenuState::Item):
				SelectIndex = PosToIndex(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 38, 38 });
				break;
			case static_cast<int>(MenuState::Position):
				SelectIndex = PosToIndex(SelectPos, { CurRenderer->Left(), CurRenderer->Top() }, { 40, 40 });
				break;
			}
		}
	}
}

void Menu::GridUpdate()
{
	float4 MousePos = GameEngineWindow::GetInst().GetMousePos();

	if (MousePos.X >= 0 && MousePos.X < 42 * 15 &&
		MousePos.Y >= 0 && MousePos.Y < 42 * 13)
	{
		int2 Pt = PosToIndex(MousePos, {}, { 42, 42 });
		if (State != static_cast<int>(MenuState::Tile) &&
			Tile::TileArr[Pt.Y][Pt.X]->Attr[static_cast<int>(MenuState::Block)].IsSet ||
			Tile::TileArr[Pt.Y][Pt.X]->Attr[static_cast<int>(MenuState::Object)].IsSet ||
			Tile::TileArr[Pt.Y][Pt.X]->Attr[static_cast<int>(MenuState::Item)].IsSet ||
			Tile::TileArr[Pt.Y][Pt.X]->Attr[static_cast<int>(MenuState::Position)].IsSet)
		{
			R = 255;
			G = 0;
			B = 0;
		}
		else
		{
			R = 0;
			G = 0;
			B = 255;
		}

		if (GameEngineInput::IsPress(VK_LBUTTON))
		{
			if (MenuIsClick)
			{
				if (State == static_cast<int>(MenuState::Tile))
				{
					if (Paint->IsClick)
					{
						for (int y = 0; y < 13; ++y)
						{
							for (int x = 0; x < 15; ++x)
							{
								Tile::TileArr[y][x]->Attr[0].Idx = SelectIndex;
								Tile::TileArr[y][x]->Attr[0].IsSet = true;
								Tile::TileArr[y][x]->Renderer[0]->On();
							}
						}

						Paint->IsClick = false;
					}
					else
					{
						Tile::TileArr[Pt.Y][Pt.X]->Attr[State].Idx = SelectIndex;
						Tile::TileArr[Pt.Y][Pt.X]->Attr[State].IsSet = true;
						Tile::TileArr[Pt.Y][Pt.X]->Renderer[State]->On();
					}
				}
				else if (State != static_cast<int>(MenuState::Tile))
				{
					if (!Tile::TileArr[Pt.Y][Pt.X]->Attr[static_cast<int>(MenuState::Block)].IsSet &&
						!Tile::TileArr[Pt.Y][Pt.X]->Attr[static_cast<int>(MenuState::Object)].IsSet &&
						!Tile::TileArr[Pt.Y][Pt.X]->Attr[static_cast<int>(MenuState::Item)].IsSet &&
						!Tile::TileArr[Pt.Y][Pt.X]->Attr[static_cast<int>(MenuState::Position)].IsSet)
					{
						Tile::TileArr[Pt.Y][Pt.X]->Attr[State].Idx = SelectIndex;
						Tile::TileArr[Pt.Y][Pt.X]->Attr[State].IsSet = true;
						Tile::TileArr[Pt.Y][Pt.X]->Renderer[State]->On();
					}
				}
			}
			else if (Erase->IsClick)
			{
				Tile::TileArr[Pt.Y][Pt.X]->Attr[State].Idx = { 0,0 };
				Tile::TileArr[Pt.Y][Pt.X]->Attr[State].IsSet = false;
				Tile::TileArr[Pt.Y][Pt.X]->Renderer[State]->Off();
			}
		}
	}
}

void Menu::ButtonUpdate()
{
	if (Prev->IsClick)
	{
		if (State != static_cast<int>(MenuState::Tile))
		{
			--State;
		}
		else
		{
			State = static_cast<int>(MenuState::Position);
		}

		CurRenderer->Off();
		MenuIsClick = false;
	}
	if (Next->IsClick)
	{
		if (State != static_cast<int>(MenuState::Position))
		{
			++State;
		}
		else
		{
			State = static_cast<int>(MenuState::Tile);
		}

		CurRenderer->Off();
		MenuIsClick = false;
	}
	if (Erase->IsClick)
	{
		MenuIsClick = false;
	}
	if (EraseAll->IsClick)
	{
		for (int y = 0; y < 13; ++y)
		{
			for (int x = 0; x < 15; ++x)
			{
				for (int i = 0; i < 5; ++i)
				{
					Tile::TileArr[y][x]->Attr[i].Idx.X = 0;
					Tile::TileArr[y][x]->Attr[i].Idx.Y = 0;
					Tile::TileArr[y][x]->Attr[i].IsSet = false;
					Tile::TileArr[y][x]->Renderer[i]->Off();
				}
			}
		}

		EraseAll->IsClick = false;
	}
	if (Save->IsClick)
	{
		std::string Filename;
		Filename.resize(256);
		std::string InitialPath = GameEnginePath::FilenameToPath("MapData");

		OPENFILENAMEA OFN{};
		OFN.lStructSize = sizeof(OPENFILENAMEA);
		OFN.hwndOwner = GameEngineWindow::GetInst().GetHwnd();
		OFN.nMaxFile = static_cast<DWORD>(Filename.size());
		OFN.lpstrDefExt = "txt";
		OFN.lpstrFile = &Filename[0];
		OFN.lpstrFilter = "Text (*.txt)\0*.txt\0";
		OFN.lpstrInitialDir = InitialPath.c_str();

		OFN.lpstrTitle = "Save MapData";
		OFN.Flags = OFN_OVERWRITEPROMPT;

		if (GetSaveFileNameA(&OFN))
		{
			std::ofstream Ofs(Filename);

			for (int y = 0; y < 13; ++y)
			{
				for (int x = 0; x < 15; ++x)
				{
					Tile* TilePtr = Tile::TileArr[y][x];
					for (int i = 0; i < 5; ++i)
					{
						if (TilePtr->Attr[i].IsSet)
						{
							std::string WriteForm{std::format("{},{} ", TilePtr->Attr[i].Idx.X, TilePtr->Attr[i].Idx.Y)};
							Ofs.write(&WriteForm[0], WriteForm.size());
						}
						else
						{
							Ofs.put('0');
							Ofs.put(' ');
						}
					}
					Ofs.put('\n');
				}
			}
		}

		Save->IsClick = false;
	}
	if (Open->IsClick)
	{
		std::string Filename;
		Filename.resize(256);
		std::string InitialPath = GameEnginePath::FilenameToPath("MapData");

		OPENFILENAMEA OFN{};
		OFN.lStructSize = sizeof(OPENFILENAMEA);
		OFN.hwndOwner = GameEngineWindow::GetInst().GetHwnd();
		OFN.nMaxFile = static_cast<DWORD>(Filename.size());
		OFN.lpstrDefExt = "txt";
		OFN.lpstrFile = &Filename[0];
		OFN.lpstrFilter = "Text (*.txt)\0*.txt\0";
		OFN.lpstrInitialDir = InitialPath.c_str();

		OFN.lpstrTitle = "Open MapData";
		OFN.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

		if (GetOpenFileNameA(&OFN))
		{
			ReadMapData Rmd(Filename);
		}

		Open->IsClick = false;
	}
}
