#include "CoreProcess.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapEditorLevel.h"

CoreProcess::CoreProcess()
{
}

CoreProcess::~CoreProcess()
{
}

void CoreProcess::Start()
{
	GameEngineProcess::Start();

	GameEngineWindow::GetInst().SetPosAndScale({ 100, 100 },
		{ 42 * 15 + 1 + 510, 42 * 13 + 1 + 200});

	CreateLevel<MapEditorLevel>();
}
