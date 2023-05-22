#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameEngineProcess.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

GameEngineProcess* GameEngineCore::Process = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::EngineStart(HINSTANCE _Hinst, const std::string& _Title, GameEngineProcess* _Process)
{
	GameEngineDebug::LeakCheck();
	//_CrtSetBreakAlloc(1227);

	Process = _Process;

	if (!Process)
	{
		MsgBoxAssert("Process == nullptr (EngineStart)");
	}

	GameEngineWindow::GetInst().Open(_Hinst, _Title);
	GameEngineWindow::GetInst().MessageLoop(CoreStart, CoreUpdate, CoreEnd);
}

void GameEngineCore::CoreStart()
{
	GameEngineTime::Init();
	GameEngineInput::Init();
	GameEngineRandom::Init();

	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (Process->NextLevel)
	{
		Process->CurLevel = Process->NextLevel;
		Process->NextLevel = nullptr;
		GameEngineTime::Reset();
	}

	GameEngineTime::Update();
	float Delta = GameEngineTime::GetFloatDelta();
	if (GameEngineWindow::GetInst().IsFocus())
	{
		GameEngineInput::Update(Delta);

	}
	else
	{
		GameEngineInput::Reset();
	}

	Process->LevelUpdate(Delta);
	Process->Update(Delta);

	GameEngineWindow::GetInst().ClearBackBuffer();
	Process->CurLevel->GetMainCamera()->Render(Delta);
	Process->LevelRender();
	Process->Render();
	GameEngineWindow::GetInst().DoubleBuffering();

	Process->CurLevel->GetMainCamera()->Release();
	Process->LevelRelease();
	Process->Release();
}

void GameEngineCore::CoreEnd()
{
	if (Process)
	{
		delete Process;
		Process = nullptr;
	}
}
