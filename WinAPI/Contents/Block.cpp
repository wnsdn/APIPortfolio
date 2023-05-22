#include "Block.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "Global.h"
#include "Tile.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Init(const int2& _Index, const std::string& _BlockSize, const float4& _Type)
{
	Index = _Index;
	Pos = IndexToPos(Index);

	CreateRenderer("Block\\" + _BlockSize, "Main", RenderOrder::Block, true, _Type, { 10, 9 });
	FindRenderer("Main")->SetRenderScale({TileSize.X, TileSize.Y * 2});
	FindRenderer("Main")->SetRenderPos({0, -TileSize.hY()});

	Tile::GetTile(Index)->Full();
}

void Block::Update(float _Delta)
{

}

void Block::Render()
{
	DrawRect(Pos, TileSize);
}
