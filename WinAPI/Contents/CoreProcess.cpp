#include "CoreProcess.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Global.h"
#include "TitleLevel.h"

CoreProcess::CoreProcess()
{
	std::string FontPath = "";
	FontPath = GameEnginePath::FilenameToPath("NanumH.ttf");
	AddFontResourceA(FontPath.c_str());
	FontPath = GameEnginePath::FilenameToPath("digital-7.ttf");
	AddFontResourceA(FontPath.c_str());
}

CoreProcess::~CoreProcess()
{
	std::string FontPath = "";
	FontPath = GameEnginePath::FilenameToPath("NanumH.ttf");
	RemoveFontResourceA(FontPath.c_str());
	FontPath = GameEnginePath::FilenameToPath("digital-7.ttf");
	RemoveFontResourceA(FontPath.c_str());
}

void CoreProcess::Start()
{
	GameEngineProcess::Start();

	GameEngineWindow::GetInst().SetPosAndScale({ 100, 100 }, { 840, 630 });

	CreateLevel<TitleLevel>();

	//Sound
	GameEngineSound::CreateSound("ButtonOn.wav", false);
	GameEngineSound::CreateSound("ButtonClick.wav", false);
}
