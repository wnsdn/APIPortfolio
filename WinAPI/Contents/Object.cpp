#include "Object.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Global.h"
#include "Tile.h"
#include "Player.h"

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

	CreateRenderer("Object\\Object", "Main", RenderOrder::Object, true, _Type, { 10, 9 });
	FindRenderer("Main")->AddRenderScale({ 2, 2 });
	FindRenderer("Main")->SetRenderPos({ 0, -20 });

	CreateRenderer("Object\\ObjectBoom", "Death", RenderOrder::Object, true, {}, { 6, 1 });
	FindRenderer("Death")->CreateAnimation("Death", 0, 0, 6, 0.05f, true);
	FindRenderer("Death")->SetRenderPos({ -1, -3 });
	FindRenderer("Death")->Off();

	if (_Type.X == 9 && _Type.Y == 4)
	{
		IsMove = true;
	}

	Tile::GetTile(Index)->Full();
}

void Object::Update(float _Delta)
{
	if (!IsUpdate())
	{
		if (GetLiveTime() >= 0.3f)
		{
			Death();
		}

		return;
	}

	if (IsMove && Tile::GetTile(Index + int2::Up)->GetIsEmpty())
	{
		for (auto Ptr : Level->FindActor(UpdateOrder::Player))
		{
			Player* Temp = dynamic_cast<Player*>(Ptr);

			if (GameEngineInput::IsPress(VK_UP) && Temp->GetDir() == "Up")
			{
				if (Index.X == Temp->GetIndex().X &&
					Index.Y == Temp->GetIndex().Y - 1)
				{
					Timer += _Delta;
				}

			}
			else
			{
				Timer = 0.f;
			}
		}

		if (Timer >= 1.f)
		{
			Moving = true;
			Tile::GetTile(Index)->Empty();
		}
	}

	if (Moving)
	{
		Pos.Y -= 80.f * _Delta;
		MoveDist += 80.f * _Delta;
		for (auto Ptr : Level->FindActor(UpdateOrder::Player))
		{
			if (Ptr->Top() >= Bot())
			{
				Ptr->SetPos({ Ptr->GetPos().X, Pos.Y + TileSize.Y});
			}
		}
		if (MoveDist >= TileSize.Y)
		{
			Moving = false;
			Index = PosToIndex(Pos);
			Tile::GetTile(Index)->Full();
			MoveDist -= TileSize.Y;
			Pos.Y += MoveDist * _Delta;
			Timer = 0.f;
			MoveDist = 0.f;
		}
	}

	//Index = PosToIndex(Pos);
}

void Object::Render()
{
	//DrawRect(Pos, Scale);
	char Buffer[30] = {};
	sprintf_s(Buffer, "%f, %f", Timer, MoveDist);
	DrawStr(Pos, Buffer);
}
