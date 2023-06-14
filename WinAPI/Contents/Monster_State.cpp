#include "Monster.h"
#include <vector>
#include <algorithm>
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
}

void Monster::RunUpdate(float _Delta)
{
	if (Dir == "Left")
	{
		Pos.X -= Speed * _Delta;
	}
	else if (Dir == "Right")
	{
		Pos.X += Speed * _Delta;
	}
	else if (Dir == "Up")
	{
		Pos.Y -= Speed * _Delta;
	}
	else if (Dir == "Down")
	{
		Pos.Y += Speed * _Delta;
	}
	else
	{
		ChangeDir();
	}

	if (Left() < MapLeft)
	{
		Pos.X += Speed * _Delta;
		ChangeDir();
	}
	else if (Right() > MapRight)
	{
		Pos.X -= Speed * _Delta;
		ChangeDir();
	}
	else if (Top() < MapTop)
	{
		Pos.Y += Speed * _Delta;
		ChangeDir();
	}
	else if (Bottom() > MapBottom)
	{
		Pos.Y -= Speed * _Delta;
		ChangeDir();
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (!Ptr)
		{
			continue;
		}

		if (Ptr->GetIndex() == (Index + int2::Left)
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty()
			&& Left() < Ptr->Right())
		{
			Pos.X += Speed * _Delta;
			ChangeDir();
		}
		if (Ptr->GetIndex() == (Index + int2::Right)
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty()
			&& Right() > Ptr->Left())
		{
			Pos.X -= Speed * _Delta;
			ChangeDir();
		}
		if (Ptr->GetIndex() == (Index + int2::Up)
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty()
			&& Top() < Ptr->Bottom())
		{
			Pos.Y += Speed * _Delta;
			ChangeDir();
		}
		if (Ptr->GetIndex() == (Index + int2::Down)
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty()
			&& Bottom() > Ptr->Top())
		{
			Pos.Y -= Speed * _Delta;
			ChangeDir();
		}
	}

	Index = PosToIndex(Pos);
}

void Monster::ChangeDir()
{
	std::vector<std::string> DirArr{"Left", "Right", "Up", "Down"};
	bool DirOn[4] = { true, true, true, true };
	if (Index.X == 0)
	{
		DirOn[0] = false;
	}
	else if (Index.X == 14)
	{
		DirOn[1] = false;
	}

	if (Index.Y == 0)
	{
		DirOn[2] = false;
	}
	else if (Index.Y == 12)
	{
		DirOn[3] = false;
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (!Ptr)
		{
			continue;
		}

		if (DirOn[0] && Ptr->GetIndex() == (Index + int2::Left)
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
		{
			DirOn[0] = false;
		}
		if (DirOn[1] && Ptr->GetIndex() == (Index + int2::Right)
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
		{
			DirOn[1] = false;
		}
		if (DirOn[2] && Ptr->GetIndex() == (Index + int2::Up)
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
		{
			DirOn[2] = false;
		}
		if (DirOn[3] && Ptr->GetIndex() == (Index + int2::Down)
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
		{
			DirOn[3] = false;
		}
	}

	int RndCnt = static_cast<int>(DirArr.size());
	if (RndCnt)
	{
		int Random = GameEngineRandom::RandomInt(RndCnt);
		Dir = DirArr[Random - 1];
	}
}
