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

	Block* BlockPtr = CreateActor<Block>(UpdateOrder::Block);
	BlockPtr->Init({ 2, 2 }, "1x1_1", { 0, 8 });

	Player* PlayerPtr = CreateActor<Player>(UpdateOrder::Player);
	PlayerPtr->Init({ 5, 3 }, "Player\\Bazzi");

	Monster* MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 10, 10 }, "Monster\\Octopus1");

	Item* ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 5, 7 }, "Item\\item_61");
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
