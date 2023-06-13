#include "Monster.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Global.h"
#include "Tile.h"

void Monster::StateUpdate(float _Delta)
{
	if (State == "Run")
	{
		RunUpdate(_Delta);
	}
}

void Monster::DirCheck()
{
	int Random = GameEngineRandom::RandomInt(2);
	if (Dir == "Up")
	{
		if (Random == 1)
		{
			Dir = "Left";
		}
		else
		{
			Dir = "Right";
		}
	}
	else if (Dir == "Down")
	{
		if (Random == 1)
		{
			Dir = "Left";
		}
		else
		{
			Dir = "Right";
		}
	}
	else if (Dir == "Left")
	{
		if (Random == 1)
		{
			Dir = "Up";
		}
		else
		{
			Dir = "Down";
		}
	}
	else if (Dir == "Right")
	{
		if (Random == 1)
		{
			Dir = "Up";
		}
		else
		{
			Dir = "Down";
		}
	}
}

void Monster::RunUpdate(float _Delta)
{
	Tile* NextTile = nullptr;

	if (Dir == "Left")
	{
		Pos.X -= Speed * _Delta;
		if (Left() < MapLeft)
		{
			Pos.X = MapLeft + Scale.hX();
			DirCheck();
		}

		NextTile = Tile::GetTile(Index + int2::Left);
		if (NextTile && !NextTile->GetIsEmpty() && Left() < NextTile->Right())
		{
			Pos.X = NextTile->Right() + Scale.hX();
			DirCheck();
		}
	}
	else if (Dir == "Right")
	{
		Pos.X += Speed * _Delta;
		if (Right() > MapRight)
		{
			Pos.X = MapRight - Scale.hX();
			DirCheck();
		}

		NextTile = Tile::GetTile(Index + int2::Right);
		if (NextTile && !NextTile->GetIsEmpty() && Right() > NextTile->Left())
		{
			Pos.X = NextTile->Left() - Scale.hX();
			DirCheck();
		}
	}
	else if (Dir == "Up")
	{
		Pos.Y -= Speed * _Delta;
		if (Top() < MapTop)
		{
			Pos.Y = MapTop + Scale.hY();
			DirCheck();
		}

		NextTile = Tile::GetTile(Index + int2::Up);
		if (NextTile && !NextTile->GetIsEmpty() && Top() < NextTile->Bottom())
		{
			Pos.Y = NextTile->Bottom() + Scale.hY();
			DirCheck();
		}
	}
	else if (Dir == "Down")
	{
		Pos.Y += Speed * _Delta;
		if (Bottom() > MapBottom)
		{
			Pos.Y = MapBottom - Scale.hY();
			DirCheck();
		}

		NextTile = Tile::GetTile(Index + int2::Down);
		if (NextTile && !NextTile->GetIsEmpty() && Bottom() > NextTile->Top())
		{
			Pos.Y = NextTile->Top() - Scale.hY();
			DirCheck();
		}
	}
	
	Index = PosToIndex(Pos);
}
