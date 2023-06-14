#include "Player.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Global.h"
#include "Item.h"
#include "Monster.h"

void Player::CollisionCheck(float _Delta)
{
	if (State == "Death")
	{
		return;
	}

	if (State != "Capture")
	{
		for (auto Ptr : Level->FindActor(UpdateOrder::Item))
		{
			if (Index == Ptr->GetIndex())
			{
				float4 Type = dynamic_cast<Item*>(Ptr)->GetType();
				GameEngineSound::FindSound("Get.mp3")->Play();
				if (Type.X == 0 && Type.Y == 0)
				{
					++CurSpeed;
				}
				else if (Type.X == 1 && Type.Y == 0)
				{
					++Length;
				}
				else if (Type.X == 2 && Type.Y == 0)
				{
					++Count;
				}
				else if (Type.X == 3 && Type.Y == 0)
				{
					Length = MaxLength;
				}
				Ptr->Death();
			}
		}
		if (Count > MaxCount)
		{
			Count = MaxCount;
		}
		if (Length > MaxLength)
		{
			Length = MaxLength;
		}
		if (CurSpeed > MaxSpeed)
		{
			CurSpeed = MaxSpeed;
		}
		Speed = CurSpeed * StdSpeed;
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Monster))
	{
		if (Index == Ptr->GetIndex())
		{
			GameEngineSound::FindSound("PlayerDeath.wav")->Play();

			Dir = "";
			State = "Death";
			LiveTime = 0.0f;
		}
	}

	if (State != "Free" && LiveTime >= 0.5f)
	{
		for (auto Ptr : Level->FindActor(UpdateOrder::Water))
		{
			if (Index == Ptr->GetIndex())
			{
				State = "Capture";
			}
		}
	}
}
