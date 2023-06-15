#include "Monster.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"

void Monster::CollisionCheck()
{
	for (auto Ptr : Level->FindActor(UpdateOrder::Water))
	{
		if (Index == Ptr->GetIndex())
		{
			if (State != "Death")
			{
				GameEngineSound::FindSound("MonsterDeath.wav")->Play();
			}

			Dir = "";
			State = "Death";
		}
	}
}
