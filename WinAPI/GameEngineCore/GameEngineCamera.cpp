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
		for (auto& Tmp : Pair.second)
		{
			GameEngineRenderer* Renderer = Tmp.second;
			if (Renderer)
			{
				delete Renderer;
				Renderer = nullptr;
			}
		}
	}
}

void GameEngineCamera::InsertRenderer(GameEngineRenderer* _Renderer, int _ZOrder)
{
	AllRenderer[_ZOrder].emplace(_Renderer->GetOrder(), _Renderer);
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
			if (Renderer->GetOrder() == Renderer->GetActor()->GetIndex().Y)//�ε����� ������ ������
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
			else//�ε����� ������ �ٸ���
			{
				Renderer->SetPreOrder(Renderer->GetOrder());
				Renderer->SetOrder(Renderer->GetActor()->GetIndex().Y);

				if (Renderer->GetOrder() - Renderer->GetPreOrder() < 0)//�Ʒ��� ���� �̵�
				{
					AllRenderer[Renderer->GetOrder()].emplace_back(Renderer);
				}
				else//������ �Ʒ��� �̵�
				{
					AllRenderer[Renderer->GetOrder()].emplace_front(Renderer);
				}

				Iter = AllRenderer[i].erase(Iter);
			}
		}
	}
}

void GameEngineCamera::Render(float _Delta)
{
	for (auto& Pair : AllRenderer)
	{
		for (auto& Tmp : Pair.second)
		{
			GameEngineRenderer* Renderer = Tmp.second;
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
		auto& Map = Pair.second;
		std::erase_if(Map,
			[](const std::pair<int, GameEngineRenderer*> _Pair)
			{
				GameEngineRenderer* Renderer = _Pair.second;
				if (Renderer->IsDeath())
				{
					delete Renderer;
					Renderer = nullptr;
				}

				return _Pair.second == nullptr;
			})
	}
}

