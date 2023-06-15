#include "Object.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Global.h"
#include "Tile.h"
#include "Item.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Init(const int2& _Index, const float4& _Type)
{
	Index = _Index;
	Pos = IndexToPos(Index);
	Scale = TileSize;

	if (GameEngineRandom::RandomInt(100) > 60)
	{
		HasItem = true;
		Type.X = static_cast<float>(GameEngineRandom::RandomInt(5, 0));
		Type.Y = static_cast<float>(GameEngineRandom::RandomInt(4, 0));
	}

	CreateRenderer("Object.bmp", ZOrder::InGameObject, RenderOrder::Object, _Type, { 10, 9 });
	FindRenderer("Object.bmp")->AddScale({ 2, 2 });
	FindRenderer("Object.bmp")->SetPos({ 0, -20 });

	CreateRenderer("ObjectBoom.bmp", ZOrder::InGameObject, RenderOrder::Object, {}, { 6, 1 });
	FindRenderer("ObjectBoom.bmp")->CreateAnimation("Death", 0, 0, 6, 0.05f, true);
	FindRenderer("ObjectBoom.bmp")->ChangeAnimation("Death");
	FindRenderer("ObjectBoom.bmp")->SetPos({ -1, -3 });
	FindRenderer("ObjectBoom.bmp")->Off();

	if (_Type.X == 9 && _Type.Y == 4)
	{
		CanMove = true;
	}
	if (_Type.X == 0 && _Type.Y == 3)
	{
		CanMove = true;
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (Ptr && Index == Ptr->GetIndex())
		{
			dynamic_cast<Tile*>(Ptr)->Full();
		}
	}
}

void Object::Update(float _Delta)
{
	CollisionCheck(_Delta);

	if (BeforeDeath)
	{
		if (!TimeReset)
		{
			LiveTime = 0.0f;
			TimeReset = true;
		}

		FindRenderer("Object.bmp")->Off();
		FindRenderer("ObjectBoom.bmp")->On();

		if (GetLiveTime() >= 0.3f)
		{
			Death();
		}
	}
}

void Object::Release()
{
	if (HasItem)
	{
		GameEngineSound::FindSound("ButtonOn.wav")->Play();
		Level->CreateActor<Item>(UpdateOrder::Item)->Init(Index, Type);
	}

	for (auto Ptr : Level->FindActor(UpdateOrder::Tile))
	{
		if (Ptr && Index == Ptr->GetIndex())
		{
			dynamic_cast<Tile*>(Ptr)->Empty();
		}
	}
}
