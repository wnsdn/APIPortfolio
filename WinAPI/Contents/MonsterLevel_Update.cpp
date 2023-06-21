#include "MonsterLevel.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineProcess.h>

#include "Global.h"
#include "Button.h"
#include "Curtain.h"
#include "GameResult.h"

#include "Player.h"
#include "Monster.h"
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

			CreateActor<GameResult>(UpdateOrder::UI)->Init(Player::MainPlayer, false);

			GameEngineSound::FindSound("Octopus.mp3")->Stop();
			LiveTime = 0.0f;
			for (auto Ptr : FindActor(UpdateOrder::Monster))
			{
				dynamic_cast<Monster*>(Ptr)->Stop();
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

			CreateActor<GameResult>(UpdateOrder::UI)->Init(Player::MainPlayer, true);

			GameEngineSound::FindSound("Octopus.mp3")->Stop();
			LiveTime = 0.0f;
			Player::MainPlayer->Stop();
			State = "Win";
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

		GameEngineSound::FindSound("Octopus.mp3")->Stop();
	}
}
