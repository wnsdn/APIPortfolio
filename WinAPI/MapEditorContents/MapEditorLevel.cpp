#include "MapEditorLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Global.h"
#include "Menu.h"
#include "Tile.h"

MapEditorLevel::MapEditorLevel()
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::Start()
{
	Menu::MainMenu = CreateActor<Menu>(UpdateOrder::UI);

	for (float y = 0; y < 13; ++y)
	{
		for (float x = 0; x < 15; ++x)
		{
			Tile::TileArr[static_cast<int>(y)][static_cast<int>(x)] =
				CreateActor<Tile>(UpdateOrder::UI);
			Tile::TileArr[static_cast<int>(y)][static_cast<int>(x)]->
				Init({ 21 + x * 42, 21 + y * 42 });
		}
	}

	IsRender = true;
}
