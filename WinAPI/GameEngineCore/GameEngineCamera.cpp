#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{
	for (auto& Pair : AllRenderer)
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

void GameEngineCamera::InsertRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer[_Renderer->GetOrder()].emplace_back(_Renderer);
}

void GameEngineCamera::Update(float _Delta)
{
	for (int i = ZOrderBegin; i <= ZOrderEnd; ++i)
	{
		auto Iter = AllRenderer[i].begin();
		auto End = AllRenderer[i].end();
		for (; Iter != End;)
		{
			GameEngineRenderer* Renderer = *Iter;
			if (Renderer->GetOrder() == Renderer->GetActor()->GetIndex().Y)
			{
				if (Renderer->GetOrderChange())
				{
					Iter = AllRenderer[i].erase(Iter);
					AllRenderer[Renderer->GetOrder()].emplace_back(Renderer);

					Renderer->SetOrderChange(false);
				}
				else
				{
					++Iter;
				}
			}
			else
			{
				Renderer->SetOrder(Renderer->GetActor()->GetIndex().Y);
				AllRenderer[Renderer->GetOrder()].emplace_back(Renderer);

				Iter = AllRenderer[i].erase(Iter);
			}
		}
	}
}

void GameEngineCamera::Render(float _Delta)
{
	for (auto& Pair : AllRenderer)
	{
		for (auto& Renderer : Pair.second)
		{
			if (Renderer->GetActor()->IsDeath())
			{
				continue;
			}

			Renderer->AddLiveTime(_Delta);

			if (!Renderer->IsUpdate())
			{
				continue;
			}

			Renderer->Render(_Delta);
		}
	}
}

void GameEngineCamera::Release()
{
	for (auto& Pair : AllRenderer)
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

