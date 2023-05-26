#pragma once
#include <GameEngineBase/GameEngineMath.h>

const float4 TileSize = { 42, 42 };

const int IndexLeft = 0;
const int IndexTop = 0;
const int2 IndexLeftTop = { IndexLeft, IndexTop };
const float MapLeft = 21;
const float MapTop = 43;
const float4 MapLeftTop = { MapLeft, MapTop };

const int IndexRight = 15;
const int IndexBottom = 13;
const int2 IndexRightBottom = { IndexRight, IndexBottom };
const float MapRight = MapLeft + TileSize.X * IndexRight;
const float MapBottom = MapTop + TileSize.Y * IndexBottom;
const float4 MapRightBottom = { MapRight, MapBottom };

const float TrimRatio = 0.6f;
const float SpeedRatio = 0.7f;

enum class UpdateOrder
{
	Tile,

	Water,
	Block,
	Object,
	Bomb,
	Item,

	Player,
	Monster,

	UI,

	None,
};

enum class RenderOrder
{
	BackGround,
	Tile,
	Shadow,

	Water,
	Block,
	Object,
	Bomb,
	Item,

	Player,
	Monster,

	UI,

	None,
};

int2 PosToIndex(const float4& _Pos);
float4 IndexToPos(const int2& _Index);
