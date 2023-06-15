#include "Player.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
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
	else if (State == "Capture")
	{
		CaptureUpdate(_Delta);
	}
	else if (State == "Death")
	{
		DeathUpdate(_Delta);
	}
	else if (State == "Free")
	{
		FreeUpdate(_Delta);
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

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Ptr))
			{
				if (Index.X > Ptr->GetIndex().X)
				{
					if (Index.Y == Ptr->GetIndex().Y)
					{
						Pos.X += Speed * _Delta;
					}

					if (Pos.Y > Ptr->GetPos().Y + Ptr->GetScale().hY() * TrimRatio)
					{
						for (auto DownTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (DownTile && (Ptr->GetIndex() + int2::Down) == DownTile->GetIndex()
								&& dynamic_cast<Tile*>(DownTile)->GetIsEmpty())
							{
								Pos.X += Speed * _Delta;
								Pos.Y += Speed * SpeedRatio * _Delta;
							}
						}
					}
					else if (Pos.Y < Ptr->GetPos().Y - Ptr->GetScale().hY() * TrimRatio)
					{
						for (auto UpTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (UpTile && (Ptr->GetIndex() + int2::Up) == UpTile->GetIndex()
								&& dynamic_cast<Tile*>(UpTile)->GetIsEmpty())
							{
								Pos.X += Speed * _Delta;
								Pos.Y -= Speed * SpeedRatio * _Delta;
							}
						}
					}
				}
			}
		}
	}
	else if (GameEngineInput::IsPress(VK_RIGHT) && Dir == "Right")
	{
		Pos.X += Speed * _Delta;
		if (Right() >= MapRight)
		{
			Pos.X -= Speed * _Delta;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Ptr))
			{
				if (Index.X < Ptr->GetIndex().X)
				{
					if (Index.Y == Ptr->GetIndex().Y)
					{
						Pos.X -= Speed * _Delta;
					}

					if (Pos.Y > Ptr->GetPos().Y + Ptr->GetScale().hY() * TrimRatio)
					{
						for (auto DownTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (DownTile && (Ptr->GetIndex() + int2::Down) == DownTile->GetIndex()
								&& dynamic_cast<Tile*>(DownTile)->GetIsEmpty())
							{
								Pos.X -= Speed * _Delta;
								Pos.Y += Speed * SpeedRatio * _Delta;
							}
						}
					}
					else if (Pos.Y < Ptr->GetPos().Y - Ptr->GetScale().hY() * TrimRatio)
					{
						for (auto UpTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (UpTile && (Ptr->GetIndex() + int2::Up) == UpTile->GetIndex()
								&& dynamic_cast<Tile*>(UpTile)->GetIsEmpty())
							{
								Pos.X -= Speed * _Delta;
								Pos.Y -= Speed * SpeedRatio * _Delta;
							}
						}
					}
				}
			}
		}
	}
	else if (GameEngineInput::IsPress(VK_UP) && Dir == "Up")
	{
		Pos.Y -= Speed * _Delta;
		if (Top() <= MapTop)
		{
			Pos.Y += Speed * _Delta;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Ptr))
			{
				if (Index.Y > Ptr->GetIndex().Y)
				{
					if (Index.X == Ptr->GetIndex().X)
					{
						Pos.Y += Speed * _Delta;
					}
					if (Pos.X > Ptr->GetPos().X + Ptr->GetScale().hX() * TrimRatio)
					{
						for (auto RightTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (RightTile && (Ptr->GetIndex() + int2::Right) == RightTile->GetIndex()
								&& dynamic_cast<Tile*>(RightTile)->GetIsEmpty())
							{
								Pos.Y += Speed * _Delta;
								Pos.X += Speed * SpeedRatio * _Delta;
							}
						}
					}
					else if (Pos.X < Ptr->GetPos().X - Ptr->GetScale().hX() * TrimRatio)
					{
						for (auto LeftTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (LeftTile && (Ptr->GetIndex() + int2::Left) == LeftTile->GetIndex()
								&& dynamic_cast<Tile*>(LeftTile)->GetIsEmpty())
							{
								Pos.Y += Speed * _Delta;
								Pos.X -= Speed * SpeedRatio * _Delta;
							}
						}
					}
				}
			}
		}
	}
	else if (GameEngineInput::IsPress(VK_DOWN) && Dir == "Down")
	{
		Pos.Y += Speed * _Delta;
		if (Bottom() >= MapBottom)
		{
			Pos.Y -= Speed * _Delta;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Ptr))
			{
				if (Index.Y < Ptr->GetIndex().Y)
				{
					if (Index.X == Ptr->GetIndex().X)
					{
						Pos.Y -= Speed * _Delta;
					}

					if (Pos.X > Ptr->GetPos().X + Ptr->GetScale().hX() * TrimRatio)
					{
						for (auto RightTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (RightTile && (Ptr->GetIndex() + int2::Right) == RightTile->GetIndex()
								&& dynamic_cast<Tile*>(RightTile)->GetIsEmpty())
							{
								Pos.Y -= Speed * _Delta;
								Pos.X += Speed * SpeedRatio * _Delta;
							}
						}
					}
					else if (Pos.X < Ptr->GetPos().X - Ptr->GetScale().hX() * TrimRatio)
					{
						for (auto LeftTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (LeftTile && (Ptr->GetIndex() + int2::Left) == LeftTile->GetIndex()
								&& dynamic_cast<Tile*>(LeftTile)->GetIsEmpty())
							{
								Pos.Y -= Speed * _Delta;
								Pos.X -= Speed * SpeedRatio * _Delta;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		State = "Idle";
	}

	Index = PosToIndex(Pos);
}

void Player::DeathUpdate(float _Delta)
{
	if (LiveTime >= 2.5f)
	{
		Death();
	}

	if (FindRenderer(Main)->IsAnimationEnd("Death"))
	{
		if (FindRenderer(Main)->GetLiveTime() <= 0.1f)
		{
			FindRenderer("PlayerShadow.bmp")->On();
			FindRenderer(Main)->On();
		}
		else if (FindRenderer(Main)->GetLiveTime() <= 0.2f)
		{
			FindRenderer("PlayerShadow.bmp")->Off();
			FindRenderer(Main)->Off();
		}
		else
		{
			FindRenderer(Main)->ResetLiveTime();
		}
	}
}

void Player::CaptureUpdate(float _Delta)
{
	if (FindRenderer(Main)->IsAnimationEnd("Capture"))
	{
		GameEngineSound::FindSound("PlayerDeath.wav")->Play();

		Dir = "";
		State = "Death";
		LiveTime = 0.0f;
		FindRenderer(Main)->SetPos({ 0, -11 });
		return;
	}

	if (GameEngineInput::IsDown(VK_LCONTROL))
	{
		Dir = "Down";
		if (State == "Capture")
		{
			GameEngineSound::FindSound("PlayerFree.wav")->Play();
			State = "Free";
		}
		FindRenderer(Main)->SetPos({ 0, -11 });
		return;
	}

	Speed = 20.0f;

	FindRenderer(Main)->AddPos({ 0, MoveDir * MoveSpeed * _Delta });
	MoveDist += MoveSpeed * _Delta;
	if (MoveDist >= MaxDist)
	{
		MoveDir *= -1.f;
		MoveDist -= MaxDist;
		FindRenderer(Main)->AddPos({ 0, MoveDir * MoveDist });
	}

	DirCheck();
	if (GameEngineInput::IsPress(VK_LEFT) && Dir == "Left")
	{
		Pos.X -= Speed * _Delta;
		if (Left() <= MapLeft)
		{
			Pos.X += Speed * _Delta;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Ptr))
			{
				if (Index.X > Ptr->GetIndex().X)
				{
					if (Index.Y == Ptr->GetIndex().Y)
					{
						Pos.X += Speed * _Delta;
					}

					if (Pos.Y > Ptr->GetPos().Y + Ptr->GetScale().hY() * TrimRatio)
					{
						for (auto DownTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (DownTile && (Ptr->GetIndex() + int2::Down) == DownTile->GetIndex()
								&& dynamic_cast<Tile*>(DownTile)->GetIsEmpty())
							{
								Pos.X += Speed * _Delta;
								Pos.Y += Speed * SpeedRatio * _Delta;
							}
						}
					}
					else if (Pos.Y < Ptr->GetPos().Y - Ptr->GetScale().hY() * TrimRatio)
					{
						for (auto UpTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (UpTile && (Ptr->GetIndex() + int2::Up) == UpTile->GetIndex()
								&& dynamic_cast<Tile*>(UpTile)->GetIsEmpty())
							{
								Pos.X += Speed * _Delta;
								Pos.Y -= Speed * SpeedRatio * _Delta;
							}
						}
					}
				}
			}
		}
	}
	else if (GameEngineInput::IsPress(VK_RIGHT) && Dir == "Right")
	{
		Pos.X += Speed * _Delta;
		if (Right() >= MapRight)
		{
			Pos.X -= Speed * _Delta;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Ptr))
			{
				if (Index.X < Ptr->GetIndex().X)
				{
					if (Index.Y == Ptr->GetIndex().Y)
					{
						Pos.X -= Speed * _Delta;
					}

					if (Pos.Y > Ptr->GetPos().Y + Ptr->GetScale().hY() * TrimRatio)
					{
						for (auto DownTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (DownTile && (Ptr->GetIndex() + int2::Down) == DownTile->GetIndex()
								&& dynamic_cast<Tile*>(DownTile)->GetIsEmpty())
							{
								Pos.X -= Speed * _Delta;
								Pos.Y += Speed * SpeedRatio * _Delta;
							}
						}
					}
					else if (Pos.Y < Ptr->GetPos().Y - Ptr->GetScale().hY() * TrimRatio)
					{
						for (auto UpTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (UpTile && (Ptr->GetIndex() + int2::Up) == UpTile->GetIndex()
								&& dynamic_cast<Tile*>(UpTile)->GetIsEmpty())
							{
								Pos.X -= Speed * _Delta;
								Pos.Y -= Speed * SpeedRatio * _Delta;
							}
						}
					}
				}
			}
		}
	}
	else if (GameEngineInput::IsPress(VK_UP) && Dir == "Up")
	{
		Pos.Y -= Speed * _Delta;
		if (Top() <= MapTop)
		{
			Pos.Y += Speed * _Delta;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Ptr))
			{
				if (Index.Y > Ptr->GetIndex().Y)
				{
					if (Index.X == Ptr->GetIndex().X)
					{
						Pos.Y += Speed * _Delta;
					}
					if (Pos.X > Ptr->GetPos().X + Ptr->GetScale().hX() * TrimRatio)
					{
						for (auto RightTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (RightTile && (Ptr->GetIndex() + int2::Right) == RightTile->GetIndex()
								&& dynamic_cast<Tile*>(RightTile)->GetIsEmpty())
							{
								Pos.Y += Speed * _Delta;
								Pos.X += Speed * SpeedRatio * _Delta;
							}
						}
					}
					else if (Pos.X < Ptr->GetPos().X - Ptr->GetScale().hX() * TrimRatio)
					{
						for (auto LeftTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (LeftTile && (Ptr->GetIndex() + int2::Left) == LeftTile->GetIndex()
								&& dynamic_cast<Tile*>(LeftTile)->GetIsEmpty())
							{
								Pos.Y += Speed * _Delta;
								Pos.X -= Speed * SpeedRatio * _Delta;
							}
						}
					}
				}
			}
		}
	}
	else if (GameEngineInput::IsPress(VK_DOWN) && Dir == "Down")
	{
		Pos.Y += Speed * _Delta;
		if (Bottom() >= MapBottom)
		{
			Pos.Y -= Speed * _Delta;
		}

		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				continue;
			}

			if (GameEngineCollision::CollisionCheck(this, Ptr))
			{
				if (Index.Y < Ptr->GetIndex().Y)
				{
					if (Index.X == Ptr->GetIndex().X)
					{
						Pos.Y -= Speed * _Delta;
					}

					if (Pos.X > Ptr->GetPos().X + Ptr->GetScale().hX() * TrimRatio)
					{
						for (auto RightTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (RightTile && (Ptr->GetIndex() + int2::Right) == RightTile->GetIndex()
								&& dynamic_cast<Tile*>(RightTile)->GetIsEmpty())
							{
								Pos.Y -= Speed * _Delta;
								Pos.X += Speed * SpeedRatio * _Delta;
							}
						}
					}
					else if (Pos.X < Ptr->GetPos().X - Ptr->GetScale().hX() * TrimRatio)
					{
						for (auto LeftTile : Level->FindActor(UpdateOrder::Tile))
						{
							if (LeftTile && (Ptr->GetIndex() + int2::Left) == LeftTile->GetIndex()
								&& dynamic_cast<Tile*>(LeftTile)->GetIsEmpty())
							{
								Pos.Y -= Speed * _Delta;
								Pos.X -= Speed * SpeedRatio * _Delta;
							}
						}
					}
				}
			}
		}
	}
	Index = PosToIndex(Pos);
}

void Player::FreeUpdate(float _Delta)
{
	if (GameEngineInput::IsPress(VK_UP))
	{
		Dir = "Up";
	}
	else if (GameEngineInput::IsPress(VK_DOWN))
	{
		Dir = "Down";
	}
	else if (GameEngineInput::IsPress(VK_LEFT))
	{
		Dir = "Left";
	}
	else if (GameEngineInput::IsPress(VK_RIGHT))
	{
		Dir = "Right";
	}

	if (FindRenderer(Main)->IsAnimationEnd("Free"))
	{
		State = "Run";
		LiveTime = 0.0f;
		FindRenderer(Main)->ResetAnimation("Free");
	}
}
