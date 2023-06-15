#include "Monster.h"
#include <vector>
#include <algorithm>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Tile.h"

void Monster::StateUpdate(float _Delta)
{
	if (State == "Start")
	{
		StartUpdate(_Delta);
	}
	else if (State == "Run")
	{
		RunUpdate(_Delta);
	}
	else if (State == "Death")
	{
		DeathUpdate(_Delta);
	}
}

void Monster::StartUpdate(float _Delta)
{
	if (FindRenderer(Main)->IsAnimationEnd("Start")
		&& LiveTime >= 1.75f)
	{
		RandomMove();
		LiveTime = 0.0f;
	}
}

void Monster::RunUpdate(float _Delta)
{
	if (Dir == "Left")
	{
		Pos.X -= Speed * _Delta;

		if (Left() < MapLeft)
		{
			Pos.X += Speed * _Delta;
			ChangeDir();
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Ptr->GetIndex() == Index + int2::Left
				&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty()
				&& Left() < Ptr->Right())
			{
				Pos.X = Ptr->GetPos().X + TileSize.X;
				ChangeDir();
			}
		}
	}
	else if (Dir == "Right")
	{
		Pos.X += Speed * _Delta;

		if (Right() > MapRight)
		{
			Pos.X -= Speed * _Delta;
			ChangeDir();
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Ptr->GetIndex() == Index + int2::Right
				&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty()
				&& Right() > Ptr->Left())
			{
				Pos.X = Ptr->GetPos().X - TileSize.X;
				ChangeDir();
			}
		}
	}
	else if (Dir == "Up")
	{
		Pos.Y -= Speed * _Delta;

		if (Top() < MapTop)
		{
			Pos.Y += Speed * _Delta;
			ChangeDir();
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Ptr->GetIndex() == Index + int2::Up
				&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty()
				&& Top() < Ptr->Bottom())
			{
				Pos.Y = Ptr->GetPos().Y + TileSize.Y;
				ChangeDir();
			}
		}
	}
	else if (Dir == "Down")
	{
		Pos.Y += Speed * _Delta;

		if (Bottom() > MapBottom)
		{
			Pos.Y -= Speed * _Delta;
			ChangeDir();
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr && Ptr->GetIndex() == Index + int2::Down
				&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty()
				&& Bottom() > Ptr->Top())
			{
				Pos.Y = Ptr->GetPos().Y - TileSize.Y;
				ChangeDir();
			}
		}
	}
	else
	{
		ChangeDir();
	}

	Index = PosToIndex(Pos);
}

void Monster::ChangeDir()
{
	bool DirOn[4] = { true, true, true, true };

	if (DirOn[0] && Pos.X - TileSize.X < MapLeft)
	{
		DirOn[0] = false;
	}
	else if (DirOn[1] && Pos.X + TileSize.X > MapRight)
	{
		DirOn[1] = false;
	}

	if (DirOn[2] && Pos.Y - TileSize.Y < MapTop)
	{
		DirOn[2] = false;
	}
	else if (DirOn[3] && Pos.Y + TileSize.Y > MapBottom)
	{
		DirOn[3] = false;
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (DirOn[0] && Ptr && Ptr->GetIndex() == Index + int2::Left
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
		{
			DirOn[0] = false;
		}
		if (DirOn[1] && Ptr && Ptr->GetIndex() == Index + int2::Right
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
		{
			DirOn[1] = false;
		}
		if (DirOn[2] && Ptr && Ptr->GetIndex() == Index + int2::Up
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
		{
			DirOn[2] = false;
		}
		if (DirOn[3] && Ptr && Ptr->GetIndex() == Index + int2::Down
			&& !dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
		{
			DirOn[3] = false;
		}
	}

	if (!DirOn[0] && !DirOn[1] && !DirOn[2] && !DirOn[3])
	{
		Dir = "";
		return;
	}

	std::vector<std::string> DirArr = { "Left", "Right", "Up", "Down" };
	if (!DirOn[0])
	{
		DirArr.erase(std::remove_if(DirArr.begin(), DirArr.end(),
			[](std::string _Str)
			{
				return _Str == "Left";
			}),
			DirArr.end());
	}
	if (!DirOn[1])
	{
		DirArr.erase(std::remove_if(DirArr.begin(), DirArr.end(),
			[](std::string _Str)
			{
				return _Str == "Right";
			}),
			DirArr.end());
	}
	if (!DirOn[2])
	{
		DirArr.erase(std::remove_if(DirArr.begin(), DirArr.end(),
			[](std::string _Str)
			{
				return _Str == "Up";
			}),
			DirArr.end());
	}
	if (!DirOn[3])
	{
		DirArr.erase(std::remove_if(DirArr.begin(), DirArr.end(),
			[](std::string _Str)
			{
				return _Str == "Down";
			}),
			DirArr.end());
	}

	int RndCnt = static_cast<int>(DirArr.size());
	int RndInt = GameEngineRandom::RandomInt(RndCnt);
	Dir = DirArr[RndInt - 1];
}

void Monster::DeathUpdate(float _Delta)
{
	if (FindRenderer(Main)->IsAnimationEnd("Death"))
	{
		Death();
	}
}
