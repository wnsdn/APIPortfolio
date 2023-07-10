#include "Player.h"
#include <fstream>
#include <format>
#include <sstream>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Global.h"
#include "Bomb.h"
#include "Tile.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
	if (Collider)
	{
		delete Collider;
		Collider = nullptr;
	}
}

void Player::Init(const int2& _Index, const std::string& _Path)
{
	Main = _Path;
	Collider = new GameEngineCollision(Pos, { 30, 30 });

	Count = 1;
	MaxCount = 6;
	Length = 1;
	MaxLength = 7;
	StdSpeed = 33.f;
	CurSpeed = 5.0f;
	Speed = CurSpeed * StdSpeed;
	MaxSpeed = 9.f;
	Dir = "";
	State = "Ready";

	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize - 1;

	CreateRenderer(Main, RenderOrder::InGameObject, { 0, 0 }, { 5, 7 });
	FindRenderer(Main)->CreateAnimation("UpRun", 1, 0, 4, 0.15f, true);
	FindRenderer(Main)->CreateAnimation("DownRun", 1, 1, 4, 0.15f, true);
	FindRenderer(Main)->CreateAnimation("RightRun", 1, 2, 3, 0.15f, true);
	FindRenderer(Main)->CreateAnimation("LeftRun", 0, 3, 3, 0.15f, true);
	FindRenderer(Main)->CreateAnimation("UpIdle", 0, 0, 1, 0.0f, false);
	FindRenderer(Main)->CreateAnimation("DownIdle", 0, 1, 1, 0.0f, false);
	FindRenderer(Main)->CreateAnimation("RightIdle", 0, 2, 1, 0.0f, false);
	FindRenderer(Main)->CreateAnimation("LeftIdle", 3, 3, 1, 0.0f, false);
	FindRenderer(Main)->CreateAnimation("Capture", 0, 4, 4, 1.5f, false);
	FindRenderer(Main)->CreateAnimation("Free", 0, 5, 5, 0.05f, false);
	FindRenderer(Main)->CreateAnimation("Death", 0, 6, 5, 0.1f, false);
	FindRenderer(Main)->SetPos({ 0, -11 });
	FindRenderer(Main)->Off();

	CreateRenderer("BazziReady.bmp", RenderOrder::InGameObject, {}, { 18, 1 });
	FindRenderer("BazziReady.bmp")->CreateAnimation("Ready", 0, 0, 18, 0.07f, false);
	FindRenderer("BazziReady.bmp")->SetPos({ -2, -13 });
	FindRenderer("BazziReady.bmp")->AddScale({ 3, 0 });
	FindRenderer("BazziReady.bmp")->ChangeAnimation("Ready");

	CreateRenderer("PlayerShield.bmp", RenderOrder::InGameObject, {}, { 4, 1 });
	FindRenderer("PlayerShield.bmp")->CreateAnimation("Shield", 0, 0, 4, 0.03f, true);
	FindRenderer("PlayerShield.bmp")->SetPos({ 0, -13 });
	FindRenderer("PlayerShield.bmp")->ChangeAnimation("Shield");
	FindRenderer("PlayerShield.bmp")->Off();

	InsertRenderer();

	CreateRenderer("PlayerShadow.bmp", RenderOrder::Shadow);
	FindRenderer("PlayerShadow.bmp")->SetPos({ -1.f, -1.4f });
	FindRenderer("PlayerShadow.bmp")->InsertSingleRenderer();
}

