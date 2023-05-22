#include "CoreProcess.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Global.h"
#include "TitleLevel.h"
#include "MonsterLevel.h"

CoreProcess::CoreProcess()
{
}

CoreProcess::~CoreProcess()
{
}

void CoreProcess::Start()
{
	GameEngineWindow::GetInst().SetPosAndScale({ 100, 100 }, { 840, 630 });

	CreateLevel<TitleLevel>("Titlelevel");
	CreateLevel<MonsterLevel>("MonsterLevel");

	//ChangeLevel("titlelevel");
	ChangeLevel("MonsterLevel");
}

void CoreProcess::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_ESCAPE))
	{
		if (CurLevel == FindLevel("titlelevel"))
		{
			ChangeLevel("MonsterLevel");
		}
	}
}
