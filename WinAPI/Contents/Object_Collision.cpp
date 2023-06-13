#include "Object.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Player.h"
#include "Tile.h"

void Object::CollisionCheck(float _Delta)
{
	Player* PlayerPtr = Player::MainPlayer;

	if (PlayerPtr && PlayerPtr->GetState() == "Run")
	{
		if (PlayerPtr->GetDir() == "Left")
		{
			Tile* LeftTile = nullptr;
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr && (Index + int2::Left) == Ptr->GetIndex())
				{
					LeftTile = dynamic_cast<Tile*>(Ptr);
				}
			}

			if (CanMove &&
				LeftTile && LeftTile->GetIsEmpty() &&
				PlayerPtr->GetIndex().X == Index.X + 1 &&
				PlayerPtr->GetIndex().Y == Index.Y)
			{
				MoveLeft += _Delta;
			}
			MoveRight = 0.f;
			MoveUp = 0.f;
			MoveDown = 0.f;
		}
		else if (PlayerPtr->GetDir() == "Right")
		{
			Tile* RightTile = nullptr;
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr && (Index + int2::Right) == Ptr->GetIndex())
				{
					RightTile = dynamic_cast<Tile*>(Ptr);
				}
			}

			if (CanMove &&
				RightTile && RightTile->GetIsEmpty() &&
				PlayerPtr->GetIndex().X == Index.X - 1 &&
				PlayerPtr->GetIndex().Y == Index.Y)
			{
				MoveRight += _Delta;
			}
			MoveUp = 0.f;
			MoveLeft = 0.f;
			MoveDown = 0.f;
		}
		else if (PlayerPtr->GetDir() == "Up")
		{
			Tile* UpTile = nullptr;
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr && (Index + int2::Up) == Ptr->GetIndex())
				{
					UpTile = dynamic_cast<Tile*>(Ptr);
				}
			}

			if (CanMove &&
				UpTile && UpTile->GetIsEmpty() &&
				PlayerPtr->GetIndex().X == Index.X &&
				PlayerPtr->GetIndex().Y == Index.Y + 1)
			{
				MoveUp += _Delta;
			}
			MoveLeft = 0.f;
			MoveRight = 0.f;
			MoveDown = 0.f;
		}
		else if (PlayerPtr->GetDir() == "Down")
		{
			Tile* DownTile = nullptr;
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr && (Index + int2::Down) == Ptr->GetIndex())
				{
					DownTile = dynamic_cast<Tile*>(Ptr);
				}
			}

			if (CanMove &&
				DownTile && DownTile->GetIsEmpty() &&
				PlayerPtr->GetIndex().X == Index.X &&
				PlayerPtr->GetIndex().Y == Index.Y - 1)
			{
				MoveDown += _Delta;
			}
			MoveLeft = 0.f;
			MoveRight = 0.f;
			MoveUp = 0.f;
		}
	}
	else
	{
		MoveLeft = 0.f;
		MoveRight = 0.f;
		MoveUp = 0.f;
		MoveDown = 0.f;
	}

	if (MoveLeft >= 0.5f)
	{
		MoveDir = "Left";
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Index == Ptr->GetIndex())
			{
				dynamic_cast<Tile*>(Ptr)->Empty();
			}
		}
	}
	else if (MoveRight >= 0.5f)
	{
		MoveDir = "Right";
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Index == Ptr->GetIndex())
			{
				dynamic_cast<Tile*>(Ptr)->Empty();
			}
		}
	}
	else if (MoveUp >= 0.5f)
	{
		MoveDir = "Up";
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Index == Ptr->GetIndex())
			{
				dynamic_cast<Tile*>(Ptr)->Empty();
			}
		}
	}
	else if (MoveDown >= 0.5f)
	{
		MoveDir = "Down";
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Index == Ptr->GetIndex())
			{
				dynamic_cast<Tile*>(Ptr)->Empty();
			}
		}
	}

	if (MoveDir == "Left")
	{
		Pos.X -= 120.f * _Delta;
		MoveDist += 120.f * _Delta;
	}
	else if (MoveDir == "Right")
	{
		Pos.X += 120.f * _Delta;
		MoveDist += 120.f * _Delta;
	}
	else if (MoveDir == "Up")
	{
		Pos.Y -= 120.f * _Delta;
		MoveDist += 120.f * _Delta;
	}
	else if (MoveDir == "Down")
	{
		Pos.Y += 120.f * _Delta;
		MoveDist += 120.f * _Delta;
	}

	if (MoveDist >= TileSize.X)
	{
		MoveLeft = 0.f;
		MoveRight = 0.f;
		MoveUp = 0.f;
		MoveDown = 0.f;
		MoveDist -= TileSize.X;

		if (MoveDir == "Left")
		{
			Pos.X += MoveDist * _Delta;
		}
		else if (MoveDir == "Right")
		{
			Pos.X -= MoveDist * _Delta;
		}
		else if (MoveDir == "Up")
		{
			Pos.Y += MoveDist * _Delta;
		}
		else if (MoveDir == "Down")
		{
			Pos.Y -= MoveDist * _Delta;
		}

		MoveDist = 0.f;
		MoveDir = "";

		Index = PosToIndex(Pos);
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Index == Ptr->GetIndex())
			{
				dynamic_cast<Tile*>(Ptr)->Full();
			}
		}
	}

	if (MoveDir == "Left")
	{
		if (PlayerPtr->Left() <= Right())
		{
			PlayerPtr->AddPos({ PlayerPtr->GetSpeed() * _Delta, 0 });
		}
	}
	else if (MoveDir == "Right")
	{
		if (PlayerPtr->Right() >= Left())
		{
			PlayerPtr->AddPos({ -PlayerPtr->GetSpeed() * _Delta, 0 });
		}
	}
	else if (MoveDir == "Up")
	{
		if (PlayerPtr->Top() <= Bottom())
		{
			PlayerPtr->AddPos({ 0, PlayerPtr->GetSpeed() * _Delta });
		}
	}
	else if (MoveDir == "Down")
	{
		if (PlayerPtr->Bottom() >= Top())
		{
			PlayerPtr->AddPos({ 0, -PlayerPtr->GetSpeed() * _Delta });
		}
	}
}