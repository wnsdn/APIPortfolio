#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineProcess.h>

#include "MonsterLevel.h"

#include "Button.h"
#include "Curtain.h"

void TitleLevel::StartButtonUpdate(float _Delta)
{
	if (StartButton->GetIsClick())
	{
		CurtainPtr->SetDark(_Delta, StartButton->GetTime());
	}

	if (StartButton->GetAction())
	{
		StartButton->Reset();

		Process->CreateLevel<MonsterLevel>()->Init("Octopus.txt");

		GameEngineSound::FindSound("Title.wav")->Stop();
	}
}

void TitleLevel::ExitButtonUpdate(float _Delta)
{
	if (ExitButton->GetIsClick())
	{
		CurtainPtr->SetDark(_Delta, ExitButton->GetTime());
	}

	if (ExitButton->GetAction())
	{
		ExitButton->Reset();
		GameEngineWindow::GetInst().SetIsWindowUpdate(false);

		CurtainPtr->Reset();
		CurtainPtr->SetDark(_Delta, StartButton->GetTime());
	}
}
