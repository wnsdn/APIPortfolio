#include "MonsterLevel.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineProcess.h>

#include "Global.h"
#include "Button.h"
#include "Curtain.h"
#include "GameResult.h"

#include "Player.h"
#include "TitleLevel.h"

void MonsterLevel::CuratinUpdate(float _Delta)
{
	if (LiveTime <= 1.0f)
	{
		CurtainPtr->SetBright(_Delta, 1.0f, 100.0f);
	}
	else if (LiveTime >= 2.5f)
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
	if (!Player::MainPlayer)
	{
		return;
	}

	if (Player::MainPlayer->GetState() == "Death")
	{
		if (State != "Lose")
		{
			ResultPtr->RendererOn();
			GameEngineSound::FindSound("Octopus.mp3")->Stop();
			GameEngineSound::FindSound("GameLose.mp3")->Play();
			LiveTime = 0.0f;
			State = "Lose";
		}
	}
}

void MonsterLevel::OutButtonUpdate()
{
	if (BtnOut->GetAction())
	{
		BtnOut->Reset();

		Process->CreateLevel<TitleLevel>();

		GameEngineSound::FindSound("Octopus.mp3")->Stop();
	}
}
