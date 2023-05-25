#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{
	for (auto& Pair : Ordered_Renderer)
	{
		for (auto& Renderer : Pair.second)
		{
			if (Renderer)
			{
				delete Renderer;
				Renderer = nullptr;
			}
		}
	}
	for (auto& Pair : Unordered_Renderer)
	{
		for (auto& Renderer : Pair.second)
		{
			if (Renderer)
			{
				delete Renderer;
				Renderer = nullptr;
			}
		}
	}
}

void GameEngineCamera::InsertRenderer(GameEngineRenderer* _Renderer, bool _Ordered)
{
	if (_Ordered)
	{
		Ordered_Renderer[_Renderer->GetOrder()].emplace_back(_Renderer);
	}
	else
	{
		Unordered_Renderer[_Renderer->GetOrder()].emplace_back(_Renderer);
	}
}

void GameEngineCamera::Render(float _Delta)
{
	for (auto& Pair : Unordered_Renderer)
	{
		for (auto& Renderer : Pair.second)
		{
			if (!Renderer->IsUpdate())
			{
				continue;
			}

			Renderer->Render(this, _Delta);
		}
	}
	for (int Y = 0; Y < 13; ++Y)
	{
		for (auto& Pair : Ordered_Renderer)
		{
			for (auto& Renderer : Pair.second)
			{
				if (!Renderer->IsUpdate())
				{
					continue;
				}

				if (Renderer->GetMaster()->GetIndex().Y == Y)
				{
					Renderer->Render(this, _Delta);
				}
			}
		}
	}
}

void GameEngineCamera::Release()
{
	for (auto& Pair : Ordered_Renderer)
	{
		auto Iter = Pair.second.begin();
		auto End = Pair.second.end();
		for (; Iter != End;)
		{
			GameEngineRenderer* Renderer = *Iter;
			if (Renderer->IsDeath())
			{
				delete Renderer;
				Renderer = nullptr;

				Iter = Pair.second.erase(Iter);
			}
			else
			{
				++Iter;
			}
		}
	}
	for (auto& Pair : Unordered_Renderer)
	{
		auto Iter = Pair.second.begin();
		auto End = Pair.second.end();
		for (; Iter != End;)
		{
			GameEngineRenderer* Renderer = *Iter;
			if (Renderer->IsDeath())
			{
				delete Renderer;
				Renderer = nullptr;

				Iter = Pair.second.erase(Iter);
			}
			else
			{
				++Iter;
			}
		}
	}
}
