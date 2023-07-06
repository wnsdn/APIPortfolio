#include "MonsterBoss.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Tile.h"
#include "Water.h"
#include "Bomb.h"
#include "Player.h"
#include "Monster.h"

MonsterBoss::MonsterBoss()
{
}

MonsterBoss::~MonsterBoss()
{
}

void MonsterBoss::Init(const int2& _Pos)
{
	Monster::AddCount(1);
	Index = _Pos;
	Pos = IndexToPos(Index);

	Collider = new GameEngineCollision(Pos + float4::Up * 42, TileSize * 3);

	CreateRenderer("Boss.bmp", RenderOrder::InGameObjectEnd, {}, { 24, 3 });
	FindRenderer("Boss.bmp")->AddPos({ 0, -84 });
	FindRenderer("Boss.bmp")->CreateAnimation("Up", 0, 0, 6, 0.2f, true);
	FindRenderer("Boss.bmp")->CreateAnimation("Down", 6, 0, 6, 0.2f, true);
	FindRenderer("Boss.bmp")->CreateAnimation("Left", 12, 0, 6, 0.2f, true);
	FindRenderer("Boss.bmp")->CreateAnimation("Right", 18, 0, 6, 0.2f, true);
	FindRenderer("Boss.bmp")->CreateAnimation("Capture", 0, 1, 24, 0.2f, false);
	FindRenderer("Boss.bmp")->CreateAnimation("Death", 0, 2, 18, 0.13f, false);
	FindRenderer("Boss.bmp")->CreateAnimation("Idle", 18, 2, 4, 0.4f, true);
	FindRenderer("Boss.bmp")->CreateAnimation("Hit", 22, 2, 2, 0.2f, false);
	FindRenderer("Boss.bmp")->ChangeAnimation("Idle");
	FindRenderer("Boss.bmp")->SetTheFirst(true);

	CreateRenderer("EmptyHp.bmp", RenderOrder::InGameObjectEnd);
	FindRenderer("EmptyHp.bmp")->AddPos({ 0, -163 });
	FindRenderer("EmptyHp.bmp")->SetIsGauge(true);

	CreateRenderer("FullHp.bmp", RenderOrder::InGameObjectEnd);
	FindRenderer("FullHp.bmp")->AddPos({ 0, -163 });
	FindRenderer("FullHp.bmp")->SetIsGauge(true);

	MaxHpBar = FindRenderer("FullHp.bmp")->GetScale().X;
	CurHpBar = MaxHpBar;

	InsertRenderer();

	CreateRenderer("BossShadow.bmp", RenderOrder::Shadow);
	FindRenderer("BossShadow.bmp")->AddScale({ 80, 200 });
	FindRenderer("BossShadow.bmp")->AddPos({ 2, -104 });
	FindRenderer("BossShadow.bmp")->InsertSingleRenderer();

	//CreateRenderer("BossHp.bmp", RenderOrder::InGameObject, {}, { 1, 2 });

	State = "Move";
	Dir = "Down";
}

void MonsterBoss::Update(float _Delta)
{
	HitTimer += _Delta;
	if (LiveTime >= 2.0f && State != "Stop")
	{
		PatternUpdate(_Delta);
		StateUpdate(_Delta);
	}
	CollisionCheck();
	ChangeAnimation();

	MidIdx = Index + int2::Up;
}

void MonsterBoss::Render(float _Delta)
{
	/*DrawRect(IndexToPos(MidIdx), TileSize, Rgb(0, 255, 0));
	DrawRect(Collider->GetPos(), Collider->GetScale(), Rgb(0, 0, 255));*/
}

void MonsterBoss::RandomMove()
{
	switch (GameEngineRandom::RandomInt(3, 0))
	{
	case 0:
		Dir = "Left";
		break;
	case 1:
		Dir = "Right";
		break;
	case 2:
		Dir = "Up";
		break;
	case 3:
		Dir = "Down";
		break;
	}
	State = "Move";
}

void MonsterBoss::ChangeDir()
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
		State = "Idle";
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
	int RndInt = GameEngineRandom::RandomInt(RndCnt, 1);
	Dir = DirArr[RndInt - 1];
}

void MonsterBoss::StateUpdate(float _Delta)
{
	if (State == "Move")
	{
		RunUpdate(_Delta);
	}
	else if (State == "Hit")
	{
		HitUpdate(_Delta);
	}
	else if (State == "Capture")
	{
		CaptureUpdate(_Delta);
	}
	else if (State == "Death")
	{
		DeathUpdate(_Delta);
	}
}

