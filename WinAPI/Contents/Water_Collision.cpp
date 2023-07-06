#include "Water.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Object.h"
#include "Bomb.h"

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
		if (_CurIndex == Ptr->GetIndex() &&
			dynamic_cast<Bomb*>(Ptr)->GetState() == "")
		{
			DirOn[_Dir] = false;
			Ptr->Death();
		}
	}
}

void Water::CollisionCheck2(const int2 _CurIndex, bool& _Check)
{
	if (_CurIndex.X < 0 || _CurIndex.X > 14 ||
		_CurIndex.Y < 0 || _CurIndex.Y > 12)
	{
		_Check = true;
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Block))
	{
		if (_CurIndex == Ptr->GetIndex())
		{
			_Check = true;
		}
	}
	for (auto Ptr : Level->FindActor(UpdateOrder::Object))
	{
		if (_CurIndex == Ptr->GetIndex())
		{
			_Check = true;

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
		if (_CurIndex == Ptr->GetIndex() &&
			dynamic_cast<Bomb*>(Ptr)->GetState() == "")
		{
			_Check = true;

			Ptr->Death();
		}
	}
}
