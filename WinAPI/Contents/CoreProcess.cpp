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

	CreateLevel<MonsterLevel>("MonsterLevel")->Init("Octopus1.txt");
}

void CoreProcess::Update(float _Delta)
{
}
