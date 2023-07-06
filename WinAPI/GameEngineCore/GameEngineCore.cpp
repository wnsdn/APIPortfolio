#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineGraphics.h>
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
		return;
	}

	GameEngineWindow::GetInst().Open(_Hinst, _Title);
	GameEngineWindow::GetInst().MessageLoop(CoreStart, CoreUpdate, CoreEnd);
}

void GameEngineCore::CoreStart()
{
	GameEngineTime::Init();
	GameEngineInput::Init();
	GameEngineSound::Init();
	GameEngineGraphics::Init();

	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (Process->NextLevel)
	{
		Process->CurLevel = Process->NextLevel;
		Process->NextLevel = nullptr;
		if (Process->PrevLevel)
		{
			delete Process->PrevLevel;
			Process->PrevLevel = nullptr;
		}
		GameEngineTime::Reset();
	}

	//Update
	GameEngineSound::Update();
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
	Process->Update(Delta);
	Process->CurLevel->GetCamera()->Update(Delta);

	//Render
	GameEngineWindow::GetInst().ClearBackBuffer();
	Process->CurLevel->GetCamera()->Render(Delta);
	Process->Render(Delta);
	GameEngineWindow::GetInst().DoubleBuffering();

	//Release
	Process->Release();
	Process->CurLevel->GetCamera()->Release();
}

void GameEngineCore::CoreEnd()
{
	GameEngineSound::SoundRelease();
	GameEngineSound::SystemRelease();
	GameEngineGraphics::Release();

	if (Process)
	{
		delete Process;
		Process = nullptr;
	}
}
