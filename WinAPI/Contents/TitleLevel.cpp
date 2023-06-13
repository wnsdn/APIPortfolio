#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "Global.h"
#include "BackGround.h"

#include "UI.h"
#include "Button.h"
#include "Cursor.h"
#include "Curtain.h"

#include "MonsterLevel.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	float4 WindowPos = GameEngineWindow::GetPos();

	//Background
	CreateActor<BackGround>(UpdateOrder::None)->Init("Title.bmp");

	//UI
	UI* UIPtr = CreateActor<UI>(UpdateOrder::UI);
	UIPtr->Init("Menu.bmp", WindowPos, RenderOrder::FrontUI);
	UIPtr->AddPos({ 0, 227 });
	StartButton = CreateActor<Button>(UpdateOrder::UI);//Button
	StartButton->Init("TitleStart.bmp", WindowPos, true);
	StartButton->AddPos({ 0, 203 });
	ExitButton = CreateActor<Button>(UpdateOrder::UI);//Button
	ExitButton->Init("TitleExit.bmp", WindowPos, true, 0.26f);
	ExitButton->AddPos({ 0, 251 });
	CreateActor<Cursor>(UpdateOrder::UI);//Cursor
	CurtainPtr = CreateActor<Curtain>(UpdateOrder::UI);//Curtain

	//Sound
	GameEngineSound::CreateSound("Title.wav", true);
	GameEngineSound::FindSound("Title.wav")->Play();
}

void TitleLevel::Update(float _Delta)
{
	GameEngineLevel::Update(_Delta);

	if (LiveTime <= 0.5f)
	{
		CurtainPtr->SetBright(_Delta, 0.5f);
	}

	StartButtonUpdate(_Delta);
	ExitButtonUpdate(_Delta);
}
