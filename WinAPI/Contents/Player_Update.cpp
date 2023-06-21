#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Global.h"
#include "Tile.h"
#include "Item.h"
#include "Bomb.h"
#include "Monster.h"

void Player::CollisionCheck(float _Delta)
{
	if (State == "Death" || State == "Stop" || State == "Ready")
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
				GameEngineSound::FindSound("ItemGet.mp3")->Play();
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
			if (State != "Death")
			{
				GameEngineSound::FindSound("PlayerDeath.wav")->Play();
			}

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

void Player::ChangeAnimation()
{
	if (State == "Ready")
	{
		return;
	}

	if (State == "Capture" || State == "Free")
	{
		FindRenderer(Main)->ChangeAnimation(State);
	}
	else if (State == "Stop")
	{
		FindRenderer(Main)->ChangeAnimation("DownIdle");
	}
	else
	{
		FindRenderer(Main)->ChangeAnimation(Dir + State);
	}
}

void Player::BombSet()
{
	if (State == "Capture" || State == "Death" || State == "Stop" || State == "Ready")
	{
		return;
	}

	if (Count > 0 && GameEngineInput::IsDown(VK_SPACE))
	{
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Index == Ptr->GetIndex() && dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				Level->CreateActor<Bomb>(UpdateOrder::Bomb)->Init(Index, Length, this);
				--Count;
			}
		}
	}
}

void Player::ExpUpdate()
{
	if (Rank == 19)
	{
		return;
	}

	while (CurExp >= MaxExp)
	{
		CurExp -= MaxExp;
		Rank += 1;
	}

	if (Rank >= 20)
	{
		Rank = 19;
	}

	//MaxExp = Rank + 1 * 100;
}
