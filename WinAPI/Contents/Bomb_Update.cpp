#include "Bomb.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Player.h"
#include "Tile.h"


void Bomb::CollisionCheck(float _Delta)
{
	if (!Player::MainPlayer)
	{
		return;
	}

	KickUpdate(_Delta);
}

void Bomb::KickUpdate(float _Delta)
{
	if (!Player::MainPlayer->GetCanKick())
	{
		return;
	}

	if (Player::MainPlayer->GetIndex() == Index + int2::Right &&
		Player::MainPlayer->Left() <= Right() + 2 &&
		Player::MainPlayer->GetState() == "Run" &&
		Player::MainPlayer->GetDir() == "Left")
	{
		LeftMove += _Delta;
		RightMove = 0.0f;
		UpMove = 0.0f;
		DownMove = 0.0f;

		if (Index.X == 0)
		{
			LeftMove = 0;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr->GetIndex() == Index + int2::Left &&
				!dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				LeftMove = 0.0f;
			}
		}

		for (auto MonPtr : Level->FindActor(UpdateOrder::Monster))
		{
			if (MonPtr->GetIndex() == Index + int2::Left)
			{
				LeftMove = 0.0f;
			}
		}

		if (LeftMove >= 0.1f)
		{
			State = "Move";
			Dir = "Left";
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr->GetIndex() == Index)
				{
					dynamic_cast<Tile*>(Ptr)->Empty();
				}
			}
			GameEngineSound::FindSound("PlayerKick.mp3")->Play();
			LeftMove = 0.0f;
			LiveTime = 0.0f;
		}
	}
	else if (Player::MainPlayer->GetIndex() == Index + int2::Left &&
		Player::MainPlayer->Right() >= Left() - 2 &&
		Player::MainPlayer->GetState() == "Run" &&
		Player::MainPlayer->GetDir() == "Right")
	{
		LeftMove = 0.0f;
		RightMove += _Delta;
		UpMove = 0.0f;
		DownMove = 0.0f;

		if (Index.X == 14)
		{
			RightMove = 0;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr->GetIndex() == Index + int2::Right &&
				!dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				RightMove = 0.0f;
			}
		}

		for (auto MonPtr : Level->FindActor(UpdateOrder::Monster))
		{
			if (MonPtr->GetIndex() == Index + int2::Right)
			{
				RightMove = 0.0f;
			}
		}

		if (RightMove >= 0.1f)
		{
			State = "Move";
			Dir = "Right";
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr->GetIndex() == Index)
				{
					dynamic_cast<Tile*>(Ptr)->Empty();
				}
			}
			GameEngineSound::FindSound("PlayerKick.mp3")->Play();
			RightMove = 0.0f;
			LiveTime = 0.0f;
		}
	}
	else if (Player::MainPlayer->GetIndex() == Index + int2::Down &&
		Player::MainPlayer->Top() <= Bottom() + 2 &&
		Player::MainPlayer->GetState() == "Run" &&
		Player::MainPlayer->GetDir() == "Up")
	{
		LeftMove = 0.0f;
		RightMove = 0.0f;
		UpMove += _Delta;
		DownMove = 0.0f;

		if (Index.Y == 0)
		{
			UpMove = 0;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr->GetIndex() == Index + int2::Up &&
				!dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				UpMove = 0.0f;
			}
		}

		for (auto MonPtr : Level->FindActor(UpdateOrder::Monster))
		{
			if (MonPtr->GetIndex() == Index + int2::Up)
			{
				UpMove = 0.0f;
			}
		}

		if (UpMove >= 0.1f)
		{
			State = "Move";
			Dir = "Up";
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr->GetIndex() == Index)
				{
					dynamic_cast<Tile*>(Ptr)->Empty();
				}
			}
			GameEngineSound::FindSound("PlayerKick.mp3")->Play();
			UpMove = 0.0f;
			LiveTime = 0.0f;
		}
	}
	else if (Player::MainPlayer->GetIndex() == Index + int2::Up &&
		Player::MainPlayer->Bottom() >= Top() - 2 &&
		Player::MainPlayer->GetState() == "Run" &&
		Player::MainPlayer->GetDir() == "Down")
	{
		LeftMove = 0.0f;
		RightMove = 0.0f;
		UpMove = 0.0f;
		DownMove += _Delta;

		if (Index.Y == 12)
		{
			DownMove = 0;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr->GetIndex() == Index + int2::Down &&
				!dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				DownMove = 0.0f;
			}
		}

		for (auto MonPtr : Level->FindActor(UpdateOrder::Monster))
		{
			if (MonPtr->GetIndex() == Index + int2::Down)
			{
				DownMove = 0.0f;
			}
		}

		if (DownMove >= 0.1f)
		{
			State = "Move";
			Dir = "Down";
			for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
			{
				if (Ptr->GetIndex() == Index)
				{
					dynamic_cast<Tile*>(Ptr)->Empty();
				}
			}
			GameEngineSound::FindSound("PlayerKick.mp3")->Play();
			DownMove = 0.0f;
			LiveTime = 0.0f;
		}
	}
	else if (Player::MainPlayer->GetState() != "Run")
	{
		LeftMove = 0.0f;
		RightMove = 0.0f;
		UpMove = 0.0f;
		DownMove = 0.0f;
	}
}
