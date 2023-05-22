#include "Monster.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "Global.h"

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
	float4 MovePos = {};
	if (Dir == "Up")
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}
	else if (Dir == "Down")
	{
		MovePos = { 0.0f, Speed * _Delta };
	}
	else if (Dir == "Left")
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (Dir == "Right")
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (Pos.X - TileSize.Half().X + MovePos.X > MapLeft
		&& Pos.Y - TileSize.Half().Y + MovePos.Y > MapTop
		&& Pos.X + TileSize.Half().X + MovePos.X < MapRight
		&& Pos.Y + TileSize.Half().Y + MovePos.Y < MapBottom)
	{
		Pos += MovePos;
		Index = PosToIndex(Pos);
	}
	else
	{
		DirCheck();
	}
}
