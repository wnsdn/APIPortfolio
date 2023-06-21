#include "Tile.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"

Tile* Tile::TileArr[13][15]{};

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Init(const float4& _Pos)
{
	Pos = _Pos;

	Renderer[0] = CreateRenderer("Tile1x1.bmp", RenderOrder::Tile, {}, { 10,10 });
	Renderer[0]->SetScale({ 42, 42 });
	Renderer[0]->Off();

	Renderer[1] = CreateRenderer("1x1_1.bmp", RenderOrder::Block, {}, { 10,9 });
	Renderer[1]->AddPos({ 0, -21 });
	Renderer[1]->SetScale({ 42, 84 });
	Renderer[1]->Off();

	Renderer[2] = CreateRenderer("Object.bmp", RenderOrder::Object, {}, { 10,9 });
	Renderer[2]->AddPos({ 0, -21 });
	Renderer[2]->SetScale({ 47, 84 });
	Renderer[2]->Off();

	Renderer[3] = CreateRenderer("Item.bmp", RenderOrder::Item, {}, { 4,3 });
	Renderer[3]->Off();

	Renderer[4] = CreateRenderer("Position.bmp", RenderOrder::Position, {}, { 3,1 });
	Renderer[4]->SetScale({ 40, 40 });
	Renderer[4]->Off();

	InsertRenderer();
}

void Tile::Update(float _Delta)
{
	for (int i = 0; i <= 4; ++i)
	{
		Renderer[i]->SetCopyPos({ Attr[i].Idx.ToFloat4() });
	}
}

void Tile::Render(float _Delta)
{
}