void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
	CollisionCheck(_Delta);
	AllUpdate(_Delta);

	if (GameEngineInput::IsDown('Q'))
	{
		if (GodMode)
		{
			GodMode = false;
		}
		else
		{
			GodMode = true;
		}
	}
	if (GameEngineInput::IsDown('A'))
	{
		++Count;
	}
	if (GameEngineInput::IsDown('Z'))
	{
		--Count;
	}
	if (GameEngineInput::IsDown('S'))
	{
		++Length;
	}
	if (GameEngineInput::IsDown('X'))
	{
		--Length;
	}
	if (GameEngineInput::IsDown('D'))
	{
		++CurSpeed;
	}
	if (GameEngineInput::IsDown('C'))
	{
		--CurSpeed;
	}
	if (GameEngineInput::IsDown('F'))
	{
		++ItemNeedle;
	}
	if (GameEngineInput::IsDown('V'))
	{
		--ItemNeedle;
	}
	if (GameEngineInput::IsDown('G'))
	{
		++ItemShield;
	}
	if (GameEngineInput::IsDown('B'))
	{
		--ItemShield;
	}
	if (GameEngineInput::IsDown('H'))
	{
		++ItemJump;
	}
	if (GameEngineInput::IsDown('N'))
	{
		--ItemJump;
	}
	if (GameEngineInput::IsDown('E'))
	{
		if (CanKick)
		{
			CanKick = false;
		}
		else
		{
			CanKick = true;
		}
	}
	if (GameEngineInput::IsDown('R'))
	{
		if (CanThrow)
		{
			CanThrow = false;
		}
		else
		{
			CanThrow = true;
		}
	}
}

void Player::Render(float _Delta)
{
	//DrawRect(Pos, Scale, RGB(255, 0, 0));
	/*DrawRect(IndexToPos(Index), Scale, RGB(0, 255, 0));
	DrawRect(Collider->GetPos(), Collider->GetScale(), RGB(255, 0, 0));

	for (int i = 2; i <= 4; ++i)
	{
		for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
		{
			if (Ptr->GetIndex() == Index + int2::Left * i &&
				dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				DrawRect(IndexToPos(Index + int2::Left * i), Scale, RGB(0, 0, 255));
			}
			else if (Ptr->GetIndex() == Index + int2::Left * i &&
				!dynamic_cast<Tile*>(Ptr)->GetIsEmpty())
			{
				DrawRect(IndexToPos(Index + int2::Left * i), Scale, RGB(255, 0, 0));
			}
		}
	}*/

	/*HDC Hdc = GameEngineWindow::GetInst().GetBackBuffer()->GetImageDC();

	std::string Buffer(std::format("{},{},{}", Rank, CurExp, MaxExp));
	TextOut(Hdc, 200, 2, &Buffer[0], static_cast<int>(Buffer.size()));*/
}

void Player::Stop()
{
	Dir = "";
	State = "Stop";
	FindRenderer(Main)->SetPos({ 0, -11 });
}

void Player::WriteData()
{
	std::string Filename = GameEnginePath::FilenameToPath("PlayerData.txt");
	std::ofstream Ofs(Filename);

	if (Ofs)
	{
		std::string Buffer(std::format("{},{}", Rank, CurExp));
		Ofs.write(&Buffer[0], Buffer.size());
	}
}

void Player::ReadData()
{
	std::string Filename = GameEnginePath::FilenameToPath("PlayerData.txt");
	std::ifstream Ifs(Filename);

	if (Ifs)
	{
		std::string Str = "";

		std::getline(Ifs, Str, '\n');
		std::stringstream SStream(Str);

		Rank = 0;
		CurExp = 0;

		std::getline(SStream, Str, ',');
		for (int i = 0; i < Str.size(); ++i)
		{
			Rank += static_cast<int>(Str[i] - '0');
			if (i != Str.size() - 1)
			{
				Rank *= 10;
			}
		}

		std::getline(SStream, Str, ',');
		for (int i = 0; i < Str.size(); ++i)
		{
			CurExp += static_cast<int>(Str[i] - '0');
			if (i != Str.size() - 1)
			{
				CurExp *= 10;
			}
		}

		MaxExp = (Rank + 1) * 100;
	}

	while (CurExp >= MaxExp)
	{
		CurExp -= MaxExp;
		++Rank;
		if (Rank >= 19)
		{
			Rank = 19;
		}

		MaxExp = (Rank + 1) * 100;
	}
}
