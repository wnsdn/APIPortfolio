#include "Player.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Tile.h"

void Player::StateUpdate(float _Delta)
{
	if (State == "Idle")
	{
		IdleUpdate(_Delta);
	}
	else if (State == "Run")
	{
		RunUpdate(_Delta);
	}
}

void Player::DirCheck()
{
	if (GameEngineInput::IsFree(VK_UP)
		&& GameEngineInput::IsFree(VK_DOWN)
		&& GameEngineInput::IsFree(VK_LEFT)
		&& GameEngineInput::IsFree(VK_RIGHT))
	{
		return;
	}
	if (GameEngineInput::IsDown(VK_UP))
	{
		Dir = "Up";
		return;
	}
	if (GameEngineInput::IsDown(VK_DOWN))
	{
		Dir = "Down";
		return;
	}
	if (GameEngineInput::IsDown(VK_LEFT))
	{
		Dir = "Left";
		return;
	}
	if (GameEngineInput::IsDown(VK_RIGHT))
	{
		Dir = "Right";
		return;
	}
}

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_UP)
		|| GameEngineInput::IsDown(VK_DOWN)
		|| GameEngineInput::IsDown(VK_LEFT)
		|| GameEngineInput::IsDown(VK_RIGHT))
	{
		DirCheck();
		State = "Run";
	}
}

void Player::RunUpdate(float _Delta)
{
	DirCheck();

	if (GameEngineInput::IsPress(VK_LEFT) && Dir == "Left")
	{
		Pos.X -= Speed * _Delta;
		if (Left() <= MapLeft)
		{
			Pos.X += Speed * _Delta;
		}

		Tile* TilePtr = Tile::GetTile(Index + int2::Left);
		if ((TilePtr->GetBlock()) &&
			Left() <= TilePtr->Right())
		{
			Pos.X += Speed * _Delta;
		}
		/*for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			Tile* Temp = dynamic_cast<Tile*>(Ptr);
			if (Temp->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Temp))
			{
				if (Index.X > Ptr->GetIndex().X)
				{
					if (Index.Y == Ptr->GetIndex().Y)
					{
						Pos.X += Speed * _Delta;
					}

					if (Pos.Y > Ptr->GetPos().Y + Ptr->GetScale().hY() * TrimRatio &&
						Tile::GetTile(Ptr->GetIndex() + int2::Down)->GetIsEmpty())
					{
						Pos.X += Speed * _Delta;
						Pos.Y += Speed * SpeedRatio * _Delta;
					}
					else if (Pos.Y < Ptr->GetPos().Y - Ptr->GetScale().hY() * TrimRatio &&
						Tile::GetTile(Ptr->GetIndex() + int2::Up)->GetIsEmpty())
					{
						Pos.X += Speed * _Delta;
						Pos.Y -= Speed * SpeedRatio * _Delta;
					}
				}
			}
		}*/
	}
	else if (GameEngineInput::IsPress(VK_RIGHT) && Dir == "Right")
	{
		Pos.X += Speed * _Delta;
		if (Right() >= MapRight)
		{
			Pos.X -= Speed * _Delta;
		}

		/*for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			Tile* Temp = dynamic_cast<Tile*>(Ptr);
			if (Temp->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Temp))
			{
				if (Index.X < Ptr->GetIndex().X)
				{
					if (Index.Y == Ptr->GetIndex().Y)
					{
						Pos.X -= Speed * _Delta;
					}

					if (Pos.Y > Ptr->GetPos().Y + Ptr->GetScale().hY() * TrimRatio &&
						Tile::GetTile(Ptr->GetIndex() + int2::Down)->GetIsEmpty())
					{
						Pos.X -= Speed * _Delta;
						Pos.Y += Speed * SpeedRatio * _Delta;
					}
					else if (Pos.Y < Ptr->GetPos().Y - Ptr->GetScale().hY() * TrimRatio &&
						Tile::GetTile(Ptr->GetIndex() + int2::Up)->GetIsEmpty())
					{
						Pos.X -= Speed * _Delta;
						Pos.Y -= Speed * SpeedRatio * _Delta;
					}
				}
			}
		}*/
	}
	else if (GameEngineInput::IsPress(VK_UP) && Dir == "Up")
	{
		Pos.Y -= Speed * _Delta;
		if (Top() <= MapTop)
		{
			Pos.Y += Speed * _Delta;
		}

		//for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		//{
		//	Tile* Temp = dynamic_cast<Tile*>(Ptr);
		//	if (Temp->GetIsEmpty())
		//	{
		//		continue;
		//	}

		//	if (GameEngineCollision::CollisionCheck(this, Temp))
		//	{
		//		if (Index.Y > Ptr->GetIndex().Y)
		//		{
		//			if (Index.X == Ptr->GetIndex().X)
		//			{
		//				//Pos.Y += Speed * _Delta;
		//				Pos.Y = Ptr->GetPos().Y + TileSize.Y;
		//			}

		//			if (Pos.X > Ptr->GetPos().X + Ptr->GetScale().hX() * TrimRatio &&
		//				Tile::GetTile(Ptr->GetIndex() + int2::Right)->GetIsEmpty())
		//			{
		//				Pos.Y += Speed * _Delta;
		//				Pos.X += Speed * SpeedRatio * _Delta;
		//			}
		//			else if (Pos.X < Ptr->GetPos().X - Ptr->GetScale().hX() * TrimRatio &&
		//				Tile::GetTile(Ptr->GetIndex() + int2::Left)->GetIsEmpty())
		//			{
		//				Pos.Y += Speed * _Delta;
		//				Pos.X -= Speed * SpeedRatio * _Delta;
		//			}
		//		}
		//	}
		//}
	}
	else if (GameEngineInput::IsPress(VK_DOWN) && Dir == "Down")
	{
		Pos.Y += Speed * _Delta;
		if (Bot() >= MapBottom)
		{
			Pos.Y -= Speed * _Delta;
		}

		/*for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			Tile* Temp = dynamic_cast<Tile*>(Ptr);
			if (Temp->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Temp))
			{
				if (Index.Y < Ptr->GetIndex().Y)
				{
					if (Index.X == Ptr->GetIndex().X)
					{
						Pos.Y -= Speed * _Delta;
					}

					if (Pos.X > Ptr->GetPos().X + Ptr->GetScale().hX() * TrimRatio &&
						Tile::GetTile(Ptr->GetIndex() + int2::Right)->GetIsEmpty())
					{
						Pos.Y -= Speed * _Delta;
						Pos.X += Speed * SpeedRatio * _Delta;
					}
					else if (Pos.X < Ptr->GetPos().X - Ptr->GetScale().hX() * TrimRatio &&
						Tile::GetTile(Ptr->GetIndex() + int2::Left)->GetIsEmpty())
					{
						Pos.Y -= Speed * _Delta;
						Pos.X -= Speed * SpeedRatio * _Delta;
					}
				}
			}
		}*/
	}
	else
	{
		State = "Idle";
	}

	Index = PosToIndex(Pos);
}
