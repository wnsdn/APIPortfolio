#include "MonsterLevel.h"
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
#include "UIFrame.h"
#include "Button.h"
#include "Cursor.h"
#include "Curtain.h"
#include "GameStart.h"
#include "GameResult.h"

#include "ReadMapData.h"

MonsterLevel::MonsterLevel()
{
}

MonsterLevel::~MonsterLevel()
{
}

void MonsterLevel::Init(const std::string& _MapData)
{
	ReadMapData Rmd("test.txt", this);

	CreateActor<UIFrame>(UpdateOrder::UI)->Init("Frame.bmp");

	GameEngineSound::CreateSound("Octopus.mp3", true);
	GameEngineSound::FindSound("Octopus.mp3")->Play();
}

void MonsterLevel::Start()
{
	State = "Start";

	float4 WindowPos = GameEngineWindow::GetPos();
	float4 WindowScale = GameEngineWindow::GetScale();

	//Camera ZOrder Setting
	Camera->Init(RenderOrder::InGameObject, RenderOrder::InGameObjectEnd);

	//UI
	BtnOut = CreateActor<Button>(UpdateOrder::UI);//Button
	BtnOut->Init("InGameOut.bmp", { 752, 606 }, false);
	CreateActor<Cursor>(UpdateOrder::UI);//Cursor
	CurtainPtr = CreateActor<Curtain>(UpdateOrder::UI);//Curtain
	CreateActor<GameStart>(UpdateOrder::UI);//GameStart

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
