#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Global.h"
#include "Tile.h"
#include "Item.h"
#include "Bomb.h"
#include "Monster.h"

void Player::AllUpdate(float _Delta)
{
	BombSet();
	ItemUseUpdate();
	ItemUpdate();
	ShieldUpdate();
	ExpUpdate();

	ChangeAnimation();
}

void Player::ChangeAnimation()
{
	if (State == "Ready" || State == "Jump")
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

	if (GameEngineInput::IsDown(VK_SPACE))
	{
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Count > 0 && Index == Ptr->GetIndex() &&
				dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				Level->CreateActor<Bomb>(UpdateOrder::Bomb)->Init(Index, Length, this);
				--Count;
				return;
			}
		}

		for (auto BombPtr : Level->FindActor(UpdateOrder::Bomb))
		{
			if (Index == BombPtr->GetIndex() && CanThrow)
			{
				dynamic_cast<Bomb*>(BombPtr)->SetDir(Dir);
				dynamic_cast<Bomb*>(BombPtr)->SetState("Fly");
				BombPtr->ResetLiveTime();

				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index)
					{
						BombPtr->FindRenderer("Bubble.bmp")->SetPos({ 0, -20.0f });
						GameEngineSound::FindSound("PlayerThrow.mp3")->Play();
						dynamic_cast<Tile*>(Ptr)->Empty();
					}
				}
			}
		}
	}
}

void Player::ItemUseUpdate()
{
	if (GameEngineInput::IsDown(VK_LCONTROL))
	{
		if (State == "Capture" && CurItem == "Needle" && ItemNeedle)
		{
			Dir = "Down";
			GameEngineSound::FindSound("PlayerFree.wav")->Play();
			State = "Free";
			FindRenderer(Main)->SetPos({ 0, -11 });
			--ItemNeedle;
			return;
		}

		if (State == "Capture" || State == "Death" || State == "Stop" || State == "Ready")
		{
			return;
		}

		if (CurItem == "Shield" && ItemShield && !ShieldOn)
		{
			GameEngineSound::FindSound("PlayerShield.wav")->Play();
			FindRenderer("PlayerShield.bmp")->ResetLiveTime();
			ShieldOn = true;
			--ItemShield;
			return;
		}

		if (CurItem == "Jump" && ItemJump && State != "Jump")
		{
			bool Tile2 = false;
			bool Tile3 = false;
			bool Tile4 = false;
			for (auto Ptr1 : Level->FindActor(UpdateOrder::Tile))
			{
				for (auto Ptr2 : Level->FindActor(UpdateOrder::Tile))
				{
					if (Dir == "Left" &&
						Ptr1->GetIndex() == Index + int2::Left &&
						!dynamic_cast<Tile*>(Ptr1)->GetIsEmpty())
					{
						if (Ptr2->GetIndex() == Index + int2::Left * 2 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile2 = true;
						}
						else if (Ptr2->GetIndex() == Index + int2::Left * 3 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile3 = true;
						}
						else if (Ptr2->GetIndex() == Index + int2::Left * 4 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile4 = true;
						}
					}
					else if (Dir == "Right" &&
						Ptr1->GetIndex() == Index + int2::Right &&
						!dynamic_cast<Tile*>(Ptr1)->GetIsEmpty())
					{
						if (Ptr2->GetIndex() == Index + int2::Right * 2 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile2 = true;
						}
						else if (Ptr2->GetIndex() == Index + int2::Right * 3 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile3 = true;
						}
						else if (Ptr2->GetIndex() == Index + int2::Right * 4 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile4 = true;
						}
					}
					else if (Dir == "Up" &&
						Ptr1->GetIndex() == Index + int2::Up &&
						!dynamic_cast<Tile*>(Ptr1)->GetIsEmpty())
					{
						if (Ptr2->GetIndex() == Index + int2::Up * 2 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile2 = true;
						}
						else if (Ptr2->GetIndex() == Index + int2::Up * 3 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile3 = true;
						}
						else if (Ptr2->GetIndex() == Index + int2::Up * 4 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile4 = true;
						}
					}
					else if (Dir == "Down" &&
						Ptr1->GetIndex() == Index + int2::Down &&
						!dynamic_cast<Tile*>(Ptr1)->GetIsEmpty())
					{
						if (Ptr2->GetIndex() == Index + int2::Down * 2 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile2 = true;
						}
						else if (Ptr2->GetIndex() == Index + int2::Down * 3 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile3 = true;
						}
						else if (Ptr2->GetIndex() == Index + int2::Down * 4 &&
							dynamic_cast<Tile*>(Ptr2)->GetIsEmpty())
						{
							Tile4 = true;
						}
					}
				}
			}

			if (Tile2)
			{
				JumpMaxDist = TileSize.X * 2;
				GameEngineSound::FindSound("PlayerJump.mp3")->Play();
				State = "Jump";
				FindRenderer(Main)->SetTheFirst(true);
				--ItemJump;
			}
			else if (Tile3)
			{
				JumpMaxDist = TileSize.X * 3;
				GameEngineSound::FindSound("PlayerJump.mp3")->Play();
				State = "Jump";
				FindRenderer(Main)->SetTheFirst(true);
				--ItemJump;
			}
			else if (Tile4)
			{
				JumpMaxDist = TileSize.X * 4;
				GameEngineSound::FindSound("PlayerJump.mp3")->Play();
				State = "Jump";
				FindRenderer(Main)->SetTheFirst(true);
				--ItemJump;
			}
		}
	}
}

void Player::ItemUpdate()
{
	if (CurItem == "Needle" && !ItemNeedle)
	{
		CurItem = "";
	}
	else if (CurItem == "Shield" && !ItemShield)
	{
		CurItem = "";
	}
	else if (CurItem == "Jump" && !ItemJump)
	{
		CurItem = "";
	}

	if (GameEngineInput::IsDown('1') && ItemNeedle)
	{
		CurItem = "Needle";
	}
	if (GameEngineInput::IsDown('2') && ItemShield)
	{
		CurItem = "Shield";
	}
	if (GameEngineInput::IsDown('3') && ItemJump)
	{
		CurItem = "Jump";
	}
}

void Player::ShieldUpdate()
{
	if (ShieldOn)
	{
		FindRenderer("PlayerShield.bmp")->On();

		if (FindRenderer("PlayerShield.bmp")->GetLiveTime() >= 2.0f)
		{
			FindRenderer("PlayerShield.bmp")->Off();
			FindRenderer("PlayerShield.bmp")->ResetLiveTime();
			ShieldOn = false;
		}
	}
}

void Player::ExpUpdate()
{
	/*if (Rank == 19)
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
	}*/

	//MaxExp = Rank + 1 * 100;
}
