#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineCollision.h"
#include "ResourceManager.h"

GameEngineLevel::GameEngineLevel()
	: Camera(new GameEngineCamera)
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (auto& Pair : AllActor)
	{
		for (auto& Actor : Pair.second)
		{
			if (Actor)
			{
				delete Actor;
				Actor = nullptr;
			}
		}
	}

	if (Camera)
	{
		delete Camera;
		Camera = nullptr;
	}
}

void GameEngineLevel::SetCameraZOrder(int _ZOrderBegin, int _ZOrderEnd)
{
	Camera->Init(_ZOrderBegin, _ZOrderEnd);
}

void GameEngineLevel::Update(float _Delta)
{
	for (auto& Pair : AllActor)
	{
		for (auto& Actor : Pair.second)
		{
			if (!Actor->IsUpdate())
			{
				continue;
			}

			Actor->AddLiveTime(_Delta);
			Actor->Update(_Delta);
		}
	}

	if (GameEngineInput::IsDown('Q'))
	{
		if (IsRender)
		{
			IsRender = false;
		}
		else
		{
			IsRender = true;
		}
	}
}

void GameEngineLevel::Render(float _Delta)
{
	for (auto& Pair : AllActor)
	{
		for (auto& Actor : Pair.second)
		{
			if (Actor->IsDeath() || !IsRender)
			{
				continue;
			}

			Actor->Render(_Delta);
		}
	}
}

void GameEngineLevel::Release()
{
	for (auto& Pair : AllActor)
	{
		auto Iter = Pair.second.begin();
		auto End = Pair.second.end();
		for (; Iter != End;)
		{
			GameEngineActor* Actor = *Iter;
			if (Actor->IsDeath())
			{
				Actor->Release();
				delete Actor;
				Actor = nullptr;

				Iter = Pair.second.erase(Iter);
			}
			else
			{
				++Iter;
			}
		}
	}
}

void GameEngineLevel::ActorInit(GameEngineActor* _Actor)
{
	_Actor->Level = this;
	_Actor->Start();
}
