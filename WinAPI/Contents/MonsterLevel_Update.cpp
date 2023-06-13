#include "MonsterLevel.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineProcess.h>

#include "Button.h"
#include "Curtain.h"

#include "TitleLevel.h"

void MonsterLevel::CuratinUpdate(float _Delta)
{
	if (LiveTime >= 2.6f)
	{
		return;
	}

	LiveTime += _Delta;

	if (LiveTime <= 1.0f)
	{
		CurtainPtr->SetBright(_Delta, 1.0f, 100.0f);
	}
	else if (LiveTime >= 2.5f)
	{
		CurtainPtr->Reset();
	}
}

void MonsterLevel::OutButtonUpdate(float _Delta)
{
	if (BtnOut->GetAction())
	{
		BtnOut->Reset();

		Process->CreateLevel<TitleLevel>();

		GameEngineSound::FindSound("Octopus.mp3")->Stop();
	}
}
