#include "UIFrame.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Player.h"

#include <format>

UIFrame::UIFrame()
{
}

UIFrame::~UIFrame()
{
}

void UIFrame::Init(const std::string& _Path)
{
	Main = _Path;
	Pos = GameEngineWindow::GetPos();
	Scale = GameEngineWindow::GetScale();

	CreateRenderer(Main, RenderOrder::BackUI);
	FindRenderer(Main)->SetScale(Scale);

	CreateRenderer("FrameBazzi.bmp", RenderOrder::BackUI);
	FindRenderer("FrameBazzi.bmp")->AddPos({ 295, -191 });
	FindRenderer("FrameBazzi.bmp")->SetScale({ 49, 39 });

	if (Player::MainPlayer)
	{
		int Rank = Player::MainPlayer->GetRank();
		CreateRenderer("PlayerRank.bmp", RenderOrder::BackUI, {}, { 2, 10 });
		FindRenderer("PlayerRank.bmp")->AddPos({ 331, -198 });
		FindRenderer("PlayerRank.bmp")->SetScale({ 19,19 });
		FindRenderer("PlayerRank.bmp")
			->SetCopyPos({ static_cast<float>(Rank / 10), static_cast<float>(Rank % 10) });
	}

	CreateTextRenderer("Player", RenderOrder::BackUI);
	FindRenderer("Player")->SetText("Player", 11.0f, 2.8f, "³ª´®½ºÄù¾î ³×¿À Heavy", ((255 | (255 << 8)) | (255 << 16)));
	FindRenderer("Player")->AddPos({ 319, -186 });

	CreateRenderer("Time0.bmp", RenderOrder::BackUI);
	FindRenderer("Time0.bmp")->AddPos({ 332, -227 });
	FindRenderer("Time0.bmp")->SetScale({ 14, 16 });
	CreateRenderer("TimeNum.bmp", RenderOrder::BackUI, {}, { 2, 5 }, "TimeNum1");
	FindRenderer("TimeNum1")->AddPos({ 345, -227 });
	FindRenderer("TimeNum1")->SetScale({ 14, 16 });

	CreateRenderer("Dot.bmp", RenderOrder::BackUI);
	FindRenderer("Dot.bmp")->AddPos({ 355, -228 });
	FindRenderer("Dot.bmp")->SetScale({ 14, 15 });

	CreateRenderer("TimeNum.bmp", RenderOrder::BackUI, {}, { 2, 5 }, "TimeNum2");
	FindRenderer("TimeNum2")->AddPos({ 365, -227 });
	FindRenderer("TimeNum2")->SetScale({ 14, 16 });
	CreateRenderer("TimeNum.bmp", RenderOrder::BackUI, {}, { 2, 5 }, "TimeNum3");
	FindRenderer("TimeNum3")->AddPos({ 378, -227 });
	FindRenderer("TimeNum3")->SetScale({ 14, 16 });

	ItemSlotInit();
	CurItemInit();

	InsertRenderer();
}

void UIFrame::Update(float _Delta)
{
	CurTime = MaxTime - static_cast<int>(LiveTime);
	if (CurTime < 0)
	{
		CurTime = 0;
	}

	Minute = CurTime / 60;
	SecTen = CurTime % 60 / 10;
	Sec = CurTime % 10;

	FindRenderer("TimeNum1")->
		SetCopyPos({ static_cast<float>(Minute / 5), static_cast<float>(Minute % 5) });
	FindRenderer("TimeNum2")->
		SetCopyPos({ static_cast<float>(SecTen / 5), static_cast<float>(SecTen % 5) });
	FindRenderer("TimeNum3")->
		SetCopyPos({ static_cast<float>(Sec / 5), static_cast<float>(Sec % 5) });
	if (Player::MainPlayer)
	{
		int Rank = Player::MainPlayer->GetRank();
		FindRenderer("PlayerRank.bmp")
			->SetCopyPos({ static_cast<float>(Rank / 10), static_cast<float>(Rank % 10) });
	}
	ItemSlotUpdate(_Delta);
	CurItemUpdate(_Delta);
}
