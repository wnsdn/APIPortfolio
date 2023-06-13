#include "MonsterLevel.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineProcess.h>

#include "Button.h"

#include "TitleLevel.h"

void MonsterLevel::OutButtonUpdate(float _Delta)
{
	if (BtnOut->GetAction())
	{
		BtnOut->Reset();

		Process->CreateLevel<TitleLevel>();

		GameEngineSound::FindSound("Octopus.mp3")->Stop();
	}
}
