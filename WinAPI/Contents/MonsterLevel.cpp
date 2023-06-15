#include "MonsterLevel.h"
#include <fstream>
#include <sstream>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineProcess.h>

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
#include "Button.h"
#include "Cursor.h"
#include "Curtain.h"
#include "GameStart.h"
#include "GameResult.h"

MonsterLevel::MonsterLevel()
{
}

MonsterLevel::~MonsterLevel()
{
}

void MonsterLevel::Init(const std::string& _MapData)
{
	/*std::filesystem::path Path = GameEnginePath::FilenameToPath(_MapData);
	std::ifstream Read(Path);
	std::istringstream Stream;
	std::string Str = "";

	if (!Read)
	{
		MsgBoxAssert(Path.string() + " ReadMapData()");
		return;
	}*/

	Tile* TilePtr = nullptr;
	for (int Y = 0; Y < 13; ++Y)
	{
		for (int X = 0; X < 15; ++X)
		{
			TilePtr = CreateActor<Tile>(UpdateOrder::Tile);
			TilePtr->Init({ X, Y }, { 6, 3 });
		}
	}

	/*Block* BlockPtr = nullptr;
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
				BlockPtr->Init({ X, Y }, "1x1_1.bmp", { static_cast<float>(Str[0] - '0'), static_cast<float>(Str[2] - '0') });
			}
		}
	}*/
	CreateActor<Block>(UpdateOrder::Block)->
		Init({ 0, 0 }, "1x1_1.bmp", { 4, 2 });
	CreateActor<Block>(UpdateOrder::Block)->
		Init({ 1, 0 }, "1x1_1.bmp", { 5, 4 });
	CreateActor<Block>(UpdateOrder::Block)->
		Init({ 2, 0 }, "1x1_1.bmp", { 4, 3 });
	CreateActor<Block>(UpdateOrder::Block)->
		Init({ 0, 1 }, "1x1_1.bmp", { 6, 4 });
	CreateActor<Block>(UpdateOrder::Block)->
		Init({ 0, 2 }, "1x1_1.bmp", { 4, 8 });
	CreateActor<Block>(UpdateOrder::Block)->
		Init({ 0, 3 }, "1x1_1.bmp", { 8, 4 });

	CreateActor<Object>(UpdateOrder::Object)->
		Init({ 3, 0 }, { 9, 4 });
	CreateActor<Object>(UpdateOrder::Object)->
		Init({ 3, 1 }, { 9, 4 });
	CreateActor<Object>(UpdateOrder::Object)->
		Init({ 3, 2 }, { 9, 4 });
	CreateActor<Object>(UpdateOrder::Object)->
		Init({ 3, 3 }, { 8, 4 });
	CreateActor<Object>(UpdateOrder::Object)->
		Init({ 3, 4 }, { 8, 4 });
	CreateActor<Object>(UpdateOrder::Object)->
		Init({ 7, 7 }, { 0, 3 });

	/*Object* ObjectPtr = nullptr;
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
	}*/

	Player::MainPlayer = CreateActor<Player>(UpdateOrder::Player);
	Player::MainPlayer->Init({ 12, 11 }, "Bazzi.bmp");

	Monster* MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 9, 6 }, "Octopus1.bmp");
	/*MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 10, 6 }, "Octopus1.bmp");
	MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 11, 6 }, "Octopus1.bmp");
	MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 12, 6 }, "Octopus1.bmp");
	MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 7, 1 }, "Octopus2.bmp");
	MonsterPtr = CreateActor<Monster>(UpdateOrder::Monster);
	MonsterPtr->Init({ 7, 11 }, "Octopus2.bmp");*/

	Item* ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 6, 0 }, { 2, 0 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 7, 0 }, { 1, 0 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 8, 0 }, { 0, 0 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 6, 12 }, { 2, 0 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 7, 12 }, { 1, 0 });
	ItemPtr = CreateActor<Item>(UpdateOrder::Item);
	ItemPtr->Init({ 8, 12 }, { 0, 0 });

	GameEngineSound::CreateSound("Octopus.mp3");
	GameEngineSound::FindSound("Octopus.mp3")->Play();
}

void MonsterLevel::Start()
{
	State = "Start";

	float4 WindowPos = GameEngineWindow::GetPos();
	float4 WindowScale = GameEngineWindow::GetScale();

	//Camera ZOrder Setting
	Camera->Init(ZOrder::InGameObject, ZOrder::InGameObjectEnd);

	//UI
	UI* UIPtr = CreateActor<UI>(UpdateOrder::UI);//Frame
	UIPtr->Init("Frame.bmp", WindowPos, ZOrder::BackUI);
	UIPtr->SetRendererScale(WindowScale);
	BtnOut = CreateActor<Button>(UpdateOrder::UI);//Button
	BtnOut->Init("InGameOut.bmp", { 752, 606 }, false);
	CreateActor<Cursor>(UpdateOrder::UI);//Cursor
	CurtainPtr = CreateActor<Curtain>(UpdateOrder::UI);//Curtain
	CreateActor<GameStart>(UpdateOrder::UI);//GameStart
	ResultPtr = CreateActor<GameResult>(UpdateOrder::UI);//GameResult

	//Sound
	GameEngineSound::CreateSound("GameStart.mp3");
	GameEngineSound::CreateSound("GameWin.wav");
	GameEngineSound::CreateSound("GameLose.mp3");
	GameEngineSound::CreateSound("MonsterDeath.wav");
	GameEngineSound::CreateSound("PlayerDeath.wav");
	GameEngineSound::CreateSound("PlayerFree.wav");
	GameEngineSound::CreateSound("BombSet.mp3");
	GameEngineSound::CreateSound("BombExplode.wav");
	GameEngineSound::CreateSound("ItemGet.mp3");

	GameEngineSound::FindSound("GameStart.mp3")->Play();
}

void MonsterLevel::Update(float _Delta)
{
	LiveTime += _Delta;

	GameEngineLevel::Update(_Delta);

	StateUpdate(_Delta);
}
