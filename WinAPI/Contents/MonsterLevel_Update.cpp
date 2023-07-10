#include "MonsterLevel.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineProcess.h>

#include "Global.h"
#include "Button.h"
#include "Curtain.h"
#include "GameResult.h"

#include "Player.h"
#include "Monster.h"
#include "MonsterBoss.h"
#include "UIFrame.h"
#include "TitleLevel.h"

void MonsterLevel::CuratinUpdate(float _Delta)
{
	CurtainPtr->SetBright(_Delta, 1.0f, 100.0f);

	if (LiveTime >= 2.5f)
	{
		if (State != "InGame")
		{
			CurtainPtr->Reset();
			State = "InGame";
		}
	}
}

void MonsterLevel::PlayerCheck()
{
	if (!Player::MainPlayer->IsUpdate())
	{
		return;
	}

	if (Player::MainPlayer->GetState() == "Death")
	{
		if (State != "Lose")
		{
			Player::MainPlayer->AddCurExp(Player::MainPlayer->GetKill() * Monster::GetExp());

			CreateActor<GameResult>(UpdateOrder::UI)->Init(false);

			SoundOff();

			LiveTime = 0.0f;
			for (auto Ptr : FindActor(UpdateOrder::Monster))
			{
				dynamic_cast<Monster*>(Ptr)->Stop();
			}
			for (auto Ptr : FindActor(UpdateOrder::Boss))
			{
				dynamic_cast<MonsterBoss*>(Ptr)->SetState("Stop");
			}
			State = "Lose";
		}
	}
}

void MonsterLevel::MonsterCheck()
{
	if (State == "Win")
	{
		return;
	}

	if (Monster::GetCount() == 0)
	{
		if (State != "Win")
		{
			Player::MainPlayer->AddCurExp(Player::MainPlayer->GetKill() * Monster::GetExp());

			CreateActor<GameResult>(UpdateOrder::UI)->Init(true);

			SoundOff();

			LiveTime = 0.0f;
			Player::MainPlayer->Stop();
			State = "Win";
		}
	}
}

void MonsterLevel::TimeCheck()
{
	if (FramePtr->TimeOver())
	{
		if (State != "Lose")
		{
			Player::MainPlayer->AddCurExp(Player::MainPlayer->GetKill() * Monster::GetExp());

			CreateActor<GameResult>(UpdateOrder::UI)->Init(false);

			SoundOff();
			LiveTime = 0.0f;
			for (auto Ptr : FindActor(UpdateOrder::Monster))
			{
				dynamic_cast<Monster*>(Ptr)->Stop();
			}
			for (auto Ptr : FindActor(UpdateOrder::Boss))
			{
				dynamic_cast<MonsterBoss*>(Ptr)->SetState("Stop");
			}
			Player::MainPlayer->Stop();
			State = "Lose";
		}
	}
}

void MonsterLevel::OutButtonUpdate(float _Delta)
{
	if (BtnOut->GetIsClick())
	{
		CurtainPtr->SetDark(_Delta, BtnOut->GetTime());
	}

	if (BtnOut->GetAction())
	{
		BtnOut->Reset();

		Process->CreateLevel<TitleLevel>();
		SoundOff();
	}
}

void MonsterLevel::SoundOff()
{
	if (CurMap == "Octopus.txt" || CurMap == "Octopus1.txt")
	{
		GameEngineSound::FindSound("Octopus.mp3")->Stop();
	}
	else if (CurMap == "Boss.txt")
	{
		GameEngineSound::FindSound("BossStart.wav")->Stop();
	}
	else if (CurMap == "test.txt" || CurMap == "BossTest.txt")
	{
		GameEngineSound::FindSound("Patrit.mp3")->Stop();
	}
}
