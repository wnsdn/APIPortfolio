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
		for (auto& Vec : Pair.second)
		{
			for (auto& Renderer : Vec)
			{
				if (Renderer)
				{
					delete Renderer;
					Renderer = nullptr;
				}
			}
		}
	}
}

void GameEngineCamera::InsertRenderer(const std::vector<GameEngineRenderer*>& _VecRenderer)
{
	AllRenderer[_VecRenderer[0]->GetRenderOrder()].emplace_back(_VecRenderer);
}

void GameEngineCamera::Update(float _Delta)
{
	for (int CurGrpRO = ZOrderBegin; CurGrpRO <= ZOrderEnd; ++CurGrpRO)
	{
		auto Iter = AllRenderer[CurGrpRO].begin();
		auto End = AllRenderer[CurGrpRO].end();
		for (; Iter != End;)
		{
			bool Check = true;
			for (auto Renderer : *Iter)
			{
				if (!Renderer)
				{
					continue;
				}

				int IdxY = Renderer->GetActor()->GetIndex().Y;
				if (IdxY < CurGrpRO)
				{
					AllRenderer[IdxY].emplace_back(*Iter);
					Iter = AllRenderer[CurGrpRO].erase(Iter);
					Check = false;
					break;
				}
				else if (IdxY > CurGrpRO)
				{
					AllRenderer[IdxY].emplace_front(*Iter);
					Iter = AllRenderer[CurGrpRO].erase(Iter);
					Check = false;
					break;
				}
			}

			if (Check)
			{
				++Iter;
			}
		}
	}
}

void GameEngineCamera::Render(float _Delta)
{
	for (auto& Pair : AllRenderer)
	{
		for (auto& Vec : Pair.second)
		{
			for (auto& Renderer : Vec)
			{
				if (!Renderer || Renderer->GetActor()->IsDeath())
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
}

void GameEngineCamera::Release()
{
	for (auto& Pair : AllRenderer)
	{
		auto Iter = Pair.second.begin();
		auto End = Pair.second.end();
		for (; Iter != End;)
		{
			bool IsErase = false;
			auto& Vec = *Iter;
			for (auto Renderer : Vec)
			{
				if (Renderer && Renderer->IsDeath())
				{
					delete Renderer;
					Renderer = nullptr;
					IsErase = true;
				}
			}

			if (IsErase)
			{
				Iter = Pair.second.erase(Iter);
			}
			else
			{
				++Iter;
			}
		}
	}
}

