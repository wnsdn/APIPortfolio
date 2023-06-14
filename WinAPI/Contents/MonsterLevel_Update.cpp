#include "MonsterLevel.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineProcess.h>

#include "Global.h"
#include "Button.h"
#include "Curtain.h"

#include "Monster.h"
#include "TitleLevel.h"

void MonsterLevel::CuratinUpdate(float _Delta)
{
	if (Once)
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
		if (!Once)
		{
			CurtainPtr->Reset();
			for (auto Ptr : FindActor(UpdateOrder::Monster))
			{
				if (Ptr)
				{
					dynamic_cast<Monster*>(Ptr)->RandomMove();
				}
			}
			Once = true;
		}
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
