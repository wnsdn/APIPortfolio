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
	if (State == "Ready")
	{
		ReadyUpdate(_Delta);
	}
	else if (State == "Idle")
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
	else if (State == "Stop")
	{
		StopUpdate(_Delta);
	}
	else if (State == "Jump")
	{
		JumpUpdate(_Delta);
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

void Player::ReadyUpdate(float _Delta)
{
	if (FindRenderer("BazziReady.bmp")->IsAnimationEnd("Ready"))
	{
		Dir = "Down";
		State = "Idle";
		FindRenderer("BazziReady.bmp")->Off();
		FindRenderer(Main)->On();
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

		for (auto LeftTile : Level->FindActor(UpdateOrder::Tile))
		{
			if (LeftTile->GetIndex() == Index + int2::Left &&
				!dynamic_cast<Tile*>(LeftTile)->GetIsEmpty() &&
				Left() <= LeftTile->Right())
			{
				Pos.X += Speed * _Delta;
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpLeft &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.Y < LeftTile->GetPos().Y - LeftTile->GetScale().hY() * TrimRatio)
					{
						Pos.Y -= Speed * _Delta * SpeedRatio;
					}
					if (Ptr->GetIndex() == Index + int2::DownLeft &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.Y > LeftTile->GetPos().Y + LeftTile->GetScale().hY() * TrimRatio)
					{
						Pos.Y += Speed * _Delta * SpeedRatio;
					}
				}
			}
			else if (LeftTile->GetIndex() == Index + int2::Left &&
				dynamic_cast<Tile*>(LeftTile)->GetIsEmpty())
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpLeft &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Left() <= Ptr->Right() && Top() <= Ptr->Bottom())
					{
						Pos.X += Speed * _Delta;
						Pos.Y += Speed * _Delta * SpeedRatio;
						if (Pos.Y > IndexToPos(Index).Y)
						{
							Pos.Y = IndexToPos(Index).Y;
						}
					}
					else if (Ptr->GetIndex() == Index + int2::DownLeft &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Left() <= Ptr->Right() && Bottom() >= Ptr->Top())
					{
						Pos.X += Speed * _Delta;
						Pos.Y -= Speed * _Delta * SpeedRatio;
						if (Pos.Y < IndexToPos(Index).Y)
						{
							Pos.Y = IndexToPos(Index).Y;
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

		for (auto RightTile : Level->FindActor(UpdateOrder::Tile))
		{
			if (RightTile->GetIndex() == Index + int2::Right &&
				!dynamic_cast<Tile*>(RightTile)->GetIsEmpty() &&
				Right() >= RightTile->Left())
			{
				Pos.X -= Speed * _Delta;
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpRight &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.Y < RightTile->GetPos().Y - RightTile->GetScale().hY() * TrimRatio)
					{
						Pos.Y -= Speed * _Delta * SpeedRatio;
					}
					if (Ptr->GetIndex() == Index + int2::DownRight &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.Y > RightTile->GetPos().Y + RightTile->GetScale().hY() * TrimRatio)
					{
						Pos.Y += Speed * _Delta * SpeedRatio;
					}
				}
			}
			else if (RightTile->GetIndex() == Index + int2::Right &&
				dynamic_cast<Tile*>(RightTile)->GetIsEmpty())
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpRight &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Right() >= Ptr->Left() && Top() <= Ptr->Bottom())
					{
						Pos.X -= Speed * _Delta;
						Pos.Y += Speed * _Delta * SpeedRatio;
						if (Pos.Y > IndexToPos(Index).Y)
						{
							Pos.Y = IndexToPos(Index).Y;
						}
					}
					else if (Ptr->GetIndex() == Index + int2::DownRight &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Right() >= Ptr->Left() && Bottom() >= Ptr->Top())
					{
						Pos.X -= Speed * _Delta;
						Pos.Y -= Speed * _Delta * SpeedRatio;
						if (Pos.Y < IndexToPos(Index).Y)
						{
							Pos.Y = IndexToPos(Index).Y;
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

		for (auto UpTile : Level->FindActor(UpdateOrder::Tile))
		{
			if (UpTile->GetIndex() == Index + int2::Up &&
				!dynamic_cast<Tile*>(UpTile)->GetIsEmpty() &&
				Top() <= UpTile->Bottom())
			{
				Pos.Y += Speed * _Delta;
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpLeft &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.X < UpTile->GetPos().X - UpTile->GetScale().hX() * TrimRatio)
					{
						Pos.X -= Speed * _Delta * SpeedRatio;
					}
					if (Ptr->GetIndex() == Index + int2::UpRight &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.X > UpTile->GetPos().X + UpTile->GetScale().hX() * TrimRatio)
					{
						Pos.X += Speed * _Delta * SpeedRatio;
					}
				}
			}
			else if (UpTile->GetIndex() == Index + int2::Up &&
				dynamic_cast<Tile*>(UpTile)->GetIsEmpty())
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpLeft &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Top() <= Ptr->Bottom() && Left() <= Ptr->Right())
					{
						Pos.Y += Speed * _Delta;
						Pos.X += Speed * _Delta * SpeedRatio;
						if (Pos.X > IndexToPos(Index).X)
						{
							Pos.X = IndexToPos(Index).X;
						}
					}
					else if (Ptr->GetIndex() == Index + int2::UpRight &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Top() <= Ptr->Bottom() && Right() >= Ptr->Left())
					{
						Pos.Y += Speed * _Delta;
						Pos.X -= Speed * _Delta * SpeedRatio;
						if (Pos.X < IndexToPos(Index).X)
						{
							Pos.X = IndexToPos(Index).X;
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

		for (auto DownTile : Level->FindActor(UpdateOrder::Tile))
		{
			if (DownTile->GetIndex() == Index + int2::Down &&
				!dynamic_cast<Tile*>(DownTile)->GetIsEmpty() &&
				Bottom() >= DownTile->Top())
			{
				Pos.Y -= Speed * _Delta;
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::DownLeft &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.X < DownTile->GetPos().X - DownTile->GetScale().hX() * TrimRatio)
					{
						Pos.X -= Speed * _Delta * SpeedRatio;
					}
					if (Ptr->GetIndex() == Index + int2::DownRight &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.X > DownTile->GetPos().X + DownTile->GetScale().hX() * TrimRatio)
					{
						Pos.X += Speed * _Delta * SpeedRatio;
					}
				}
			}
			else if (DownTile->GetIndex() == Index + int2::Down &&
				dynamic_cast<Tile*>(DownTile)->GetIsEmpty())
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::DownLeft &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Bottom() >= Ptr->Top() && Left() <= Ptr->Right())
					{
						Pos.Y -= Speed * _Delta;
						Pos.X += Speed * _Delta * SpeedRatio;
						if (Pos.X > IndexToPos(Index).X)
						{
							Pos.X = IndexToPos(Index).X;
						}
					}
					else if (Ptr->GetIndex() == Index + int2::DownRight &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Bottom() >= Ptr->Top() && Right() >= Ptr->Left())
					{
						Pos.Y -= Speed * _Delta;
						Pos.X -= Speed * _Delta * SpeedRatio;
						if (Pos.X < IndexToPos(Index).X)
						{
							Pos.X = IndexToPos(Index).X;
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
		Off();
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

		for (auto LeftTile : Level->FindActor(UpdateOrder::Tile))
		{
			if (LeftTile->GetIndex() == Index + int2::Left &&
				!dynamic_cast<Tile*>(LeftTile)->GetIsEmpty() &&
				Left() <= LeftTile->Right())
			{
				Pos.X += Speed * _Delta;
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpLeft &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.Y < LeftTile->GetPos().Y - LeftTile->GetScale().hY() * TrimRatio)
					{
						Pos.Y -= Speed * _Delta * SpeedRatio;
					}
					if (Ptr->GetIndex() == Index + int2::DownLeft &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.Y > LeftTile->GetPos().Y + LeftTile->GetScale().hY() * TrimRatio)
					{
						Pos.Y += Speed * _Delta * SpeedRatio;
					}
				}
			}
			else if (LeftTile->GetIndex() == Index + int2::Left &&
				dynamic_cast<Tile*>(LeftTile)->GetIsEmpty())
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpLeft &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Left() <= Ptr->Right() && Top() <= Ptr->Bottom())
					{
						Pos.X += Speed * _Delta;
						Pos.Y += Speed * _Delta * SpeedRatio;
						if (Pos.Y > IndexToPos(Index).Y)
						{
							Pos.Y = IndexToPos(Index).Y;
						}
					}
					else if (Ptr->GetIndex() == Index + int2::DownLeft &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Left() <= Ptr->Right() && Bottom() >= Ptr->Top())
					{
						Pos.X += Speed * _Delta;
						Pos.Y -= Speed * _Delta * SpeedRatio;
						if (Pos.Y < IndexToPos(Index).Y)
						{
							Pos.Y = IndexToPos(Index).Y;
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

		for (auto RightTile : Level->FindActor(UpdateOrder::Tile))
		{
			if (RightTile->GetIndex() == Index + int2::Right &&
				!dynamic_cast<Tile*>(RightTile)->GetIsEmpty() &&
				Right() >= RightTile->Left())
			{
				Pos.X -= Speed * _Delta;
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpRight &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.Y < RightTile->GetPos().Y - RightTile->GetScale().hY() * TrimRatio)
					{
						Pos.Y -= Speed * _Delta * SpeedRatio;
					}
					if (Ptr->GetIndex() == Index + int2::DownRight &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.Y > RightTile->GetPos().Y + RightTile->GetScale().hY() * TrimRatio)
					{
						Pos.Y += Speed * _Delta * SpeedRatio;
					}
				}
			}
			else if (RightTile->GetIndex() == Index + int2::Right &&
				dynamic_cast<Tile*>(RightTile)->GetIsEmpty())
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpRight &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Right() >= Ptr->Left() && Top() <= Ptr->Bottom())
					{
						Pos.X -= Speed * _Delta;
						Pos.Y += Speed * _Delta * SpeedRatio;
						if (Pos.Y > IndexToPos(Index).Y)
						{
							Pos.Y = IndexToPos(Index).Y;
						}
					}
					else if (Ptr->GetIndex() == Index + int2::DownRight &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Right() >= Ptr->Left() && Bottom() >= Ptr->Top())
					{
						Pos.X -= Speed * _Delta;
						Pos.Y -= Speed * _Delta * SpeedRatio;
						if (Pos.Y < IndexToPos(Index).Y)
						{
							Pos.Y = IndexToPos(Index).Y;
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

		for (auto UpTile : Level->FindActor(UpdateOrder::Tile))
		{
			if (UpTile->GetIndex() == Index + int2::Up &&
				!dynamic_cast<Tile*>(UpTile)->GetIsEmpty() &&
				Top() <= UpTile->Bottom())
			{
				Pos.Y += Speed * _Delta;
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpLeft &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.X < UpTile->GetPos().X - UpTile->GetScale().hX() * TrimRatio)
					{
						Pos.X -= Speed * _Delta * SpeedRatio;
					}
					if (Ptr->GetIndex() == Index + int2::UpRight &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.X > UpTile->GetPos().X + UpTile->GetScale().hX() * TrimRatio)
					{
						Pos.X += Speed * _Delta * SpeedRatio;
					}
				}
			}
			else if (UpTile->GetIndex() == Index + int2::Up &&
				dynamic_cast<Tile*>(UpTile)->GetIsEmpty())
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::UpLeft &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Top() <= Ptr->Bottom() && Left() <= Ptr->Right())
					{
						Pos.Y += Speed * _Delta;
						Pos.X += Speed * _Delta * SpeedRatio;
						if (Pos.X > IndexToPos(Index).X)
						{
							Pos.X = IndexToPos(Index).X;
						}
					}
					else if (Ptr->GetIndex() == Index + int2::UpRight &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Top() <= Ptr->Bottom() && Right() >= Ptr->Left())
					{
						Pos.Y += Speed * _Delta;
						Pos.X -= Speed * _Delta * SpeedRatio;
						if (Pos.X < IndexToPos(Index).X)
						{
							Pos.X = IndexToPos(Index).X;
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

		for (auto DownTile : Level->FindActor(UpdateOrder::Tile))
		{
			if (DownTile->GetIndex() == Index + int2::Down &&
				!dynamic_cast<Tile*>(DownTile)->GetIsEmpty() &&
				Bottom() >= DownTile->Top())
			{
				Pos.Y -= Speed * _Delta;
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::DownLeft &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.X < DownTile->GetPos().X - DownTile->GetScale().hX() * TrimRatio)
					{
						Pos.X -= Speed * _Delta * SpeedRatio;
					}
					if (Ptr->GetIndex() == Index + int2::DownRight &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Pos.X > DownTile->GetPos().X + DownTile->GetScale().hX() * TrimRatio)
					{
						Pos.X += Speed * _Delta * SpeedRatio;
					}
				}
			}
			else if (DownTile->GetIndex() == Index + int2::Down &&
				dynamic_cast<Tile*>(DownTile)->GetIsEmpty())
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (Ptr->GetIndex() == Index + int2::DownLeft &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Bottom() >= Ptr->Top() && Left() <= Ptr->Right())
					{
						Pos.Y -= Speed * _Delta;
						Pos.X += Speed * _Delta * SpeedRatio;
						if (Pos.X > IndexToPos(Index).X)
						{
							Pos.X = IndexToPos(Index).X;
						}
					}
					else if (Ptr->GetIndex() == Index + int2::DownRight &&
						!dynamic_cast<Tile*>(Ptr)->GetIsEmpty() &&
						Bottom() >= Ptr->Top() && Right() >= Ptr->Left())
					{
						Pos.Y -= Speed * _Delta;
						Pos.X -= Speed * _Delta * SpeedRatio;
						if (Pos.X < IndexToPos(Index).X)
						{
							Pos.X = IndexToPos(Index).X;
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

void Player::StopUpdate(float _Delta)
{
}

void Player::JumpUpdate(float _Delta)
{
	JumpSpeed = JumpMaxDist / 0.3f;
	RendererSpeed = 200.0f;

	if (!JumpDown && RendererDist <= TileSize.X)
	{
		FindRenderer(Main)->AddPos({ 0, -RendererSpeed * _Delta });
		RendererDist += RendererSpeed * _Delta;
	}
	else if (JumpDown && RendererDist >= 0.0f)
	{
		FindRenderer(Main)->AddPos({ 0, RendererSpeed * _Delta });
		RendererDist -= RendererSpeed * _Delta;
	}

	if (Dir == "Left")
	{
		Pos.X -= JumpSpeed * _Delta;
	}
	else if (Dir == "Right")
	{
		Pos.X += JumpSpeed * _Delta;

	}
	else if (Dir == "Up")
	{
		Pos.Y -= JumpSpeed * _Delta;

	}
	else if (Dir == "Down")
	{
		Pos.Y += JumpSpeed * _Delta;

	}

	Index = PosToIndex(Pos);
	JumpDist += JumpSpeed * _Delta;

	if (JumpDist >= JumpMaxDist / 2)
	{
		JumpDown = true;
	}

	if (JumpDist >= JumpMaxDist)
	{
		State = "Idle";
		JumpDist = 0.0f;
		JumpMaxDist = 0.0f;
		JumpSpeed = 0.0f;

		RendererDist = 0.0f;
		JumpDown = false;
		FindRenderer(Main)->SetPos({ 0, -11 });
		FindRenderer(Main)->SetTheFirst(false);

		if (Dir == "Left" || Dir == "Right")
		{
			Pos.X = IndexToPos(Index).X;
		}
		else if (Dir == "Up" || Dir == "Down")
		{
			Pos.Y = IndexToPos(Index).Y;
		}
	}
}
