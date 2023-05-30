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
		GameEngineLevel* Level = Pair.second;

		if (Level)
		{
			delete Level;
			Level = nullptr;
		}
	}
}

void GameEngineProcess::Start()
{
}

void GameEngineProcess::Update(float _Delta)
{
	CurLevel->Update(_Delta);
}

void GameEngineProcess::Render()
{
	CurLevel->Render();
}

void GameEngineProcess::Release()
{
	CurLevel->Release();
}

void GameEngineProcess::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}

GameEngineLevel* GameEngineProcess::FindLevel(const std::string& _Level)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Level);
	auto FindIter = AllLevel.find(Upper);

	if (FindIter == AllLevel.end())
	{
		return nullptr;
	}

	return FindIter->second;
}
