#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

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

void GameEngineLevel::ActorInit(GameEngineActor* _Actor)
{
	_Actor->Level = this;
	_Actor->Start();
}

void GameEngineLevel::ActorUpdate(float _Delta)
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
}

void GameEngineLevel::ActorRender()
{
	if (!IsActorRender)
	{
		return;
	}

	for (auto& Pair : AllActor)
	{
		for (auto& Actor : Pair.second)
		{
			if (!Actor->IsUpdate())
			{
				continue;
			}

			Actor->Render();
		}
	}
}

void GameEngineLevel::ActorRelease()
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