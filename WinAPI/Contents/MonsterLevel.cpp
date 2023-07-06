#include "MonsterLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineProcess.h>

#include "Global.h"
#include "BackGround.h"
#include "Tile.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterBoss.h"
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
#include <format>

MonsterLevel::MonsterLevel()
{
}

MonsterLevel::~MonsterLevel()
{
}

void MonsterLevel::Init(const std::string& _MapData)
{
	ReadMapData Rmd;
	Rmd.Read(_MapData, this);
	CurMap = _MapData;

	if (CurMap == "Octopus.txt" || CurMap == "Octopus1.txt")
	{
		GameEngineSound::CreateSound("Octopus.mp3", true);
		GameEngineSound::FindSound("Octopus.mp3")->Play();
	}
	else if (CurMap == "Boss.txt")
	{
		GameEngineSound::CreateSound("BossStart.wav", true);
		GameEngineSound::FindSound("BossStart.wav")->Play();
	}
	else if (CurMap == "test.txt")
	{
		GameEngineSound::CreateSound("Patrit.mp3", true);
		GameEngineSound::FindSound("Patrit.mp3")->Play();
	}

	Player::MainPlayer->ReadData();
}

void MonsterLevel::Start()
{
	Player::MainPlayer = CreateActor<Player>(UpdateOrder::Player);
	Monster::SetCount(0);

	State = "Start";

	float4 WindowPos = GameEngineWindow::GetPos();
	float4 WindowScale = GameEngineWindow::GetScale();

	//Camera ZOrder Setting
	Camera->Init(RenderOrder::InGameObject, RenderOrder::InGameObjectEnd);

	//UI
	FramePtr = CreateActor<UIFrame>(UpdateOrder::UI);
	FramePtr->Init("Frame.bmp");
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
	GameEngineSound::CreateSound("BossDeath.mp3");
	GameEngineSound::CreateSound("BossHit.mp3");
	GameEngineSound::CreateSound("PlayerDeath.wav");
	GameEngineSound::CreateSound("PlayerFree.wav");
	GameEngineSound::CreateSound("PlayerKick.mp3");
	GameEngineSound::CreateSound("PlayerThrow.mp3");
	GameEngineSound::CreateSound("PlayerJump.mp3");
	GameEngineSound::CreateSound("PlayerShield.wav");
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

	if (GameEngineInput::IsDown('Q'))
	{
		if (LevelRender)
		{
			LevelRender = false;
		}
		else
		{
			LevelRender = true;
		}
	}
	if (GameEngineInput::IsDown('W'))
	{
		for (auto MonPtr : FindActor(UpdateOrder::Monster))
		{
			dynamic_cast<Monster*>(MonPtr)->Kill();
		}

		for (auto BossPtr : FindActor(UpdateOrder::Boss))
		{
			GameEngineSound::FindSound("BossDeath.mp3")->Play();
			Monster::AddCount(-1);
			dynamic_cast<MonsterBoss*>(BossPtr)->SetState("Death");
			Player::MainPlayer->AddCurExp(111);
		}
	}
}

void MonsterLevel::Render(float _Delta)
{
	GameEngineLevel::Render(_Delta);

	if (LevelRender)
	{
		HDC Hdc = GameEngineWindow::GetInst().GetBackBuffer()->GetImageDC();
		std::string Buffer{std::format("Monster : {}", Monster::GetCount())};
		TextOut(Hdc, 2, 2, &Buffer[0], static_cast<int>(Buffer.size()));

		if (Player::MainPlayer->GetGodMode())
		{
			Buffer = "GodMode : True";
		}
		else
		{
			Buffer = "GodMode : False";
		}
		TextOut(Hdc, 2, 22, &Buffer[0], static_cast<int>(Buffer.size()));

		Buffer.clear();
		std::format_to(std::back_inserter(Buffer), "Bomb Count : {}", Player::MainPlayer->GetCount());
		TextOut(Hdc, 2, 42, &Buffer[0], static_cast<int>(Buffer.size()));

		Buffer.clear();
		std::format_to(std::back_inserter(Buffer), "Bomb Length : {}", Player::MainPlayer->GetLength());
		TextOut(Hdc, 2, 62, &Buffer[0], static_cast<int>(Buffer.size()));

		Buffer.clear();
		std::format_to(std::back_inserter(Buffer), "Bomb Speed : {}", Player::MainPlayer->GetSpeed());
		TextOut(Hdc, 2, 82, &Buffer[0], static_cast<int>(Buffer.size()));

		Buffer.clear();
		std::format_to(std::back_inserter(Buffer), "Needle : {}", Player::MainPlayer->GetItemNeedle());
		TextOut(Hdc, 2, 102, &Buffer[0], static_cast<int>(Buffer.size()));
		Buffer.clear();
		std::format_to(std::back_inserter(Buffer), "Shield : {}", Player::MainPlayer->GetItemShield());
		TextOut(Hdc, 2, 122, &Buffer[0], static_cast<int>(Buffer.size()));
		Buffer.clear();
		std::format_to(std::back_inserter(Buffer), "Jump : {}", Player::MainPlayer->GetItemJump());
		TextOut(Hdc, 2, 142, &Buffer[0], static_cast<int>(Buffer.size()));

		if (Player::MainPlayer->GetCanKick())
		{
			Buffer = "CanKick : True";
		}
		else
		{
			Buffer = "CanKick : False";
		}
		TextOut(Hdc, 2, 162, &Buffer[0], static_cast<int>(Buffer.size()));

		if (Player::MainPlayer->GetCanThrow())
		{
			Buffer = "CanThrow : True";
		}
		else
		{
			Buffer = "CanThrow : False";
		}
		TextOut(Hdc, 2, 182, &Buffer[0], static_cast<int>(Buffer.size()));
	}
}
