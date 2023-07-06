#include "GameResult.h"
#include <format>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "UI.h"
#include "GameResultText.h"
#include "Player.h"

GameResult::GameResult()
{
}

GameResult::~GameResult()
{
}

void GameResult::Init(bool _Win)
{
	if (!Player::MainPlayer)
	{
		return;
	}

	Rank = Player::MainPlayer->GetRank();
	Kill = Player::MainPlayer->GetKill();
	PreExp = Player::MainPlayer->GetPreExp();
	CurExp = Player::MainPlayer->GetCurExp();
	MaxExp = Player::MainPlayer->GetMaxExp();
	ExpDelta = Player::MainPlayer->GetExpDelta();
	ExpStart = static_cast<float>(PreExp) / static_cast<float>(MaxExp) * 100;
	ExpEnd = static_cast<float>(CurExp) / static_cast<float>(MaxExp) * 100;

	Pos = GameEngineWindow::GetPos();

	CreateRenderer("GameResult.bmp", RenderOrder::UI_GameResult);
	FindRenderer("GameResult.bmp")->SetAlphaRender(true);
	FindRenderer("GameResult.bmp")->SetAlphaValue(200);
	FindRenderer("GameResult.bmp")->AddPos({ -84, -22 });

	CreateRenderer("PIBar.bmp", RenderOrder::UI_GameResult);
	FindRenderer("PIBar.bmp")->AddPos({ -85, -145 });

	CreateRenderer("PINumber.bmp", RenderOrder::UI_GameResult);
	FindRenderer("PINumber.bmp")->AddPos({ -326, -145 });

	CreateRenderer("PINumBar.bmp", RenderOrder::UI_GameResult, {}, { 1, 2 });
	FindRenderer("PINumBar.bmp")->AddPos({ 55, -145 });

	CreateRenderer("PIGaugeMask.bmp", RenderOrder::UI_GameResult);
	FindRenderer("PIGaugeMask.bmp")->AddPos({ 55, -145 });
	FindRenderer("PIGaugeMask.bmp")->SetIsGauge(true);
	GaugeMax = FindRenderer("PIGaugeMask.bmp")->GetScale().X;
	FindRenderer("PIGaugeMask.bmp")->
		SetAdjPos({ GaugeMax / 100 * (100 - ExpStart), 0 });


	CreateRenderer("PI_ID.bmp", RenderOrder::UI_GameResult);
	FindRenderer("PI_ID.bmp")->AddPos({ -174, -175 });

	CreateRenderer("PI_Kill.bmp", RenderOrder::UI_GameResult);
	FindRenderer("PI_Kill.bmp")->AddPos({ -60, -175 });

	CreateRenderer("PI_Exp.bmp", RenderOrder::UI_GameResult);
	FindRenderer("PI_Exp.bmp")->AddPos({ 55, -175 });

	CreateRenderer("ResultPlayer.bmp", RenderOrder::UI_GameResult);
	FindRenderer("ResultPlayer.bmp")->AddPos({ -250, 103 });

	CreateRenderer("PIResult.bmp", RenderOrder::UI_GameResult, {}, { 2, 1 });
	FindRenderer("PIResult.bmp")->AddPos({ -278, -144 });

	CreateTextRenderer("PlayerName", RenderOrder::UI_GameResult);
	FindRenderer("PlayerName")->SetText("Player", 12.0f, 3.0f, "³ª´®½ºÄù¾î ³×¿À Heavy");
	FindRenderer("PlayerName")->AddPos({ -199, -152 });

	CreateRenderer("PlayerRank.bmp", RenderOrder::UI_GameResult, {}, { 2, 10 });
	FindRenderer("PlayerRank.bmp")->AddPos({ -214, -143 });
	FindRenderer("PlayerRank.bmp")->SetScale({ 20, 20 });
	FindRenderer("PlayerRank.bmp")
		->SetCopyPos({ static_cast<float>(Rank / 10), static_cast<float>(Rank % 10) });

	std::string Buffer{};
	CreateTextRenderer("PlayerKill", RenderOrder::UI_GameResult);
	std::format_to(std::back_inserter(Buffer), "{:0>2}", Kill);
	FindRenderer("PlayerKill")->SetText(Buffer, 16.0f, 3.2f, "Digital-7");
	FindRenderer("PlayerKill")->AddPos({ -73, -153 });

	Buffer.clear();
	CreateTextRenderer("PlayerExp", RenderOrder::UI_GameResult);
	std::format_to(std::back_inserter(Buffer), "+{:>8}", ExpDelta);
	FindRenderer("PlayerExp")->SetText(Buffer, 16.0f, 3.2f, "Digital-7");
	FindRenderer("PlayerExp")->AddPos({ 25, -153 });

	Buffer.clear();
	CreateTextRenderer("PlayerExpDelta", RenderOrder::UI_GameResult);
	std::format_to(std::back_inserter(Buffer), "{:.1f}%", ExpStart);
	FindRenderer("PlayerExpDelta")->SetText(Buffer, 16.0f, 3.2f, "Digital-7");
	FindRenderer("PlayerExpDelta")->AddPos({ 43, -153 });

	GameResultText* Ptr = Level->CreateActor<GameResultText>(UpdateOrder::UI);
	Ptr->Init(_Win);
	if (_Win)
	{
		FindRenderer("PIResult.bmp")->SetCopyPos({ 0, 0 });
		Ptr->AddPos({ 40, 0 });
		if (!Once)
		{
			GameEngineSound::FindSound("GameWin.wav")->Play();
			Once = true;
		}
	}
	else
	{
		FindRenderer("PIResult.bmp")->SetCopyPos({ 1, 0 });
		if (!Once)
		{
			GameEngineSound::FindSound("GameLose.mp3")->Play();
			Once = true;
		}
	}

	InsertRenderer();
}

void GameResult::Update(float _Delta)
{
	if (LiveTime <= 1.3f)
	{
		FindRenderer("PINumBar.bmp")->SetCopyPos({ 0, 0 });
		FindRenderer("PlayerExp")->On();
		FindRenderer("PlayerExpDelta")->Off();
		FindRenderer("PIGaugeMask.bmp")->Off();
	}
	else if (LiveTime <= 2.6f)
	{
		FindRenderer("PINumBar.bmp")->SetCopyPos({ 0, 1 });
		FindRenderer("PlayerExp")->Off();
		FindRenderer("PlayerExpDelta")->On();
		FindRenderer("PIGaugeMask.bmp")->On();
	}
	else
	{
		LiveTime = 0.0f;
	}

	if (Player::MainPlayer)
	{
		Rank = Player::MainPlayer->GetRank();
		FindRenderer("PlayerRank.bmp")
			->SetCopyPos({ static_cast<float>(Rank / 10), static_cast<float>(Rank % 10) });
	}

	if (!JobDone)
	{
		ExpStart += 2.8f * _Delta;
	}

	if (ExpStart >= ExpEnd)
	{
		ExpStart = ExpEnd;
		JobDone = true;
	}

	FindRenderer("PIGaugeMask.bmp")->
		SetAdjPos({ GaugeMax / 100 * (100 - ExpStart), 0 });

	std::string Buffer{};
	std::format_to(std::back_inserter(Buffer), "{:.1f}%", ExpStart);
	FindRenderer("PlayerExpDelta")->SetText(Buffer, 16.0f, 3.2f, "Digital-7");
}
