#include "MonsterLevel.h"
#include <GameEngineCore/GameEngineProcess.h>

#include "TitleLevel.h"

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
	else if (State == "Lose")
	{
		LoseUpdate(_Delta);
	}
}

void MonsterLevel::StartUpdate(float _Delta)
{
	CuratinUpdate(_Delta);
}

void MonsterLevel::InGameUpdate(float _Delta)
{
	PlayerCheck();
	OutButtonUpdate();
}

void MonsterLevel::LoseUpdate(float _Delta)
{
	LiveTime += _Delta;
	
	if (LiveTime >= 20.0f)
	{
		Process->CreateLevel<TitleLevel>();
	}
}
