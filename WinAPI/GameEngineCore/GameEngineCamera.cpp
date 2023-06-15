#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{
	for (auto& Pair1 : AllRenderer)
	{
		for (auto& Pair2 : Pair1.second)
		{
			for (auto& Renderer : Pair2.second)
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

void GameEngineCamera::InsertRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer[_Renderer->GetZOrder()][_Renderer->GetOrder()].emplace_back(_Renderer);
}

void GameEngineCamera::Update(float _Delta)
{
	for (int CurGroupZOrder = ZOrderBegin; CurGroupZOrder <= ZOrderEnd; ++CurGroupZOrder)
	{
		for (auto& Pair : AllRenderer[CurGroupZOrder])
		{
			auto Iter = Pair.second.begin();
			auto End = Pair.second.end();
			for (; Iter != End;)
			{
				GameEngineRenderer* Renderer = *Iter;
				int ZOrder = Renderer->GetActor()->GetIndex().Y;
				if (CurGroupZOrder != ZOrder)//랑 Z오더가 다르면
				{
					if (CurGroupZOrder - ZOrder > 0)
					{
						AllRenderer[ZOrder][Renderer->GetOrder()].emplace_back(Renderer);
					}
					else
					{
						AllRenderer[ZOrder][Renderer->GetOrder()].emplace_front(Renderer);
					}
					Iter = AllRenderer[CurGroupZOrder][Renderer->GetOrder()].erase(Iter);
				}
				else
				{
					++Iter;
				}
			}
		}
	}
}

void GameEngineCamera::Render(float _Delta)
{
	for (auto& Pair1 : AllRenderer)
	{
		for (auto& Pair2 : Pair1.second)
		{
			for (auto& Renderer : Pair2.second)
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
}

void GameEngineCamera::Release()
{
	/*for (auto& Pair1 : AllRenderer)
	{
		for (auto& Pair2 : Pair1.second)
		{
			auto& List = Pair2.second;
			std::erase_if(List,
				[]()
				{

				});
		}
	}*/
}

