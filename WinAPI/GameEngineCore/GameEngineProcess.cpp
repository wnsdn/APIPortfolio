#include "GameEngineProcess.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineLevel.h"

GameEngineProcess::GameEngineProcess()
{
}

GameEngineProcess::~GameEngineProcess()
{
	for (auto& Pair : AllLevel)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
}

void GameEngineProcess::ChangeLevel(const std::string& _LevelName)
{
	std::string Upper = GameEngineString::ToUpperReturn(_LevelName);
	auto FindIter = AllLevel.find(Upper);

	if (FindIter == AllLevel.end())
	{
		MsgBoxAssert(Upper + " 레벨이 존재하지 않습니다.\n(GameEngineProcess::ChangeLevel)");
	}

	NextLevel = FindIter->second;
}

GameEngineLevel* GameEngineProcess::FindLevel(const std::string& _LevelName)
{
	std::string Upper = GameEngineString::ToUpperReturn(_LevelName);
	auto FindIter = AllLevel.find(Upper);

	if (FindIter == AllLevel.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineProcess::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}

void GameEngineProcess::LevelUpdate(float _Delta)
{
	CurLevel->ActorUpdate(_Delta);
	CurLevel->Update(_Delta);
}

void GameEngineProcess::LevelRender()
{
	CurLevel->ActorRender();
	CurLevel->Render();
}

void GameEngineProcess::LevelRelease()
{
	CurLevel->ActorRelease();
	CurLevel->Release();
}
