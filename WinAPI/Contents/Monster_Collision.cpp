#include "Monster.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Water.h"
#include "Player.h"

void Monster::CollisionCheck()
{
	for (auto Ptr : Level->FindActor(UpdateOrder::Water))
	{
		if (Index == Ptr->GetIndex())
		{
			if (State != "Death")
			{
				GameEngineSound::FindSound("MonsterDeath.wav")->Play();
				Player* PlayerPtr = dynamic_cast<Water*>(Ptr)->GetOwner();
				if (PlayerPtr)
				{
					PlayerPtr->AddKill(1);
				}
			}

			Dir = "";
			State = "Death";
		}
	}
}
