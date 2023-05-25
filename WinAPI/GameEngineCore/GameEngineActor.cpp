#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineCamera.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
	for (auto& Pair : AllRenderer)
	{
		if (Pair.second)
		{
			Pair.second->Death();
			Pair.second = nullptr;
		}
	}
}

GameEngineRenderer* GameEngineActor::CreateBackUIRenderer(const std::string& _Path, const std::string& _Name, int _Order, bool _Ordered, const float4 _Pos, const float4 _Size)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Name);
	auto FindIter = AllRenderer.find(Upper);

	if (FindIter != AllRenderer.end())
	{
		return FindIter->second;
	}

	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetCamera(Level->GetBackUICamera());
	NewRenderer->SetMaster(this);
	NewRenderer->SetOrder(_Order);
	NewRenderer->Init(_Path, _Pos, _Size);

	Level->GetBackUICamera()->InsertRenderer(NewRenderer, _Ordered);
	AllRenderer.emplace(Upper, NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _Path, const std::string& _Name, int _Order, bool _Ordered, const float4 _Pos, const float4 _Size)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Name);
	auto FindIter = AllRenderer.find(Upper);

	if (FindIter != AllRenderer.end())
	{
		return FindIter->second;
	}

	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetCamera(Level->GetMainCamera());
	NewRenderer->SetMaster(this);
	NewRenderer->SetOrder(_Order);
	NewRenderer->Init(_Path, _Pos, _Size);

	Level->GetMainCamera()->InsertRenderer(NewRenderer, _Ordered);
	AllRenderer.emplace(Upper, NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateFrontUIRenderer(const std::string& _Path, const std::string& _Name, int _Order, bool _Ordered, const float4 _Pos, const float4 _Size)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Name);
	auto FindIter = AllRenderer.find(Upper);

	if (FindIter != AllRenderer.end())
	{
		return FindIter->second;
	}

	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetCamera(Level->GetFrontUICamera());
	NewRenderer->SetMaster(this);
	NewRenderer->SetOrder(_Order);
	NewRenderer->Init(_Path, _Pos, _Size);

	Level->GetFrontUICamera()->InsertRenderer(NewRenderer, _Ordered);
	AllRenderer.emplace(Upper, NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::FindRenderer(const std::string& _Name)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Name);
	auto FindIter = AllRenderer.find(Upper);

	if (FindIter == AllRenderer.end())
	{
		MsgBoxAssert(Upper + " FindRenderer() ½ÇÆÐ");
	}

	return FindIter->second;
}

void GameEngineActor::DrawRect(const float4& _Pos, const float4& _Scale)
{
	HDC BackBuffer = GameEngineWindow::GetInst().GetBackBuffer()->GetImageDC();
	HBRUSH MyBrush = static_cast<HBRUSH>(GetStockObject(HOLLOW_BRUSH));
	HBRUSH OldBrush = static_cast<HBRUSH>(SelectObject(BackBuffer, MyBrush));
	HPEN MyPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN OldPen = static_cast<HPEN>(SelectObject(BackBuffer, MyPen));

	Rectangle(BackBuffer,
		_Pos.iX() - _Scale.Half().iX(),
		_Pos.iY() - _Scale.Half().iY(),
		_Pos.iX() + _Scale.Half().iX(),
		_Pos.iY() + _Scale.Half().iY());

	SelectObject(BackBuffer, OldBrush);
	SelectObject(BackBuffer, OldPen);
	DeleteObject(MyBrush);
	DeleteObject(MyPen);
}

void GameEngineActor::DrawStr(const float4& _Pos, const char* _Str)
{
	HDC BackBuffer = GameEngineWindow::GetInst().GetBackBuffer()->GetImageDC();
	TextOutA(BackBuffer, _Pos.iX() - 15, _Pos.iY() - 15, _Str, static_cast<int>(strlen(_Str)));
}