void MonsterBoss::RunUpdate(float _Delta)
{
	float Speed = 50.0f;
	if (Dir == "Left")
	{
		Pos.X -= Speed * _Delta;
		if (Collider->Left() <= MapLeft)
		{
			Pos.X += Speed * _Delta;
			ChangeDir();
		}
	}
	else if (Dir == "Right")
	{
		Pos.X += Speed * _Delta;
		if (Collider->Right() >= MapRight)
		{
			Pos.X -= Speed * _Delta;
			ChangeDir();
		}
	}
	else if (Dir == "Up")
	{
		Pos.Y -= Speed * _Delta;
		if (Collider->Top() <= MapTop)
		{
			Pos.Y += Speed * _Delta;
			ChangeDir();
		}
	}
	else if (Dir == "Down")
	{
		Pos.Y += Speed * _Delta;
		if (Collider->Bottom() >= MapBottom)
		{
			Pos.Y -= Speed * _Delta;
			ChangeDir();
		}
	}

	Index = PosToIndex(Pos);
	Collider->SetPos(Pos + float4::Up * 42);
}

void MonsterBoss::HitUpdate(float _Delta)
{
	if (FindRenderer("Boss.bmp")->IsAnimationEnd("Hit"))
	{
		State = "";
		FindRenderer("Boss.bmp")->ResetAnimation("Hit");
	}
}

void MonsterBoss::CaptureUpdate(float _Delta)
{
	if (FindRenderer("Boss.bmp")->IsAnimationEnd("Capture"))
	{
		GameEngineSound::FindSound("BossDeath.mp3")->Play();
		Monster::SetCount(0);
		State = "Death";
		Player::MainPlayer->AddCurExp(111);
	}
}

void MonsterBoss::DeathUpdate(float _Delta)
{
	if (FindRenderer("Boss.bmp")->IsAnimationEnd("Death"))
	{
		Death();
	}
}

