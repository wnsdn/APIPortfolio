#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineCollision.h"

GameEngineLevel::GameEngineLevel()
	: MainCamera(new GameEngineCamera)
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

	if (MainCamera)
	{
		delete MainCamera;
		MainCamera = nullptr;
	}
}

void GameEngineLevel::Start()
{
}

void GameEngineLevel::Update(float _Delta)
{
	for (auto& Pair : AllActor)
	{
		for (auto& Actor : Pair.second)
		{
			if (Actor->IsDeath())
			{
				continue;
			}

			Actor->AddLiveTime(_Delta);
			Actor->Update(_Delta);
		}
	}
}

void GameEngineLevel::Render()
{
	if (!IsDebugRender)
	{
		return;
	}

	for (auto& Pair : AllActor)
	{
		for (auto& Actor : Pair.second)
		{
			if (Actor->IsDeath())
			{
				continue;
			}

			Actor->Render();
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
