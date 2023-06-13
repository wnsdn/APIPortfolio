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
		GameEngineRenderer* Renderer = Pair.second;

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
	auto FindIter = AllRenderer.find(Upper);

	if (FindIter != AllRenderer.end())
	{
		return FindIter->second;
	}

	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetCamera(Level->GetCamera());
	NewRenderer->SetActor(this);
	NewRenderer->SetOrder(_RenderOrder);
	NewRenderer->LoadTexture(_Filename, _Pos, _Size);

	Level->GetCamera()->InsertRenderer(NewRenderer);
	AllRenderer.emplace(Upper, NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _Name, int _RenderOrder, const float4& _Size, unsigned int _Color)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Name);
	auto FindIter = AllRenderer.find(Upper);

	if (FindIter != AllRenderer.end())
	{
		return FindIter->second;
	}

	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetCamera(Level->GetCamera());
	NewRenderer->SetActor(this);
	NewRenderer->SetOrder(_RenderOrder);
	NewRenderer->CreateTexture(_Name, _Size, _Color);

	Level->GetCamera()->InsertRenderer(NewRenderer);
	AllRenderer.emplace(Upper, NewRenderer);

	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::FindRenderer(const std::string& _Filename)
{
	std::string Upper = GameEngineString::ToUpperReturn(_Filename);
	auto FindIter = AllRenderer.find(Upper);

	if (FindIter == AllRenderer.end())
	{
		MsgBoxAssert(Upper + " FindRenderer() ½ÇÆÐ");
		return nullptr;
	}

	return FindIter->second;
}