void MonsterBoss::PatternUpdate(float _Delta)
{
	if (State == "Hit" || State == "Capture" || State == "Death")
	{
		return;
	}

	Timer += _Delta;
	if (Pattern == 0)
	{
		if (Timer <= 1.0f)
		{
			if (PState != "Move")
			{
				RandomMove();
				PState = "Move";
			}
		}
		else if (Timer <= 3.0f)
		{
			if (PState != "Idle")
			{
				State = "Idle";
				PState = "Idle";
			}
		}
		else if (Timer <= 4.0f)
		{
			if (PState != "Move")
			{
				RandomMove();
				PState = "Move";
			}
		}
		else if (Timer <= 6.0f)
		{
			if (PState != "Idle")
			{
				State = "Idle";
				PState = "Idle";
			}
		}
		else if (Timer <= 8.0f)
		{
			if (PState != "Water1")
			{
				Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
				WaterPtr->Rect(Index + int2::Up, 3);
				WaterPtr->Death();
				PState = "Water1";
			}
		}
		else if (Timer <= 10.0f)
		{
			if (PState != "Water2")
			{
				Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
				WaterPtr->Rect(Index + int2::Up, 4);
				WaterPtr->Death();
				PState = "Water2";
			}
		}
		else if (Timer <= 12.0f)
		{
			if (PState != "Water1")
			{
				Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
				WaterPtr->Rect(Index + int2::Up, 3);
				WaterPtr->Death();
				PState = "Water1";
			}
		}
		else if (Timer <= 14.0f)
		{
			if (PState != "Water2")
			{
				Water* WaterPtr = Level->CreateActor<Water>(UpdateOrder::Water);
				WaterPtr->Rect(Index + int2::Up, 4);
				WaterPtr->Death();
				PState = "Water2";
			}
		}
		else
		{
			Timer = 0.0f;
			Pattern = 1;
		}
	}
	else if (Pattern == 1)
	{
		if (Timer <= 1.0f)
		{
			if (PState != "Move")
			{
				RandomMove();
				PState = "Move";
			}
		}
		else if (Timer <= 3.0f)
		{
			if (PState != "Idle")
			{
				State = "Idle";
				PState = "Idle";
			}
		}
		else if (Timer <= 4.0f)
		{
			if (PState != "Move")
			{
				RandomMove();
				PState = "Move";
			}
		}
		else if (Timer <= 7.0f)
		{
			if (PState != "Idle")
			{
				State = "Idle";
				PState = "Idle";
			}
		}
		else if (Timer <= 8.0f)
		{
			if (PState != "BombSet")
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (MidIdx == Ptr->GetIndex() &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
					{
						Bomb* BombPtr = Level->CreateActor<Bomb>(UpdateOrder::Bomb);
						BombPtr->Init(MidIdx, 7, nullptr, true);

						for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
						{
							if (Ptr->GetIndex() == MidIdx &&
								!dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
							{
								dynamic_cast<Tile*>(Ptr)->Empty();
							}
						}

						int DelX = MidIdx.X - Player::MainPlayer->GetIndex().X;
						int DelY = MidIdx.Y - Player::MainPlayer->GetIndex().Y;
						int AbsX = abs(DelX);
						int AbsY = abs(DelY);
						std::string BombDir = "";

						if (AbsX >= AbsY)
						{
							if (DelX > 0)
							{
								BombDir = "Left";
							}
							else
							{
								BombDir = "Right";
							}
						}
						else
						{
							if (DelY > 0)
							{
								BombDir = "Up";
							}
							else
							{
								BombDir = "Down";
							}
						}

						BombPtr->SetDir(BombDir);
						Dir = BombDir;
						BombPtr->SetState("Move");

						PState = "BombSet";
					}
				}
			}
		}
		else if (Timer <= 9.0f)
		{
			if (PState != "BombSet1")
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (MidIdx == Ptr->GetIndex() &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
					{
						Bomb* BombPtr = Level->CreateActor<Bomb>(UpdateOrder::Bomb);
						BombPtr->Init(MidIdx, 7, nullptr, true);

						for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
						{
							if (Ptr->GetIndex() == MidIdx &&
								!dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
							{
								dynamic_cast<Tile*>(Ptr)->Empty();
							}
						}

						int DelX = MidIdx.X - Player::MainPlayer->GetIndex().X;
						int DelY = MidIdx.Y - Player::MainPlayer->GetIndex().Y;
						int AbsX = abs(DelX);
						int AbsY = abs(DelY);
						std::string BombDir = "";

						if (AbsX >= AbsY)
						{
							if (DelX > 0)
							{
								BombDir = "Left";
							}
							else
							{
								BombDir = "Right";
							}
						}
						else
						{
							if (DelY > 0)
							{
								BombDir = "Up";
							}
							else
							{
								BombDir = "Down";
							}
						}

						BombPtr->SetDir(BombDir);
						Dir = BombDir;
						BombPtr->SetState("Move");

						PState = "BombSet1";
					}
				}
			}
		}
		else if (Timer <= 10.0f)
		{
			if (PState != "BombSet2")
			{
				for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
				{
					if (MidIdx == Ptr->GetIndex() &&
						dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
					{
						Bomb* BombPtr = Level->CreateActor<Bomb>(UpdateOrder::Bomb);
						BombPtr->Init(MidIdx, 7, nullptr, true);

						for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
						{
							if (Ptr->GetIndex() == MidIdx &&
								!dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
							{
								dynamic_cast<Tile*>(Ptr)->Empty();
							}
						}

						int DelX = MidIdx.X - Player::MainPlayer->GetIndex().X;
						int DelY = MidIdx.Y - Player::MainPlayer->GetIndex().Y;
						int AbsX = abs(DelX);
						int AbsY = abs(DelY);
						std::string BombDir = "";

						if (AbsX >= AbsY)
						{
							if (DelX > 0)
							{
								BombDir = "Left";
							}
							else
							{
								BombDir = "Right";
							}
						}
						else
						{
							if (DelY > 0)
							{
								BombDir = "Up";
							}
							else
							{
								BombDir = "Down";
							}
						}

						BombPtr->SetDir(BombDir);
						Dir = BombDir;
						BombPtr->SetState("Move");

						PState = "BombSet2";
					}
				}
			}
		}
		else
		{
			Timer = 0.0f;
			Pattern = 0;
		}
	}
}

void MonsterBoss::CollisionCheck()
{
	if (State == "Capture" || State == "Death")
	{
		return;
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Bomb))
	{
		if (Ptr->Right() >= Collider->Left() && Ptr->Left() <= Collider->Right() &&
			Ptr->Bottom() >= Collider->Top() && Ptr->Top() <= Collider->Bottom())
		{
			if (dynamic_cast<Bomb*>(Ptr)->GetOwner() &&
				dynamic_cast<Bomb*>(Ptr)->GetState() != "Fly")
			{
				Ptr->Death();
			}
		}
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Water))
	{
		if (Ptr->Right() >= Collider->Left() && Ptr->Left() <= Collider->Right() &&
			Ptr->Bottom() >= Collider->Top() && Ptr->Top() <= Collider->Bottom())
		{
			if (State != "Hit" && HitTimer >= 0.5f)
			{
				GameEngineSound::FindSound("BossHit.mp3")->Play();
				State = "Hit";
				--CurHp;
				HitTimer = 0.0f;

				FindRenderer("FullHp.bmp")->SetAdjPos({ MaxHpBar * (MaxHp - CurHp) / MaxHp, 0 });

				if (CurHp <= 0)
				{
					State = "Capture";
				}
			}
		}
	}
}

void MonsterBoss::ChangeAnimation()
{
	if (State == "Hit" || State == "Capture" || State == "Death")
	{
		FindRenderer("Boss.bmp")->ChangeAnimation(State);
	}
	else
	{
		FindRenderer("Boss.bmp")->ChangeAnimation(Dir);
	}
}
