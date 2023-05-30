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
		CanMove = true;
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
}

void Object::Render()
{
	DrawRect(Pos, Scale);
	//char Buffer[30] = {};
	//sprintf_s(Buffer, "%.2f", MoveUp);
	//DrawStr(Pos, Buffer);
}
