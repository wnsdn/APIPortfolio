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
	OutButtonUpdate(_Delta);
}

void MonsterLevel::WinUpdate(float _Delta)
{
	//10�� ������ ���� ���������� �Ѿ�� ���
	if (LiveTime >= 10.0f)
	{

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
