#include "Water.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Object.h"

void Water::CollisionCheck(const int2 _CurIndex, int _Dir)
{
	for (auto Ptr : Level->FindActor(UpdateOrder::Block))
	{
		if (_CurIndex == Ptr->GetIndex())
		{
			DirOn[_Dir] = false;
		}
	}
	for (auto Ptr : Level->FindActor(UpdateOrder::Object))
	{
		if (_CurIndex == Ptr->GetIndex())
		{
			DirOn[_Dir] = false;
			dynamic_cast<Object*>(Ptr)->SetBeforeDeath(true);
		}
	}
	for (auto Ptr : Level->FindActor(UpdateOrder::Item))
	{
		if (_CurIndex == Ptr->GetIndex())
		{
			Ptr->Death();
		}
	}
	for (auto Ptr : Level->FindActor(UpdateOrder::Bomb))
	{
		if (_CurIndex == Ptr->GetIndex())
		{
			DirOn[_Dir] = false;
			Ptr->Death();
		}
	}
}
