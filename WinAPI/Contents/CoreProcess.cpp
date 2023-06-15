#include "CoreProcess.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Global.h"
#include "TitleLevel.h"

CoreProcess::CoreProcess()
{
}

CoreProcess::~CoreProcess()
{
}

void CoreProcess::Start()
{
	GameEngineProcess::Start();

	GameEngineWindow::GetInst().SetPosAndScale({ 100, 100 }, { 840, 630 });
	ShowCursor(false);

	CreateLevel<TitleLevel>();

	//Sound
	GameEngineSound::CreateSound("ButtonOn.wav", false);
	GameEngineSound::CreateSound("ButtonClick.wav", false);
}
