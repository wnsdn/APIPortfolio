#include "Monster.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Global.h"
#include "Water.h"
#include "Player.h"

void Monster::CollisionCheck()
{
	Collider->SetPos(Pos);

	if (State == "Stop")
	{
		return;
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Water))
	{
		if (Index == Ptr->GetIndex())
		{
			Kill();
		}
	}
}
