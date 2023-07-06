#include "MonsterLevel.h"
#include <GameEngineCore/GameEngineProcess.h>

#include "TitleLevel.h"
#include "Player.h"

void MonsterLevel::StateUpdate(float _Delta)
{
	if (State == "Start")
	{
		StartUpdate(_Delta);
	}
	else if (State == "InGame")
	{
		InGameUpdate(_Delta);
	}
	else if (State == "Win")
	{
		WinUpdate(_Delta);
	}
	else if (State == "Lose")
	{
		LoseUpdate(_Delta);
	}
}

void MonsterLevel::StartUpdate(float _Delta)
{
	CuratinUpdate(_Delta);
	OutButtonUpdate(_Delta);
}

void MonsterLevel::InGameUpdate(float _Delta)
{
	PlayerCheck();
	MonsterCheck();
	TimeCheck();
	OutButtonUpdate(_Delta);
}

void MonsterLevel::WinUpdate(float _Delta)
{
	static bool Check = false;

	if (!Check)
	{
		Player::MainPlayer->WriteData();

		Check = true;
	}

	//10초 지나면 다음 스테이지로 넘어가는 기능
	if (LiveTime >= 5.0f)
	{
		if (CurMap == "Octopus.txt")
		{
			Process->CreateLevel<MonsterLevel>()->Init("Octopus1.txt");
		}
		else if (CurMap == "Octopus1.txt")
		{
			Process->CreateLevel<MonsterLevel>()->Init("Boss.txt");
		}
		else if (CurMap == "Boss.txt")
		{
			Process->CreateLevel<MonsterLevel>()->Init("test.txt");
		}

		Check = false;
	}

	OutButtonUpdate(_Delta);
}

void MonsterLevel::LoseUpdate(float _Delta)
{
	if (LiveTime >= 10.0f)
	{
		Process->CreateLevel<TitleLevel>();
	}

	OutButtonUpdate(_Delta);
}
