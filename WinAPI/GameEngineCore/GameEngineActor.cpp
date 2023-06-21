#include "GameEngineActor.h"
#include <vector>
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
	for (auto& Renderer : AllRenderer)
	{
		if (Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _Filename, int _RenderOrder, const float4& _Pos, const float4& _Size)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Filename);
	for (auto& Renderer : AllRenderer)
	{
		if (Renderer->GetName() == Upper)
		{
			return Renderer;
		}
	}

	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetName(Upper);
	NewRenderer->SetCamera(Level->GetCamera());
	NewRenderer->SetActor(this);
	NewRenderer->SetRenderOrder(_RenderOrder);
	NewRenderer->LoadTexture(_Filename, _Pos, _Size);

	AllRenderer.emplace_back(NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _Name, int _RenderOrder, const float4& _Size, unsigned int _Color)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Name);
	for (auto& Renderer : AllRenderer)
	{
		if (Renderer->GetName() == Upper)
		{
			return Renderer;
		}
	}

	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetName(Upper);
	NewRenderer->SetCamera(Level->GetCamera());
	NewRenderer->SetActor(this);
	NewRenderer->SetRenderOrder(_RenderOrder);
	NewRenderer->CreateTexture(_Name, _Size, _Color);

	AllRenderer.emplace_back(NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateTextRenderer(const std::string& _Text, int _RenderOrder)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Text);
	for (auto& Renderer : AllRenderer)
	{
		if (Renderer->GetName() == Upper)
		{
			return Renderer;
		}
	}

	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetName(Upper);
	NewRenderer->SetCamera(Level->GetCamera());
	NewRenderer->SetActor(this);
	NewRenderer->SetRenderOrder(_RenderOrder);
	NewRenderer->SetText(_Text);

	AllRenderer.emplace_back(NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::FindRenderer(const std::string& _Filename)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Filename);
	for (auto& Renderer : AllRenderer)
	{
		if (Renderer->GetName() == Upper)
		{
			return Renderer;
		}
	}

	MsgBoxAssert(_Filename + " FindRenderer()");
	return nullptr;
}

void GameEngineActor::InsertRenderer()
{
	Level->GetCamera()->InsertRenderer(AllRenderer);
}

void GameEngineActor::DrawRect(const float4& _Pos, const float4& _Scale,
	unsigned int _Color)
{
	HDC BackDC = GameEngineWindow::GetInst().GetBackBuffer()->GetImageDC();

	HPEN Hpen = CreatePen(PS_SOLID, 3, _Color);
	HPEN OldPen = static_cast<HPEN>(SelectObject(BackDC, Hpen));
	HBRUSH Hbrush = static_cast<HBRUSH>(GetStockObject(HOLLOW_BRUSH));
	HBRUSH OldBrush = static_cast<HBRUSH>(SelectObject(BackDC, Hbrush));

	Rectangle(BackDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Pos.iX() + _Scale.ihX(),
		_Pos.iY() + _Scale.ihY());

	SelectObject(BackDC, OldPen);
	SelectObject(BackDC, OldBrush);
	DeleteObject(Hpen);
	DeleteObject(Hbrush);
}

void GameEngineActor::DrawLine(const float4& _StartPos, const float4& _EndPos)
{
	HDC BackDC = GameEngineWindow::GetInst().GetBackBuffer()->GetImageDC();

	MoveToEx(BackDC, _StartPos.iX(), _StartPos.iY(), nullptr);
	LineTo(BackDC, _EndPos.iX(), _EndPos.iY());
}
