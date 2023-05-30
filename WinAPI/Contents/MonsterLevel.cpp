#include "MonsterLevel.h"
#include <fstream>
#include <sstream>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "Global.h"
#include "BackGround.h"
#include "Tile.h"
#include "Player.h"
#include "Monster.h"
#include "Bomb.h"
#include "Water.h"
#include "Block.h"
#include "Object.h"
#include "Item.h"
#include "UI.h"

MonsterLevel::MonsterLevel()
{
}

MonsterLevel::~MonsterLevel()
{
}

void MonsterLevel::Init(const std::string& _MapData)
{
	GameEngineSound::CreateSound("Bomb\\Set.mp3");
	GameEngineSound::CreateSound("Bomb\\Explode.wav");
	GameEngineSound::CreateSound("Item\\Get.mp3");

	UI* UIPtr = nullptr;
	UIPtr = CreateActor<UI>(UpdateOrder::UI);

	std::filesystem::path Path = GameEnginePath::GetPath("MapData", "Octopus1.txt");
	std::ifstream Read(Path);
	std::istringstream Stream;
	std::string Str = "";

	if (!Read)
	{
		MsgBoxAssert(Path.string() + " ReadMapData()");
		return;
	}

	Tile* TilePtr = nullptr;
	for (int Y = 0; Y < 13; ++Y)
	{
		for (int X = 0; X < 15; ++X)
		{
			TilePtr = CreateActor<Tile>(UpdateOrder::Tile);
			TilePtr->Init({ X, Y }, { 6, 3 });
		}
	}

	Block* BlockPtr = nullptr;
	std::getline(Read, Str);
	for (int Y = 0; Y < 13; ++Y)
	{
		std::getline(Read, Str);
		Stream.clear();
		Stream.str(Str);
		for (int X = 0; X < 15; ++X)
		{
			std::getline(Stream, Str, ' ');

			if (Str != "0")
			{
				BlockPtr = CreateActor<Block>(UpdateOrder::Block);
				BlockPtr->Init({ X, Y }, "1x1_1", { static_cast<float>(Str[0] - '0'), static_cast<float>(Str[2] - '0') });
			}
		}
	}

	Object* ObjectPtr = nullptr;
	std::getline(Read, Str);
	for (int Y = 0; Y < 13; ++Y)
	{
		std::getline(Read, Str);
		Stream.clear();
		Stream.str(Str);
		for (int X = 0; X < 15; ++X)
		{
			std::getline(Stream, Str, ' ');

			if (Str != "0")
			{
				ObjectPtr = CreateActor<Object>(UpdateOrder::Object);
				ObjectPtr->Init({ X, Y }, { static_cast<float>(Str[0] - '0'), static_cast<float>(Str[2] - '0') });
			}
		}
	}

	Player* PlayerPtr = CreateActor<Player>(UpdateOrder::Player);
	PlayerPtr->Init({ 12, 11 }, "Player\\Bazzi");

	Monster* MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 9, 6 }, "Monster\\Octopus1");
	MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 10, 6 }, "Monster\\Octopus1");
	 MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 11, 6 }, "Monster\\Octopus1");
	MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 12, 6 }, "Monster\\Octopus1");
	 MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 7, 1 }, "Monster\\Octopus2");
	MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 7, 11 }, "Monster\\Octopus2");

	Item* ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 6, 0 }, { 0, 3 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 7, 0 }, { 5, 2 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 8, 0 }, { 3, 2 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 6, 12 }, { 0, 3 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 7, 12 }, { 5, 2 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 8, 12 }, { 3, 2 });
}

void MonsterLevel::Update(float _Delta)
{
	GameEngineLevel::Update(_Delta);

	if (GameEngineInput::IsDown('R'))
	{
		if (IsDebugRender)
		{
			IsDebugRender = false;
		}
		else
		{
			IsDebugRender = true;
		}
	}
}
