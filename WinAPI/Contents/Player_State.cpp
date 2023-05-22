#include "Player.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
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

	float4 MovePos = {};
	if (GameEngineInput::IsPress(VK_LEFT) && Dir == "Left")
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (GameEngineInput::IsPress(VK_RIGHT) && Dir == "Right")
	{
		MovePos = { Speed * _Delta, 0.0f };
	}
	else if (GameEngineInput::IsPress(VK_UP) && Dir == "Up")
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}
	else if (GameEngineInput::IsPress(VK_DOWN) && Dir == "Down")
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (Pos - TileSize.Half() + MovePos > MapLeftTop &&
		Pos + TileSize.Half() + MovePos < MapRightBottom)
	{
		Pos += MovePos;
		Index = PosToIndex(Pos);
	}

	if (!MovePos)
	{
		State = "Idle";
	}
}
