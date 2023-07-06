#include "Player.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Item.h"
#include "Monster.h"
#include "MonsterBoss.h"

void Player::CollisionCheck(float _Delta)
{
	Collider->SetPos(Pos);

	if (State == "Death" || State == "Stop" || State == "Ready")
	{
		return;
	}

	if (State != "Capture")
	{
		for (auto Ptr : Level->FindActor(UpdateOrder::Item))
		{
			//if (GameEngineCollision::CollisionCheck(Collider, dynamic_cast<Item*>(Ptr)->GetCollider()))
			if (Index == Ptr->GetIndex())
			{
				float4 Type = dynamic_cast<Item*>(Ptr)->GetType();
				GameEngineSound::FindSound("ItemGet.mp3")->Play();
				if (Type.X == 0 && Type.Y == 0)
				{
					++CurSpeed;
				}
				else if (Type.X == 0 && Type.Y == 1)
				{
					++Count;
				}
				else if (Type.X == 0 && Type.Y == 2)
				{
					CanKick = true;
				}
				else if (Type.X == 0 && Type.Y == 3)
				{
					CurSpeed = MaxSpeed;
					CanKick = true;
				}
				else if (Type.X == 0 && Type.Y == 4)
				{
					++ItemShield;
					CurItem = "Shield";
				}
				else if (Type.X == 1 && Type.Y == 0)
				{
					++Length;
				}
				else if (Type.X == 1 && Type.Y == 1)
				{
					Length = MaxLength;
				}
				else if (Type.X == 1 && Type.Y == 2)
				{
					CanThrow = true;
				}
				else if (Type.X == 1 && Type.Y == 3)
				{
					++ItemNeedle;
					CurItem = "Needle";
				}
				else if (Type.X == 1 && Type.Y == 4)
				{
					++ItemJump;
					CurItem = "Jump";
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
		if (ItemJump > 6)
		{
			ItemJump = 6;
		}
		if (ItemNeedle > 6)
		{
			ItemNeedle = 6;
		}
		if (ItemShield > 6)
		{
			ItemShield = 6;
		}
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Monster))
	{
		if (!ShieldOn && State != "Jump" && !GodMode &&
			GameEngineCollision::CollisionCheck(Collider, dynamic_cast<Monster*>(Ptr)->GetCollider()))
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

	for (auto Ptr : Level->FindActor(UpdateOrder::Boss))
	{
		if (!ShieldOn && State != "Jump" && !GodMode &&
			Pos.X >= dynamic_cast<MonsterBoss*>(Ptr)->GetCollider()->Left() && Pos.X <= dynamic_cast<MonsterBoss*>(Ptr)->GetCollider()->Right() &&
			Pos.Y >= dynamic_cast<MonsterBoss*>(Ptr)->GetCollider()->Top() && Pos.Y <= dynamic_cast<MonsterBoss*>(Ptr)->GetCollider()->Bottom() &&
			dynamic_cast<MonsterBoss*>(Ptr)->GetState() != "Capture" && dynamic_cast<MonsterBoss*>(Ptr)->GetState() != "Death")
		{
			if (State != "Death")
			{
				GameEngineSound::FindSound("PlayerDeath.wav")->Play();
			}

			Dir = "";
			State = "Death";
			LiveTime = 0.0f;
		}
		else if (dynamic_cast<MonsterBoss*>(Ptr)->GetState() == "Capture" &&
			Pos.X >= dynamic_cast<MonsterBoss*>(Ptr)->GetCollider()->Left() + 21 && Pos.X <= dynamic_cast<MonsterBoss*>(Ptr)->GetCollider()->Right() - 21 &&
			Pos.Y >= dynamic_cast<MonsterBoss*>(Ptr)->GetCollider()->Top() + 21 && Pos.Y <= dynamic_cast<MonsterBoss*>(Ptr)->GetCollider()->Bottom() - 21)
		{
			GameEngineSound::FindSound("BossDeath.mp3")->Play();
			Monster::SetCount(0);
			dynamic_cast<MonsterBoss*>(Ptr)->SetState("Death");
			Player::MainPlayer->AddCurExp(111);
		}
	}

	if (State != "Free" && LiveTime >= 0.5f && !ShieldOn && State != "Jump" && !GodMode)
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