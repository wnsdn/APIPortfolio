#include "GameEngineProcess.h"
#include <algorithm>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineLevel.h"

GameEngineProcess::GameEngineProcess()
{
}

GameEngineProcess::~GameEngineProcess()
{
	if (CurLevel)
	{
		delete CurLevel;
		CurLevel = nullptr;
	}
}

void GameEngineProcess::LevelInit(GameEngineLevel* _Level)
{
	_Level->Process = this;
	_Level->Start();
}

void GameEngineProcess::Update(float _Delta)
{
	CurLevel->Update(_Delta);
}

void GameEngineProcess::Render(float _Delta)
{
	CurLevel->Render(_Delta);
}

void GameEngineProcess::Release()
{
	CurLevel->Release();
}
