#include "MonsterLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Global.h"

#include "BackGround.h"
#include "Tile.h"
#include "Player.h"
#include "Monster.h"
#include "Bomb.h"
#include "Water.h"
#include "Block.h"
#include "Item.h"

MonsterLevel::MonsterLevel()
{
}

MonsterLevel::~MonsterLevel()
{
}

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>

void MonsterLevel::ReadMapData()
{
	
}

void MonsterLevel::Start()
{
	BackGround* BackGroundPtr = CreateActor<BackGround>(UpdateOrder::None);
	BackGroundPtr->Init("UI\\Frame");

	Tile* TilePtr = nullptr;
	for (int Y = 0; Y < 13; ++Y)
	{
		for (int X = 0; X < 15; ++X)
		{
			TilePtr = CreateActor<Tile>(UpdateOrder::Tile);
			TilePtr->Init({ X, Y }, { 6, 3 });
		}
	}

	std::filesystem::path Path = GameEnginePath::GetPath("MapData", "Octopus1.txt");
	std::ifstream Read(Path);
	//std::string Str[15][13] = {};

	if (Read)
	{
		Block* BlockPtr = nullptr;
		for (int Y = 0; Y < 13; ++Y)
		{
			for (int X = 0; X < 15; ++X)
			{
				//Block* BlockPtr = CreateActor<Block>(UpdateOrder::Block);
				//BlockPtr->Init({ X, Y }, "1x1_1", { 0, 8 });

				/*Read >> Str[Y][X];

				std::istringstream Stream(Str[Y][X]);
				std::string Buffer = "";
				std::vector<float> Result;
				while (std::getline(Stream, Buffer, ','))
				{
					if (Buffer == "0")
					{
						continue;
					}

					Result.push_back(std::stof(Buffer, nullptr));
				}

				BlockPtr = CreateActor<Block>(UpdateOrder::Block);
				if (Result.size())
				{
					BlockPtr->Init({ X, Y }, "1x1_1", { Result[0], Result[1] });
				}*/
			}
		}
	}
	else
	{
		MsgBoxAssert(Path.string() + " ReadMapData()");
	}
	/*Block* BlockPtr = CreateActor<Block>(UpdateOrder::Block);
	BlockPtr->Init({ 2, 2 }, "1x1_1", { 0, 8 });*/

	Player* PlayerPtr = CreateActor<Player>(UpdateOrder::Player);
	PlayerPtr->Init({ 5, 3 }, "Player\\Bazzi");

	Monster* MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 10, 10 }, "Monster\\Octopus1");

	Item* ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 5, 7 }, { 3, 2 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 6, 7 }, { 4, 2 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 7, 7 }, { 5, 2 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 8, 7 }, { 0, 3 });
}

void MonsterLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('R'))
	{
		if (IsActorRender)
		{
			IsActorRender = false;
		}
		else
		{
			IsActorRender = true;
		}
	}
}
